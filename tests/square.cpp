#include <iostream>
#include <libataxx/square.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Square()") {
    for (int i = 0; i < 49; ++i) {
        const auto sq = libataxx::Square{i};
        const int f = i % 7;
        const int r = i / 7;
        REQUIRE(static_cast<int>(sq) == i);
        REQUIRE(libataxx::Square(f, r) == sq);
        REQUIRE(libataxx::Square(sq.file(), sq.rank()) == sq);
    }
}
