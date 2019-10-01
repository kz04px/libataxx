#include <libataxx/move.hpp>
#include <libataxx/position.hpp>

#define CATCH_CONFIG_MAIN
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
}

TEST_CASE("Position::perft()") {
    const std::pair<std::string, std::uint64_t> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0", 155888},
        {"x5o/7/2-1-2/7/2-1-2/7/o5x x 0", 86528},
        {"x5o/7/3-3/2-1-2/3-3/7/o5x x 0", 133264},
    };

    for (const auto &[fen, nodes] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.perft(4) == nodes);
    }
}

TEST_CASE("Position::count_moves()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0",
        "o6/7/7/7/7/7/7 x 0",
        "o6/7/7/7/7/7/7 o 0",
        "7/7/7/7/4ooo/4ooo/4oox x 0",
        "7/7/7/7/4ooo/4ooo/4oox o 0",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        libataxx::Move moves[libataxx::max_moves];
        const int num_moves = pos.legal_moves(moves);
        REQUIRE(pos.count_moves() == num_moves);
    }
}

TEST_CASE("Position::gameover()") {
    const std::pair<std::string, bool> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0", false},
        {"x5o/7/2-1-2/7/2-1-2/7/o5x x 0", false},
        {"x5o/7/3-3/2-1-2/3-3/7/o5x x 0", false},
        {"7/7/7/7/7/7/7 x 0", true},
        {"7/7/7/7/7/7/7 o 0", true},
        {"x5o/7/7/7/7/7/o5x x 0", false},
        {"x5o/7/7/7/7/7/o5x x 99", false},
        {"x5o/7/7/7/7/7/o5x x 100", true},
        {"x5o/7/7/7/7/7/o5x x 101", true},
        {"x6/7/7/7/7/7/7 x 0", true},
        {"x6/7/7/7/7/7/7 o 0", true},
        {"o6/7/7/7/7/7/7 x 0", true},
        {"o6/7/7/7/7/7/7 o 0", true},
    };

    for (const auto &[fen, gameover] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.gameover() == gameover);

        const int num_moves = pos.count_moves();

        if (gameover) {
            REQUIRE(num_moves == 0);
        } else {
            REQUIRE(num_moves > 0);
            REQUIRE(num_moves < libataxx::max_moves);
        }
    }
}

TEST_CASE("Position::legal_move()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0",
        "o6/7/7/7/7/7/7 x 0",
        "o6/7/7/7/7/7/7 o 0",
        "7/7/7/7/4ooo/4ooo/4oox x 0",
        "7/7/7/7/4ooo/4ooo/4oox o 0",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};

        libataxx::Move moves[libataxx::max_moves];
        const int num_moves = pos.legal_moves(moves);

        for (int i = 0; i < num_moves; ++i) {
            REQUIRE(pos.legal_move(moves[i]) == true);
        }

        if (!pos.must_pass()) {
            REQUIRE(pos.legal_move(libataxx::Move::nullmove()) == false);
        }
    }
}

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

TEST_CASE("Position::score()") {
    const std::pair<std::string, int> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0", 0},
        {"x5o/7/2-1-2/7/2-1-2/7/o5x x 0", 0},
        {"x5o/7/3-3/2-1-2/3-3/7/o5x x 0", 0},
        {"7/7/7/7/7/7/7 x 0", 0},
        {"x6/7/7/7/7/7/7 x 0", 1},
        {"o6/7/7/7/7/7/7 x 0", -1},
        {"xxo4/7/7/7/7/7/7 x 0", 1},
        {"oox4/7/7/7/7/7/7 x 0", -1},
        {"xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx x 0", 49},
        {"ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo x 0", -49},
    };

    for (const auto &[fen, score] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.score() == score);
    }
}

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

    for (const auto &[fen, pass] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.must_pass() == pass);
    }
}

TEST_CASE("Move::hash()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        REQUIRE(pos.hash());
    }
}
