#include <iostream>
#include <libataxx/bitboard.hpp>
#include "catch.hpp"

TEST_CASE("transformation") {
    // Horizontal
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> horizontal[] = {
        {libataxx::Bitboard::Empty(), libataxx::Bitboard::Empty()},
        {libataxx::Bitboard::all(), libataxx::Bitboard::all()},
        {libataxx::Bitboard::FileA(), libataxx::Bitboard::FileG()},
        {libataxx::Bitboard::FileB(), libataxx::Bitboard::FileF()},
        {libataxx::Bitboard::FileC(), libataxx::Bitboard::FileE()},
        {libataxx::Bitboard::FileD(), libataxx::Bitboard::FileD()},
        {libataxx::Bitboard::FileE(), libataxx::Bitboard::FileC()},
        {libataxx::Bitboard::FileF(), libataxx::Bitboard::FileB()},
        {libataxx::Bitboard::FileG(), libataxx::Bitboard::FileA()},
        {libataxx::Bitboard{libataxx::Squares::B2},
         libataxx::Bitboard{libataxx::Squares::F2}},
    };
    for (const auto& [bb1, bb2] : horizontal) {
        REQUIRE(bb1.flip_horizontal() == bb2);
    }

    // Vertical
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> vertical[] = {
        {libataxx::Bitboard::Empty(), libataxx::Bitboard::Empty()},
        {libataxx::Bitboard::all(), libataxx::Bitboard::all()},
        {libataxx::Bitboard::FileA(), libataxx::Bitboard::FileA()},
        {libataxx::Bitboard::FileB(), libataxx::Bitboard::FileB()},
        {libataxx::Bitboard::FileC(), libataxx::Bitboard::FileC()},
        {libataxx::Bitboard::FileD(), libataxx::Bitboard::FileD()},
        {libataxx::Bitboard::FileE(), libataxx::Bitboard::FileE()},
        {libataxx::Bitboard::FileF(), libataxx::Bitboard::FileF()},
        {libataxx::Bitboard::FileG(), libataxx::Bitboard::FileG()},
        {libataxx::Bitboard{libataxx::Squares::B2},
         libataxx::Bitboard{libataxx::Squares::B6}},
    };
    for (const auto& [bb1, bb2] : vertical) {
        REQUIRE(bb1.flip_vertical() == bb2);
    }

    // Diagonal A7G1
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> a7g1[] = {
        {libataxx::Bitboard::Empty(), libataxx::Bitboard::Empty()},
        {libataxx::Bitboard::all(), libataxx::Bitboard::all()},
        {libataxx::Bitboard::FileA(), libataxx::Bitboard::Rank7()},
        {libataxx::Bitboard::FileB(), libataxx::Bitboard::Rank6()},
        {libataxx::Bitboard::FileC(), libataxx::Bitboard::Rank5()},
        {libataxx::Bitboard::FileD(), libataxx::Bitboard::Rank4()},
        {libataxx::Bitboard::FileE(), libataxx::Bitboard::Rank3()},
        {libataxx::Bitboard::FileF(), libataxx::Bitboard::Rank2()},
        {libataxx::Bitboard::FileG(), libataxx::Bitboard::Rank1()},
        {libataxx::Bitboard{libataxx::Squares::B2},
         libataxx::Bitboard{libataxx::Squares::F6}},
    };
    for (const auto& [bb1, bb2] : a7g1) {
        REQUIRE(bb1.flip_diagA7G1() == bb2);
    }

    // Diagonal A1G7
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> a1g7[] = {
        {libataxx::Bitboard::Empty(), libataxx::Bitboard::Empty()},
        {libataxx::Bitboard::all(), libataxx::Bitboard::all()},
        {libataxx::Bitboard::FileA(), libataxx::Bitboard::Rank1()},
        {libataxx::Bitboard::FileB(), libataxx::Bitboard::Rank2()},
        {libataxx::Bitboard::FileC(), libataxx::Bitboard::Rank3()},
        {libataxx::Bitboard::FileD(), libataxx::Bitboard::Rank4()},
        {libataxx::Bitboard::FileE(), libataxx::Bitboard::Rank5()},
        {libataxx::Bitboard::FileF(), libataxx::Bitboard::Rank6()},
        {libataxx::Bitboard::FileG(), libataxx::Bitboard::Rank7()},
        {libataxx::Bitboard{libataxx::Squares::B6},
         libataxx::Bitboard{libataxx::Squares::F2}},
    };
    for (const auto& [bb1, bb2] : a1g7) {
        REQUIRE(bb1.flip_diagA1G7() == bb2);
    }

    // Rotate 90 clockwise
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> rot90[] = {
        {libataxx::Bitboard::Empty(), libataxx::Bitboard::Empty()},
        {libataxx::Bitboard::all(), libataxx::Bitboard::all()},
        {libataxx::Bitboard::FileA(), libataxx::Bitboard::Rank7()},
        {libataxx::Bitboard::FileB(), libataxx::Bitboard::Rank6()},
        {libataxx::Bitboard::FileC(), libataxx::Bitboard::Rank5()},
        {libataxx::Bitboard::FileD(), libataxx::Bitboard::Rank4()},
        {libataxx::Bitboard::FileE(), libataxx::Bitboard::Rank3()},
        {libataxx::Bitboard::FileF(), libataxx::Bitboard::Rank2()},
        {libataxx::Bitboard::FileG(), libataxx::Bitboard::Rank1()},
        {libataxx::Bitboard{libataxx::Squares::B2},
         libataxx::Bitboard{libataxx::Squares::B6}},
    };
    for (const auto& [bb1, bb2] : rot90) {
        REQUIRE(bb1.rot90() == bb2);
    }

    // Rotate 180 clockwise
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> rot180[] = {
        {libataxx::Bitboard::Empty(), libataxx::Bitboard::Empty()},
        {libataxx::Bitboard::all(), libataxx::Bitboard::all()},
        {libataxx::Bitboard::FileA(), libataxx::Bitboard::FileG()},
        {libataxx::Bitboard::FileB(), libataxx::Bitboard::FileF()},
        {libataxx::Bitboard::FileC(), libataxx::Bitboard::FileE()},
        {libataxx::Bitboard::FileD(), libataxx::Bitboard::FileD()},
        {libataxx::Bitboard::FileE(), libataxx::Bitboard::FileC()},
        {libataxx::Bitboard::FileF(), libataxx::Bitboard::FileB()},
        {libataxx::Bitboard::FileG(), libataxx::Bitboard::FileA()},
        {libataxx::Bitboard{libataxx::Squares::B2},
         libataxx::Bitboard{libataxx::Squares::F6}},
    };
    for (const auto& [bb1, bb2] : rot180) {
        REQUIRE(bb1.rot90().rot90() == bb2);
        REQUIRE(bb1.rot180() == bb2);
    }

    // Rotate 270 clockwise
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> rot270[] = {
        {libataxx::Bitboard::Empty(), libataxx::Bitboard::Empty()},
        {libataxx::Bitboard::all(), libataxx::Bitboard::all()},
        {libataxx::Bitboard::FileA(), libataxx::Bitboard::Rank1()},
        {libataxx::Bitboard::FileB(), libataxx::Bitboard::Rank2()},
        {libataxx::Bitboard::FileC(), libataxx::Bitboard::Rank3()},
        {libataxx::Bitboard::FileD(), libataxx::Bitboard::Rank4()},
        {libataxx::Bitboard::FileE(), libataxx::Bitboard::Rank5()},
        {libataxx::Bitboard::FileF(), libataxx::Bitboard::Rank6()},
        {libataxx::Bitboard::FileG(), libataxx::Bitboard::Rank7()},
        {libataxx::Bitboard{libataxx::Squares::B2},
         libataxx::Bitboard{libataxx::Squares::F2}},
    };
    for (const auto& [bb1, bb2] : rot270) {
        REQUIRE(bb1.rot90().rot90().rot90() == bb2);
        REQUIRE(bb1.rot270() == bb2);
    }

    // Same
    const libataxx::Bitboard same[] = {
        libataxx::Bitboard::Empty(),
        libataxx::Bitboard::all(),
        libataxx::Bitboard::FileA(),
        libataxx::Bitboard::FileB(),
        libataxx::Bitboard::FileC(),
        libataxx::Bitboard::FileD(),
        libataxx::Bitboard::FileE(),
        libataxx::Bitboard::FileF(),
        libataxx::Bitboard::FileG(),
        libataxx::Bitboard{libataxx::Squares::B2},
        libataxx::Bitboard{libataxx::Squares::B6},
        libataxx::Bitboard{libataxx::Squares::F2},
        libataxx::Bitboard{libataxx::Squares::B6},
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