#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Move::get_fen()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0",
        "7/7/7/7/7/7/7 x 0",
        "7/7/7/7/7/7/7 o 0",
        "7/7/7/7/7/7/7 x 100",
        "7/7/7/7/7/7/7 o 100",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        REQUIRE(pos.get_fen() == fen);
    }
}
