#include <chrono>
#include <cstdint>
#include <iostream>
#include <libataxx/libataxx.hpp>

using namespace std::chrono;
using namespace libataxx;

void split_perft(const Position &pos, const int depth) {
    std::uint64_t total_nodes = 0;

    // Generate initial moves
    Move moves[max_moves];
    const int num_moves = pos.legal_moves(moves);

    // Start timer
    const auto t0 = high_resolution_clock::now();

    for (int i = 0; i < num_moves; ++i) {
        // Make the current move on a new position
        Position npos = pos;
        npos.makemove(moves[i]);

        // Run perft on the new position and tally the results
        const std::uint64_t nodes = npos.perft(depth - 1);
        total_nodes += nodes;

        // Print output
        std::cout << i + 1 << "/" << num_moves;
        std::cout << "  " << moves[i];
        std::cout << "  " << nodes;
        std::cout << std::endl;
    }

    // Stop timer
    const auto t1 = high_resolution_clock::now();

    // Print summary
    const auto diff = duration_cast<milliseconds>(t1 - t0);
    std::cout << "Total: " << total_nodes << std::endl;
    std::cout << "Time: " << diff.count() << " ms" << std::endl;
}

int main(int argc, char **argv) {
    const auto pos = Position("startpos");

    std::cout << pos << std::endl;

    split_perft(pos, 7);

    return 0;
}
