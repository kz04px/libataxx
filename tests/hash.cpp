#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Move::hash()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0 1",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0 1",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0 1",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        REQUIRE(pos.hash());
    }
}
