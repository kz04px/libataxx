#include <libataxx/bitboard.hpp>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::reachable()") {
    const std::pair<std::string, libataxx::Bitboard> tests[] = {
        {"7/7/7/7/7/7/6x x 0", libataxx::Bitboard::all()},
        {"7/7/7/7/7/7/6o o 0", libataxx::Bitboard::all()},
        {"7/7/7/7/7/7/7 x 0", libataxx::Bitboard{}},
        {"7/7/7/7/7/7/7 o 0", libataxx::Bitboard{}},
        {"7/7/-------/7/7/7/6x x 0", libataxx::Bitboard{0x1FFF80FFFFFFF}},
        {"7/7/-------/7/7/7/6o o 0", libataxx::Bitboard{0x1FFF80FFFFFFF}},
        {"7/7/-------/-------/7/7/6x x 0", libataxx::Bitboard{0x1FFFFF}},
        {"7/7/-------/-------/7/7/6o o 0", libataxx::Bitboard{0x1FFFFF}},
    };

    for (const auto& [fen, bb] : tests) {
        const libataxx::Position pos{fen};
        REQUIRE(pos.reachable() == bb);
    }
}
