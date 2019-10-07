#include <libataxx/move.hpp>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Move::from_uai()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0",
        "xxxxxxx/7/ooooooo/7/ooooooo/7/xxxxxxx x 0",
    };

    REQUIRE(libataxx::Move::nullmove() == libataxx::Move::from_uai("0000"));

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};

        libataxx::Move moves[libataxx::max_moves];
        const int num_moves = pos.legal_moves(moves);

        for (int i = 0; i < num_moves; ++i) {
            const std::string movestr = static_cast<std::string>(moves[i]);
            REQUIRE(moves[i] == libataxx::Move::from_uai(movestr));
        }
    }

    const std::string move_strings[] = {
        "g8",
        "g0",
        "h1",
        "e",
        "1",
        "g1g4",
        "g1g1",
        "00000",
        "",
    };
    for (const auto &movestr : move_strings) {
        try {
            [[maybe_unused]] const auto move =
                libataxx::Move::from_uai(movestr);
            FAIL("Illegal move string parsed: " << movestr);
        } catch (...) {
        }
    }
}
