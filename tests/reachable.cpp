#include <libataxx/bitboard.hpp>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::reachable()") {
    const std::pair<std::string, libataxx::Bitboard> tests[] = {
        {"7/7/7/7/7/7/6x x 0 1", libataxx::Bitboard(libataxx::Bitmask::All)},
        {"7/7/7/7/7/7/6o o 0 1", libataxx::Bitboard(libataxx::Bitmask::All)},
        {"7/7/7/7/7/7/7 x 0 1", libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {"7/7/7/7/7/7/7 o 0 1", libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {"7/7/-------/7/7/7/6x x 0 1", libataxx::Bitboard{0x7f7f007f7f7f7f}},
        {"7/7/-------/7/7/7/6o o 0 1", libataxx::Bitboard{0x7f7f007f7f7f7f}},
        {"7/7/-------/-------/7/7/6x x 0 1", libataxx::Bitboard{0x7f7f7f}},
        {"7/7/-------/-------/7/7/6o o 0 1", libataxx::Bitboard{0x7f7f7f}},
        {"6o/7/-------/-------/7/7/6x x 0 1", libataxx::Bitboard{0x7f7f00007f7f7f}},
        {"6o/7/-------/-------/7/7/6x o 0 1", libataxx::Bitboard{0x7f7f00007f7f7f}},
        {"4oox/4ooo/4ooo/7/7/7/7 x 0 1", libataxx::Bitboard(libataxx::Bitmask::All)},
        {"4oox/4ooo/4ooo/7/7/7/7 o 0 1", libataxx::Bitboard(libataxx::Bitmask::All)},
    };

    for (const auto& [fen, bb] : tests) {
        const libataxx::Position pos{fen};
        REQUIRE(pos.get_reachable() == bb);
    }
}

TEST_CASE("Position::reachable(Side)") {
    const std::pair<std::string, libataxx::Bitboard> tests[] = {
        {"7/7/7/7/7/7/6x x 0 1", libataxx::Bitboard(libataxx::Bitmask::All)},
        {"7/7/7/7/7/7/6o o 0 1", libataxx::Bitboard(libataxx::Bitmask::All)},
        {"7/7/7/7/7/7/7 x 0 1", libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {"7/7/7/7/7/7/7 o 0 1", libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {"7/7/-------/7/7/7/6x x 0 1", libataxx::Bitboard{0x7f7f007f7f7f7f}},
        {"7/7/-------/7/7/7/6o o 0 1", libataxx::Bitboard{0x7f7f007f7f7f7f}},
        {"7/7/-------/-------/7/7/6x x 0 1", libataxx::Bitboard{0x7f7f7f}},
        {"7/7/-------/-------/7/7/6o o 0 1", libataxx::Bitboard{0x7f7f7f}},
        {"6o/7/-------/-------/7/7/6x x 0 1", libataxx::Bitboard{0x7f7f7f}},
        {"6o/7/-------/-------/7/7/6x o 0 1", libataxx::Bitboard{0x7f7f0000000000}},
        {"4oox/4ooo/4ooo/7/7/7/7 x 0 1", libataxx::Bitboard{0x40000000000000}},
        {"4oox/4ooo/4ooo/7/7/7/7 o 0 1", libataxx::Bitboard{0x3f7f7f7f7f7f7f}},
    };

    for (const auto& [fen, bb] : tests) {
        const libataxx::Position pos{fen};
        REQUIRE(pos.get_reachable(pos.get_turn()) == bb);
        REQUIRE((pos.get_reachable() | pos.get_reachable(libataxx::Side::Black)) == pos.get_reachable());
        REQUIRE((pos.get_reachable() | pos.get_reachable(libataxx::Side::White)) == pos.get_reachable());
    }
}
