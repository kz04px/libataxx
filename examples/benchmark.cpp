#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <libataxx/libataxx.hpp>
#include <string>

const std::array<std::string, 20> fens = {
    "x5o/7/7/7/7/7/o5x x 0 1",
    "x5o/7/2-1-2/7/2-1-2/7/o5x x 0 1",
    "x5o/7/3-3/2-1-2/3-3/7/o5x x 0 1",
    "x2-2o/3-3/2---2/7/2---2/3-3/o2-2x x 0 1",
    "x2-2o/3-3/7/--3--/7/3-3/o2-2x x 0 1",
    "x1-1-1o/2-1-2/2-1-2/7/2-1-2/2-1-2/o1-1-1x x 0 1",
    "x5o/7/2-1-2/3-3/2-1-2/7/o5x x 0 1",
    "x5o/7/3-3/2---2/3-3/7/o5x x 0 1",
    "x5o/2-1-2/1-3-1/7/1-3-1/2-1-2/o5x x 0 1",
    "x5o/1-3-1/2-1-2/7/2-1-2/1-3-1/o5x x 0 1",
    "x-1-1-o/-1-1-1-/1-1-1-1/-1-1-1-/1-1-1-1/-1-1-1-/o-1-1-x x 0 1",
    "x-1-1-o/1-1-1-1/1-1-1-1/1-1-1-1/1-1-1-1/1-1-1-1/o-1-1-x x 0 1",
    "x1-1-1o/2-1-2/-------/2-1-2/-------/2-1-2/o1-1-1x x 0 1",
    "x5o/1-----1/1-3-1/1-1-1-1/1-3-1/1-----1/o5x x 0 1",
    "x-1-1-o/1-1-1-1/-1-1-1-/-1-1-1-/-1-1-1-/1-1-1-1/o-1-1-x/ x 0 1",
    "x5o/1--1--1/1--1--1/7/1--1--1/1--1--1/o5x x 0 1",
    "x-3-o/1-1-1-1/1-1-1-1/3-3/1-1-1-1/1-1-1-1/o-3-x x 0 1",
    "x2-2o/3-3/3-3/-------/3-3/3-3/o2-2x x 0 1",
    "x2-2o/2-1-2/1-3-1/-2-2-/1-3-1/2-1-2/o2-2x x 0 1",
    "x5o/6-/1-4-/-3--1/2-4/7/o-3-x x 0 1",
};

[[nodiscard]] auto format_ms(const std::chrono::microseconds micro) noexcept -> std::string {
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(micro).count();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(micro).count();
    return std::to_string(seconds) + "." + std::to_string((milliseconds / 100) % 10) +
           std::to_string((milliseconds / 10) % 10) + std::to_string(milliseconds % 10);
}

int main(int argc, char **argv) {
    int depth = 1;
    auto total_time = std::chrono::microseconds(0);
    std::uint64_t total_nodes = 0;

    // Get depth
    if (argc > 1) {
        depth = std::stoi(argv[1]);
        depth = std::max(1, depth);
    }

    // Print chart title
    std::cout << "Pos       Nodes       ΣNodes     Time     ΣTime   Mnps  ΣMnps  FEN\n";

    for (std::size_t i = 0; i < fens.size(); ++i) {
        const auto pos = libataxx::Position(fens.at(i));

        // Perft
        const auto t0 = std::chrono::steady_clock::now();
        const auto nodes = pos.perft(depth);
        const auto t1 = std::chrono::steady_clock::now();
        const auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);

        total_time += dt;
        total_nodes += nodes;
        const auto mnps = dt.count() == 0 ? 0 : nodes / dt.count();
        const auto total_mnps = total_time.count() == 0 ? 0 : total_nodes / total_time.count();

        // Print chart row
        std::cout << std::left;
        std::cout << std::setw(5) << i + 1;
        std::cout << std::right;
        std::cout << std::setw(10) << nodes;
        std::cout << std::setw(13) << total_nodes;
        std::cout << std::setw(9) << format_ms(dt);
        std::cout << std::setw(10) << format_ms(total_time);
        std::cout << std::setw(7) << mnps;
        std::cout << std::setw(7) << total_mnps;
        std::cout << std::left;
        std::cout << "  " << fens.at(i);
        std::cout << "\n";
    }

    return 0;
}
