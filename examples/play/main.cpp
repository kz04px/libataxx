#include <iostream>
#include <libataxx/libataxx.hpp>
#include <string>

using namespace libataxx;

int main(int argc, char **argv) {
    auto pos = Position("startpos");

    while (!pos.gameover()) {
        // Print board
        std::cout << pos << std::endl;

        // Get move
        std::cout << "Move: ";
        std::string movestr;
        std::cin >> movestr;
        std::cout << std::endl;

        // Find & make move
        Move moves[max_moves];
        const int num_moves = pos.legal_moves(moves);
        for (int i = 0; i < num_moves; ++i) {
            if (static_cast<std::string>(moves[i]) == movestr) {
                pos.makemove(moves[i]);
                break;
            }
        }
    }

    // Print board
    std::cout << pos << std::endl;

    return 0;
}
