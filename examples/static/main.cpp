#include <chrono>
#include <iostream>
#include <libataxx.hpp>

using namespace std::chrono;

int main(int argc, char **argv) {
    auto pos = libataxx::Position("startpos");

    std::cout << pos << std::endl;

    for (int i = 0; i <= 7; ++i) {
        const auto t0 = high_resolution_clock::now();
        const auto nodes = pos.perft(i);
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
