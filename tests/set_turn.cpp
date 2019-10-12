#include <libataxx/position.hpp>
#include "catch.hpp"

TEST_CASE("Position::set_turn()") {
    libataxx::Position pos{"x5o/7/7/7/7/7/o5x x 0 1"};
    REQUIRE(pos.turn() == libataxx::Side::Black);
    pos.set_turn(libataxx::Side::White);
    REQUIRE(pos.turn() == libataxx::Side::White);
}
