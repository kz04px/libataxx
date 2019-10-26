#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Move") {
    REQUIRE(libataxx::Move{} == libataxx::Move::nomove());
    REQUIRE(!libataxx::Move::nomove());
    REQUIRE(libataxx::Move::nullmove());
    REQUIRE(libataxx::Move::nomove() != libataxx::Move::nullmove());
    REQUIRE(static_cast<std::string>(libataxx::Move::nullmove()) == "0000");
    REQUIRE(static_cast<std::string>(libataxx::Move::nomove()) == "NONE");
}
