#include <libataxx/move.hpp>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::legal_captures()") {
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
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        libataxx::Move moves[libataxx::max_moves];
        const int num_moves = pos.legal_captures(moves);
        for (int i = 0; i < num_moves; ++i) {
            const auto num_captured = pos.count_captures(moves[i]);
            REQUIRE(pos.is_capture(moves[i]));
            REQUIRE(num_captured > 0);
            REQUIRE(num_captured <= 8);
        }
    }
}
