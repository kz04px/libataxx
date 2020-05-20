#include <ctime>
#include <fstream>
#include <iostream>
#include <libataxx/pgn.hpp>
#include <libataxx/position.hpp>

int main() {
    std::srand(std::time(nullptr));

    auto pos = libataxx::Position("startpos");

    // Create .pgn
    libataxx::pgn::PGN pgn{};
    pgn.header().add("Event", "Random game");
    pgn.header().add("FEN", pos.get_fen());
    pgn.header().add("Black", "PlayerBlack");
    pgn.header().add("White", "PlayerWhite");

    auto *node = pgn.root();
    libataxx::Move moves[libataxx::max_moves];

    // Create game
    while (!pos.gameover()) {
        // Play random move
        const int num_moves = pos.legal_moves(moves);
        const int idx = std::rand() % num_moves;
        pos.makemove(moves[idx]);

        // Add move to pgn
        node = node->add_mainline(moves[idx]);
    }

    switch (pos.result()) {
        case libataxx::Result::WhiteWin:
            pgn.header().add("Result", "1-0");
            break;
        case libataxx::Result::BlackWin:
            pgn.header().add("Result", "0-1");
            break;
        case libataxx::Result::Draw:
            pgn.header().add("Result", "1/2-1/2");
            break;
        case libataxx::Result::None:
            pgn.header().add("Result", "*");
            break;
        default:
            break;
    }

    // Write .pgn
    std::ofstream file("game.pgn");
    if (file.is_open()) {
        file << pgn;
    }
    file.close();

    return 0;
}
