#include <libataxx/move.hpp>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Combined moves") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0 1",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0 1",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0 1",
        "o6/7/7/7/7/7/7 x 0 1",
        "o6/7/7/7/7/7/7 o 0 1",
        "7/7/7/7/4ooo/4ooo/4oox x 0 1",
        "7/7/7/7/4ooo/4ooo/4oox o 0 1",
        "7/7/7/7/7/7/2x1o2 x 0 1",
        "7/7/7/7/7/7/2x1o2 o 0 1",
        "7/7/7/7/7/7/7 x 0 1",
        "7/7/7/7/7/7/7 o 0 1",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        libataxx::Move moves[libataxx::max_moves];
        libataxx::Move captures[libataxx::max_moves];
        libataxx::Move noncaptures[libataxx::max_moves];
        const int num_moves = pos.legal_moves(moves);
        const int num_captures = pos.legal_captures(captures);
        const int num_noncaptures = pos.legal_noncaptures(noncaptures);

        REQUIRE(num_moves == num_captures + num_noncaptures);

        // Every capture must exist in all moves
        for (int a = 0; a < num_captures; ++a) {
            bool found = false;
            for (int b = 0; b < num_moves; ++b) {
                if (captures[a] == moves[b]) {
                    found = true;
                    break;
                }
            }
            REQUIRE(found);
        }

        // Every noncapture must exist in all moves
        for (int a = 0; a < num_noncaptures; ++a) {
            bool found = false;
            for (int b = 0; b < num_moves; ++b) {
                if (noncaptures[a] == moves[b]) {
                    found = true;
                    break;
                }
            }
            REQUIRE(found);
        }

        // Captures and noncaptures can't be the same
        for (int a = 0; a < num_captures; ++a) {
            for (int b = 0; b < num_noncaptures; ++b) {
                REQUIRE(captures[a] != noncaptures[b]);
            }
        }
    }
}
