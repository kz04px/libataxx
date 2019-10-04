#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::score()") {
    const std::pair<std::string, int> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0", 0},
        {"x5o/7/2-1-2/7/2-1-2/7/o5x x 0", 0},
        {"x5o/7/3-3/2-1-2/3-3/7/o5x x 0", 0},
        {"7/7/7/7/7/7/7 x 0", 0},
        {"x6/7/7/7/7/7/7 x 0", 1},
        {"o6/7/7/7/7/7/7 x 0", -1},
        {"xxo4/7/7/7/7/7/7 x 0", 1},
        {"oox4/7/7/7/7/7/7 x 0", -1},
        {"xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx x 0", 49},
        {"ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo x 0", -49},
    };

    for (const auto& [fen, score] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.score() == score);
    }
}
