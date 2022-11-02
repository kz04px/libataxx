#include <libataxx/move.hpp>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::is_gameover()") {
    const std::pair<std::string, bool> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0 1", false},
        {"x5o/7/2-1-2/7/2-1-2/7/o5x x 0 1", false},
        {"x5o/7/3-3/2-1-2/3-3/7/o5x x 0 1", false},
        {"7/7/7/7/7/7/7 x 0 1", true},
        {"7/7/7/7/7/7/7 o 0 1", true},
        {"x5o/7/7/7/7/7/o5x x 0 1", false},
        {"x5o/7/7/7/7/7/o5x x 99 1", false},
        {"x5o/7/7/7/7/7/o5x x 100 1", true},
        {"x5o/7/7/7/7/7/o5x x 101 1", true},
        {"x6/7/7/7/7/7/7 x 0 1", true},
        {"x6/7/7/7/7/7/7 o 0 1", true},
        {"o6/7/7/7/7/7/7 x 0 1", true},
        {"o6/7/7/7/7/7/7 o 0 1", true},
    };

    for (const auto& [fen, gameover] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.is_gameover() == gameover);

        const int num_moves = pos.count_legal_moves();

        if (gameover) {
            REQUIRE(num_moves == 0);
        } else {
            REQUIRE(num_moves > 0);
            REQUIRE(num_moves < libataxx::max_moves);
        }
    }
}
