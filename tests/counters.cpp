#include <libataxx/bitboard.hpp>
#include <libataxx/position.hpp>
#include <string>
#include <tuple>
#include <vector>
#include "catch.hpp"

using asd = std::tuple<std::string, unsigned int, unsigned int>;

TEST_CASE("counters") {
    {
        std::vector<asd> tests = {
            {"g2", 0u, 1u},
            {"a2", 0u, 2u},
            {"g3", 0u, 2u},
            {"a2a4", 1u, 3u},
            {"a7a5", 2u, 3u},
            {"a1b3", 3u, 4u},
            {"b4", 0u, 4u},
            {"f6", 0u, 5u},
        };

        libataxx::Position pos("startpos");
        for (const auto& [movestr, half, full] : tests) {
            try {
                const libataxx::Move move = libataxx::Move::from_uai(movestr);
                pos.makemove(move);
                REQUIRE(pos.get_halfmoves() == half);
                REQUIRE(pos.get_fullmoves() == full);
            } catch (...) {
                FAIL();
            }
        }
    }

    {
        libataxx::Position pos("7/7/7/7/4ooo/4ooo/4oox x 0 1");
        pos.makemove(libataxx::Move::nullmove());
        REQUIRE(pos.get_halfmoves() == 1);
        REQUIRE(pos.get_fullmoves() == 1);
        pos.makemove(libataxx::Move::from_uai("d1"));
        REQUIRE(pos.get_halfmoves() == 0);
        REQUIRE(pos.get_fullmoves() == 2);
        pos.makemove(libataxx::Move::nullmove());
        REQUIRE(pos.get_halfmoves() == 1);
        REQUIRE(pos.get_fullmoves() == 2);
        pos.makemove(libataxx::Move::from_uai("d1b1"));
        REQUIRE(pos.get_halfmoves() == 2);
        REQUIRE(pos.get_fullmoves() == 3);
        pos.makemove(libataxx::Move::nullmove());
        REQUIRE(pos.get_halfmoves() == 3);
        REQUIRE(pos.get_fullmoves() == 3);
        pos.makemove(libataxx::Move::from_uai("a1"));
        REQUIRE(pos.get_halfmoves() == 0);
        REQUIRE(pos.get_fullmoves() == 4);
    }
}
