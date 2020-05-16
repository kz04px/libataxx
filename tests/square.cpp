#include <iostream>
#include <libataxx/square.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Square()") {
    for (int f = 0; f < 7; ++f) {
        for (int r = 0; r < 7; ++r) {
            const auto sq = libataxx::Square{f, r};
            REQUIRE(static_cast<int>(sq.file()) == f);
            REQUIRE(static_cast<int>(sq.rank()) == r);
            REQUIRE(libataxx::Square(sq.file(), sq.rank()) == sq);
        }
    }
}
