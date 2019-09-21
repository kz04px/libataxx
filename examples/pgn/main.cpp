#include <ctime>
#include <fstream>
#include <iostream>
#include <libataxx/libataxx.hpp>
#include <libataxx/pgn.hpp>

int main(int argc, char **argv) {
    std::srand(std::time(nullptr));

    auto pos = libataxx::Position("startpos");

    // Create .pgn
    libataxx::pgn::PGN pgn{};
    pgn.header().add("Event", "Random game");
    pgn.header().add("FEN", "x5o/7/7/7/7/7/o5x x");
    pgn.header().add("Black", "PlayerBlack");
    pgn.header().add("White", "PlayerWhite");

    libataxx::pgn::Node *node = pgn.root();

    // Create game
    while (!pos.gameover()) {
        // Play random move
        libataxx::Move moves[libataxx::max_moves];
        const int num_moves = pos.legal_moves(moves);
        const libataxx::Move move = moves[std::rand() % num_moves];
        pos.makemove(move);

        // Add move to pgn
        node = node->add_mainline(move);
    }

    // Write .pgn
    std::ofstream file("game.pgn");
    if (file.is_open()) {
        file << pgn;
    }
    file.close();

    return 0;
}
