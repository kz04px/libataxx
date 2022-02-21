#include <libataxx/bitboard.hpp>
#include "catch.hpp"

TEST_CASE("flip_horizontal()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::FileG},
        {libataxx::bitboards::FileB, libataxx::bitboards::FileF},
        {libataxx::bitboards::FileC, libataxx::bitboards::FileE},
        {libataxx::bitboards::FileD, libataxx::bitboards::FileD},
        {libataxx::bitboards::FileE, libataxx::bitboards::FileC},
        {libataxx::bitboards::FileF, libataxx::bitboards::FileB},
        {libataxx::bitboards::FileG, libataxx::bitboards::FileA},
        {libataxx::Bitboard{libataxx::squares::B2}, libataxx::Bitboard{libataxx::squares::F2}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_horizontal() == bb2);
    }
}

TEST_CASE("flip_vertical()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::FileA},
        {libataxx::bitboards::FileB, libataxx::bitboards::FileB},
        {libataxx::bitboards::FileC, libataxx::bitboards::FileC},
        {libataxx::bitboards::FileD, libataxx::bitboards::FileD},
        {libataxx::bitboards::FileE, libataxx::bitboards::FileE},
        {libataxx::bitboards::FileF, libataxx::bitboards::FileF},
        {libataxx::bitboards::FileG, libataxx::bitboards::FileG},
        {libataxx::Bitboard{libataxx::squares::B2}, libataxx::Bitboard{libataxx::squares::B6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_vertical() == bb2);
    }
}

TEST_CASE("flip_diagA7G1()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank7},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank1},
        {libataxx::Bitboard{libataxx::squares::B2}, libataxx::Bitboard{libataxx::squares::F6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_diagA7G1() == bb2);
    }
}

TEST_CASE("flip_diagA1G7()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank1},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank7},
        {libataxx::Bitboard{libataxx::squares::B6}, libataxx::Bitboard{libataxx::squares::F2}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_diagA1G7() == bb2);
    }
}

TEST_CASE("rot90()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank7},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank1},
        {libataxx::Bitboard{libataxx::squares::B2}, libataxx::Bitboard{libataxx::squares::B6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.rot90() == bb2);
    }
}

TEST_CASE("rot180()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::FileG},
        {libataxx::bitboards::FileB, libataxx::bitboards::FileF},
        {libataxx::bitboards::FileC, libataxx::bitboards::FileE},
        {libataxx::bitboards::FileD, libataxx::bitboards::FileD},
        {libataxx::bitboards::FileE, libataxx::bitboards::FileC},
        {libataxx::bitboards::FileF, libataxx::bitboards::FileB},
        {libataxx::bitboards::FileG, libataxx::bitboards::FileA},
        {libataxx::Bitboard{libataxx::squares::B2}, libataxx::Bitboard{libataxx::squares::F6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.rot180() == bb2);
    }
}

TEST_CASE("rot270()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank1},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank7},
        {libataxx::Bitboard{libataxx::squares::B2}, libataxx::Bitboard{libataxx::squares::F2}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.rot270() == bb2);
    }
}

TEST_CASE("identity") {
    const libataxx::Bitboard bitboards[] = {
        libataxx::bitboards::Empty,
        libataxx::bitboards::All,
        libataxx::bitboards::Edge,
        libataxx::bitboards::Center,
        libataxx::bitboards::FileA,
        libataxx::bitboards::FileB,
        libataxx::bitboards::FileC,
        libataxx::bitboards::FileD,
        libataxx::bitboards::FileE,
        libataxx::bitboards::FileF,
        libataxx::bitboards::FileG,
        libataxx::bitboards::Rank1,
        libataxx::bitboards::Rank2,
        libataxx::bitboards::Rank3,
        libataxx::bitboards::Rank4,
        libataxx::bitboards::Rank5,
        libataxx::bitboards::Rank6,
        libataxx::bitboards::Rank7,
        libataxx::Bitboard{libataxx::squares::B2},
        libataxx::Bitboard{libataxx::squares::B6},
        libataxx::Bitboard{libataxx::squares::F2},
        libataxx::Bitboard{libataxx::squares::B6},
    };
    for (const auto& bb : bitboards) {
        REQUIRE(bb.flip_horizontal().flip_horizontal() == bb);
        REQUIRE(bb.flip_vertical().flip_vertical() == bb);
        REQUIRE(bb.flip_diagA1G7().flip_diagA1G7() == bb);
        REQUIRE(bb.flip_diagA7G1().flip_diagA7G1() == bb);
        REQUIRE(bb.rot90().rot90().rot90().rot90() == bb);
        REQUIRE(bb.rot90().rot90().rot180() == bb);
        REQUIRE(bb.rot90().rot180().rot90() == bb);
        REQUIRE(bb.rot180().rot90().rot90() == bb);
        REQUIRE(bb.rot180().rot180() == bb);
        REQUIRE(bb.rot270().rot270().rot270().rot270() == bb);
        REQUIRE(bb.rot270().rot90() == bb);
        REQUIRE(bb.rot90().rot270() == bb);
    }
}

TEST_CASE("equivalency") {
    const libataxx::Bitboard bitboards[] = {
        libataxx::bitboards::Empty,
        libataxx::bitboards::All,
        libataxx::bitboards::Edge,
        libataxx::bitboards::Center,
        libataxx::bitboards::FileA,
        libataxx::bitboards::FileB,
        libataxx::bitboards::FileC,
        libataxx::bitboards::FileD,
        libataxx::bitboards::FileE,
        libataxx::bitboards::FileF,
        libataxx::bitboards::FileG,
        libataxx::bitboards::Rank1,
        libataxx::bitboards::Rank2,
        libataxx::bitboards::Rank3,
        libataxx::bitboards::Rank4,
        libataxx::bitboards::Rank5,
        libataxx::bitboards::Rank6,
        libataxx::bitboards::Rank7,
        libataxx::Bitboard{libataxx::squares::B2},
        libataxx::Bitboard{libataxx::squares::B6},
        libataxx::Bitboard{libataxx::squares::F2},
        libataxx::Bitboard{libataxx::squares::B6},
    };
    for (const auto& bb : bitboards) {
        REQUIRE(bb.rot90().rot90() == bb.rot180());
        REQUIRE(bb.rot90().rot90().rot90() == bb.rot270());
        REQUIRE(bb.rot180().rot90() == bb.rot270());
        REQUIRE(bb.rot90().rot180() == bb.rot270());
    }
}
