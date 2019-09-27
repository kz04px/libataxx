#include <chrono>
#include <iostream>
#include <libataxx/libataxx.hpp>
#include <libataxx/zobrist.hpp>

using namespace std::chrono;

struct TTEntry {
    std::uint64_t hash;
    std::uint64_t nodes;
    std::uint8_t depth;
};

class TT {
   public:
    TT(const unsigned int MB) {
        num_entries_ = (MB * 1024 * 1024) / sizeof(TTEntry);
        entries_ = new TTEntry[num_entries_];
    }

    ~TT() {
        delete entries_;
    }

    void set(const std::uint64_t hash,
             const std::uint64_t nodes,
             const std::uint8_t depth) noexcept {
        const auto idx = index(hash);
        entries_[idx] = {hash, nodes, depth};
    }

    [[nodiscard]] TTEntry get(const std::uint64_t hash) const noexcept {
        const auto idx = index(hash);
        return entries_[idx];
    }

    [[nodiscard]] std::size_t num_entries() const noexcept {
        return num_entries_;
    }

   private:
    [[nodiscard]] std::size_t index(const std::uint64_t hash) const noexcept {
        return hash % num_entries_;
    }

   private:
    std::size_t num_entries_;
    TTEntry *entries_;
};

std::uint64_t ttperft(TT &tt, const libataxx::Position &pos, const int depth) {
    if (depth == 1) {
        return pos.count_moves();
    } else if (depth == 0) {
        return 1;
    }

    // Poll TT
    const auto &entry = tt.get(pos.hash());
    if (pos.hash() == entry.hash && entry.depth == depth) {
        return entry.nodes;
    }

    std::uint64_t nodes = 0;
    libataxx::Move moves[libataxx::max_moves];
    const int num_moves = pos.legal_moves(moves);

    for (int i = 0; i < num_moves; ++i) {
        libataxx::Position npos = pos;
        npos.makemove(moves[i]);
        nodes += ttperft(tt, npos, depth - 1);
    }

    // Create TT entry
    tt.set(pos.hash(), nodes, depth);

    return nodes;
}

int main(int argc, char **argv) {
    unsigned int MB = 16;
    if (argc > 1) {
        try {
            MB = std::stoul(argv[1]);
            MB = std::max(MB, 1u);
        } catch (...) {
            return 1;
        }
    }
    TT tt{MB};
    std::cout << "Table size: " << MB << "MB" << std::endl;
    std::cout << "Number of entries: " << tt.num_entries() << std::endl;
    std::cout << "TTEntry size: " << sizeof(TTEntry) << "B" << std::endl;
    std::cout << "Entries/MB: " << (1024 * 1024) / sizeof(TTEntry) << std::endl;
    std::cout << std::endl;

    auto pos = libataxx::Position("startpos");

    std::cout << pos << std::endl;

    for (int i = 0; i <= 7; ++i) {
        const auto t0 = high_resolution_clock::now();
        const auto nodes = ttperft(tt, pos, i);
        const auto t1 = high_resolution_clock::now();
        const auto diff = duration_cast<milliseconds>(t1 - t0);

        std::cout << "Depth " << i;
        std::cout << " nodes " << nodes;
        std::cout << " time " << diff.count() << "ms";
        if (diff.count() > 0) {
            const auto nps = 1000 * (nodes / diff.count());
            std::cout << " nps " << nps;
        }
        std::cout << std::endl;
    }

    return 0;
}
