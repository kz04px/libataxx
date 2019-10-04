#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Passing & nullmove") {
    const std::pair<std::string, bool> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0", false},
        {"x5o/7/2-1-2/7/2-1-2/7/o5x x 0", false},
        {"x5o/7/3-3/2-1-2/3-3/7/o5x x 0", false},
        {"7/7/7/7/4ooo/4ooo/4oox x 0", true},
        {"7/7/7/7/4ooo/4ooo/4oox o 0", false},
        {"7/7/7/7/4xxx/4xxx/4xxo x 0", false},
        {"7/7/7/7/4xxx/4xxx/4xxo o 0", true},
        {"xxxxxxx/-------/-------/7/7/-------/ooooooo x 0", true},
        {"xxxxxxx/-------/-------/7/7/-------/ooooooo o 0", false},
        {"ooooooo/-------/-------/7/7/-------/xxxxxxx x 0", false},
        {"ooooooo/-------/-------/7/7/-------/xxxxxxx o 0", true},
    };

    for (const auto& [fen, pass] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.must_pass() == pass);
    }
}
