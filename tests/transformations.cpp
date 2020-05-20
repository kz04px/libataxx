#include <iostream>
#include <libataxx/bitboard.hpp>
#include "catch.hpp"

TEST_CASE("transformation") {
    // Horizontal
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> horizontal[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::FileG},
        {libataxx::bitboards::FileB, libataxx::bitboards::FileF},
        {libataxx::bitboards::FileC, libataxx::bitboards::FileE},
        {libataxx::bitboards::FileD, libataxx::bitboards::FileD},
        {libataxx::bitboards::FileE, libataxx::bitboards::FileC},
        {libataxx::bitboards::FileF, libataxx::bitboards::FileB},
        {libataxx::bitboards::FileG, libataxx::bitboards::FileA},
        {libataxx::Bitboard{libataxx::squares::B2},
         libataxx::Bitboard{libataxx::squares::F2}},
    };
    for (const auto& [bb1, bb2] : horizontal) {
        REQUIRE(bb1.flip_horizontal() == bb2);
    }

    // Vertical
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> vertical[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::FileA},
        {libataxx::bitboards::FileB, libataxx::bitboards::FileB},
        {libataxx::bitboards::FileC, libataxx::bitboards::FileC},
        {libataxx::bitboards::FileD, libataxx::bitboards::FileD},
        {libataxx::bitboards::FileE, libataxx::bitboards::FileE},
        {libataxx::bitboards::FileF, libataxx::bitboards::FileF},
        {libataxx::bitboards::FileG, libataxx::bitboards::FileG},
        {libataxx::Bitboard{libataxx::squares::B2},
         libataxx::Bitboard{libataxx::squares::B6}},
    };
    for (const auto& [bb1, bb2] : vertical) {
        REQUIRE(bb1.flip_vertical() == bb2);
    }

    // Diagonal A7G1
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> a7g1[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank7},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank1},
        {libataxx::Bitboard{libataxx::squares::B2},
         libataxx::Bitboard{libataxx::squares::F6}},
    };
    for (const auto& [bb1, bb2] : a7g1) {
        REQUIRE(bb1.flip_diagA7G1() == bb2);
    }

    // Diagonal A1G7
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> a1g7[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank1},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank7},
        {libataxx::Bitboard{libataxx::squares::B6},
         libataxx::Bitboard{libataxx::squares::F2}},
    };
    for (const auto& [bb1, bb2] : a1g7) {
        REQUIRE(bb1.flip_diagA1G7() == bb2);
    }

    // Rotate 90 clockwise
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> rot90[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank7},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank1},
        {libataxx::Bitboard{libataxx::squares::B2},
         libataxx::Bitboard{libataxx::squares::B6}},
    };
    for (const auto& [bb1, bb2] : rot90) {
        REQUIRE(bb1.rot90() == bb2);
    }

    // Rotate 180 clockwise
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> rot180[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::FileG},
        {libataxx::bitboards::FileB, libataxx::bitboards::FileF},
        {libataxx::bitboards::FileC, libataxx::bitboards::FileE},
        {libataxx::bitboards::FileD, libataxx::bitboards::FileD},
        {libataxx::bitboards::FileE, libataxx::bitboards::FileC},
        {libataxx::bitboards::FileF, libataxx::bitboards::FileB},
        {libataxx::bitboards::FileG, libataxx::bitboards::FileA},
        {libataxx::Bitboard{libataxx::squares::B2},
         libataxx::Bitboard{libataxx::squares::F6}},
    };
    for (const auto& [bb1, bb2] : rot180) {
        REQUIRE(bb1.rot90().rot90() == bb2);
        REQUIRE(bb1.rot180() == bb2);
    }

    // Rotate 270 clockwise
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> rot270[] = {
        {libataxx::bitboards::Empty, libataxx::bitboards::Empty},
        {libataxx::bitboards::All, libataxx::bitboards::All},
        {libataxx::bitboards::FileA, libataxx::bitboards::Rank1},
        {libataxx::bitboards::FileB, libataxx::bitboards::Rank2},
        {libataxx::bitboards::FileC, libataxx::bitboards::Rank3},
        {libataxx::bitboards::FileD, libataxx::bitboards::Rank4},
        {libataxx::bitboards::FileE, libataxx::bitboards::Rank5},
        {libataxx::bitboards::FileF, libataxx::bitboards::Rank6},
        {libataxx::bitboards::FileG, libataxx::bitboards::Rank7},
        {libataxx::Bitboard{libataxx::squares::B2},
         libataxx::Bitboard{libataxx::squares::F2}},
    };
    for (const auto& [bb1, bb2] : rot270) {
        REQUIRE(bb1.rot90().rot90().rot90() == bb2);
        REQUIRE(bb1.rot270() == bb2);
    }

    // Same
    const libataxx::Bitboard same[] = {
        libataxx::bitboards::Empty,
        libataxx::bitboards::All,
        libataxx::bitboards::FileA,
        libataxx::bitboards::FileB,
        libataxx::bitboards::FileC,
        libataxx::bitboards::FileD,
        libataxx::bitboards::FileE,
        libataxx::bitboards::FileF,
        libataxx::bitboards::FileG,
        libataxx::Bitboard{libataxx::squares::B2},
        libataxx::Bitboard{libataxx::squares::B6},
        libataxx::Bitboard{libataxx::squares::F2},
        libataxx::Bitboard{libataxx::squares::B6},
    };
    for (const auto& bb : same) {
        REQUIRE(bb.flip_horizontal().flip_horizontal() == bb);
        REQUIRE(bb.flip_vertical().flip_vertical() == bb);
        REQUIRE(bb.flip_diagA1G7().flip_diagA1G7() == bb);
        REQUIRE(bb.flip_diagA7G1().flip_diagA7G1() == bb);
        REQUIRE(bb.rot90().rot90().rot90().rot90() == bb);
        REQUIRE(bb.rot180().rot180() == bb);
        REQUIRE(bb.rot270().rot270().rot270().rot270() == bb);
        REQUIRE(bb.rot270().rot90() == bb);
    }
}