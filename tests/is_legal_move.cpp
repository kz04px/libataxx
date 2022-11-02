#include <libataxx/move.hpp>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::is_legal_move()") {
    SECTION("Positions with legal moves") {
        const std::string fens[] = {
            "x5o/7/7/7/7/7/o5x x 0 1",
            "x5o/7/2-1-2/7/2-1-2/7/o5x x 0 1",
            "x5o/7/3-3/2-1-2/3-3/7/o5x x 0 1",
            "o6/7/7/7/7/7/7 x 0 1",
            "o6/7/7/7/7/7/7 o 0 1",
            "7/7/7/7/4ooo/4ooo/4oox x 0 1",
            "7/7/7/7/4ooo/4ooo/4oox o 0 1",
        };

        for (const auto &fen : fens) {
            const libataxx::Position pos{fen};
            const auto moves = pos.legal_moves();

            for (const auto &move : moves) {
                REQUIRE(move);
                REQUIRE(move != libataxx::Move::nomove());
                REQUIRE(pos.is_legal_move(move));
                REQUIRE(pos.is_pseudolegal_move(move));
            }

            if (!pos.must_pass()) {
                REQUIRE_FALSE(pos.is_legal_move(libataxx::Move::nullmove()));
            }
        }
    }

    SECTION("Positions with pseudolegal moves that are illegal") {
        const std::string fens[] = {
            "7/7/7/7/7/7/7 x 0 1",
            "7/7/7/7/7/7/7 o 0 1",
            "x6/7/7/7/7/7/7 x 0 1",
            "x6/7/7/7/7/7/7 o 0 1",
            "o6/7/7/7/7/7/7 x 0 1",
            "o6/7/7/7/7/7/7 o 0 1",
            "x5o/7/7/7/7/7/o5x x 100 1",
            "x5o/7/7/7/7/7/o5x o 100 1",
        };

        for (const auto &fen : fens) {
            const libataxx::Position pos{fen};
            const auto moves = pos.pseudolegal_moves();

            for (const auto &move : moves) {
                REQUIRE(move);
                REQUIRE(move != libataxx::Move::nomove());
                REQUIRE_FALSE(pos.is_legal_move(move));
                REQUIRE(pos.is_pseudolegal_move(move));
            }
        }
    }
}
