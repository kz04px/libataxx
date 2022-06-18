#include <chrono>
#include <iostream>
#include <libataxx/libataxx.hpp>

using namespace std::chrono;

int main(int argc, char **argv) {
    int depth = 6;
    std::string fen = "startpos";

    if (argc > 2) {
        depth = std::stoi(argv[1]);
        fen = argv[2];
        for (int i = 3; i < argc; ++i) {
            fen += " " + std::string(argv[i]);
        }
    }

    const auto pos = libataxx::Position(fen);

    std::cout << "FEN: " << fen << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << std::endl;

    std::cout << pos << std::endl;
    std::cout << std::endl;

    std::uint64_t total = 0;
    libataxx::Move moves[libataxx::max_moves];
    const int num_moves = pos.legal_moves(moves);

    const auto t0 = high_resolution_clock::now();
    for (int i = 0; i < num_moves; ++i) {
        const auto npos = pos.after_move(moves[i]);
        std::cout << i + 1 << ") " << moves[i];
        const auto nodes = npos.perft(depth - 1);
        std::cout << " " << nodes;
        std::cout << std::endl;
        total += nodes;
    }
    const auto t1 = high_resolution_clock::now();
    const auto diff = duration_cast<milliseconds>(t1 - t0);

    std::cout << std::endl;
    std::cout << "Total: " << total << std::endl;
    std::cout << "Time: " << diff.count() << "ms" << std::endl;
    if (diff.count() > 0) {
        const auto nps = 1000 * total / diff.count();
        std::cout << "NPS: " << nps << std::endl;
    }

    return 0;
}
