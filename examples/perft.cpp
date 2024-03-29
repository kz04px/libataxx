#include <chrono>
#include <iostream>
#include <libataxx/libataxx.hpp>

using namespace std::chrono;

int main(int argc, char **argv) {
    int depth = 6;
    std::string fen = "startpos";

    if (argc > 1) {
        depth = std::stoi(argv[1]);
    }

    if (argc > 2) {
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

    for (int i = 0; i <= depth; ++i) {
        const auto t0 = high_resolution_clock::now();
        const auto nodes = pos.perft(i);
        const auto t1 = high_resolution_clock::now();
        const auto diff = duration_cast<milliseconds>(t1 - t0);

        std::cout << "Depth " << i;
        std::cout << " nodes " << nodes;
        std::cout << " time " << diff.count() << "ms";
        if (diff.count() > 0) {
            const auto nps = 1000 * nodes / diff.count();
            std::cout << " nps " << nps;
        }
        std::cout << std::endl;
    }

    return 0;
}
