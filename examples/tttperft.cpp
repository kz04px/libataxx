#include <chrono>
#include <iostream>
#include <libataxx/libataxx.hpp>
#include "tt.hpp"

struct TTEntry {
    std::uint64_t hash = 0;
    std::uint64_t nodes = 0;
    std::uint8_t depth = 0;
};

[[nodiscard]] std::uint64_t ttperft(TT<TTEntry> &tt, const libataxx::Position &pos, const std::uint8_t depth) {
    if (depth == 0) {
        return 1;
    }
    if (depth == 1) {
        return pos.count_moves();
    }

    const auto hash = pos.get_minimal_hash();

    // Poll TT
    const auto &entry = tt.poll(hash);
    if (hash == entry.hash && entry.depth == depth) {
        return entry.nodes;
    }

    std::uint64_t nodes = 0;
    libataxx::Move moves[libataxx::max_moves];
    const int num_moves = pos.legal_moves(moves);

    for (int i = 0; i < num_moves; ++i) {
        const auto npos = pos.after_move(moves[i]);
        nodes += ttperft(tt, npos, depth - 1);
    }

    // Create TT entry
    tt.add(hash, {hash, nodes, depth});

    return nodes;
}

int main(int argc, char **argv) {
    unsigned int MB = 16;
    int depth = 6;
    std::string fen = "startpos";

    if (argc > 1) {
        MB = std::stoi(argv[1]);
    }

    if (argc > 2) {
        depth = std::stoi(argv[2]);
    }

    if (argc > 3) {
        fen = argv[3];
        for (int i = 4; i < argc; ++i) {
            fen += " " + std::string(argv[i]);
        }
    }

    TT<TTEntry> tt{MB};
    std::cout << "FEN: " << fen << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Table size: " << MB << "MB" << std::endl;
    std::cout << "Max entries: " << tt.size() << std::endl;
    std::cout << "TTEntry size: " << sizeof(TTEntry) << "B" << std::endl;
    std::cout << "Entries/MB: " << (1024 * 1024) / sizeof(TTEntry) << std::endl;
    std::cout << std::endl;

    auto pos = libataxx::Position(fen);

    std::cout << pos << std::endl;
    std::cout << std::endl;

    for (int i = 0; i <= depth; ++i) {
        const auto t0 = std::chrono::high_resolution_clock::now();
        const auto nodes = ttperft(tt, pos, i);
        const auto t1 = std::chrono::high_resolution_clock::now();
        const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

        std::cout << "Depth " << i;
        std::cout << " nodes " << nodes;
        std::cout << " hashfull " << tt.hashfull();
        std::cout << " time " << diff.count() << "ms";
        if (diff.count() > 0) {
            const auto nps = 1000 * nodes / diff.count();
            std::cout << " nps " << nps;
        }
        std::cout << std::endl;
    }

    return 0;
}
