#include <libataxx/bitboard.hpp>
#include "catch.hpp"

TEST_CASE("flip_horizontal()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::Bitboard(libataxx::Bitmask::Empty), libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {libataxx::Bitboard(libataxx::Bitmask::All), libataxx::Bitboard(libataxx::Bitmask::All)},
        {libataxx::Bitboard(libataxx::Bitmask::FileA), libataxx::Bitboard(libataxx::Bitmask::FileG)},
        {libataxx::Bitboard(libataxx::Bitmask::FileB), libataxx::Bitboard(libataxx::Bitmask::FileF)},
        {libataxx::Bitboard(libataxx::Bitmask::FileC), libataxx::Bitboard(libataxx::Bitmask::FileE)},
        {libataxx::Bitboard(libataxx::Bitmask::FileD), libataxx::Bitboard(libataxx::Bitmask::FileD)},
        {libataxx::Bitboard(libataxx::Bitmask::FileE), libataxx::Bitboard(libataxx::Bitmask::FileC)},
        {libataxx::Bitboard(libataxx::Bitmask::FileF), libataxx::Bitboard(libataxx::Bitmask::FileB)},
        {libataxx::Bitboard(libataxx::Bitmask::FileG), libataxx::Bitboard(libataxx::Bitmask::FileA)},
        {libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::F2}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_horizontal() == bb2);
    }
}

TEST_CASE("flip_vertical()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::Bitboard(libataxx::Bitmask::Empty), libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {libataxx::Bitboard(libataxx::Bitmask::All), libataxx::Bitboard(libataxx::Bitmask::All)},
        {libataxx::Bitboard(libataxx::Bitmask::FileA), libataxx::Bitboard(libataxx::Bitmask::FileA)},
        {libataxx::Bitboard(libataxx::Bitmask::FileB), libataxx::Bitboard(libataxx::Bitmask::FileB)},
        {libataxx::Bitboard(libataxx::Bitmask::FileC), libataxx::Bitboard(libataxx::Bitmask::FileC)},
        {libataxx::Bitboard(libataxx::Bitmask::FileD), libataxx::Bitboard(libataxx::Bitmask::FileD)},
        {libataxx::Bitboard(libataxx::Bitmask::FileE), libataxx::Bitboard(libataxx::Bitmask::FileE)},
        {libataxx::Bitboard(libataxx::Bitmask::FileF), libataxx::Bitboard(libataxx::Bitmask::FileF)},
        {libataxx::Bitboard(libataxx::Bitmask::FileG), libataxx::Bitboard(libataxx::Bitmask::FileG)},
        {libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::B6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_vertical() == bb2);
    }
}

TEST_CASE("flip_diagA7G1()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::Bitboard(libataxx::Bitmask::Empty), libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {libataxx::Bitboard(libataxx::Bitmask::All), libataxx::Bitboard(libataxx::Bitmask::All)},
        {libataxx::Bitboard(libataxx::Bitmask::FileA), libataxx::Bitboard(libataxx::Bitmask::Rank7)},
        {libataxx::Bitboard(libataxx::Bitmask::FileB), libataxx::Bitboard(libataxx::Bitmask::Rank6)},
        {libataxx::Bitboard(libataxx::Bitmask::FileC), libataxx::Bitboard(libataxx::Bitmask::Rank5)},
        {libataxx::Bitboard(libataxx::Bitmask::FileD), libataxx::Bitboard(libataxx::Bitmask::Rank4)},
        {libataxx::Bitboard(libataxx::Bitmask::FileE), libataxx::Bitboard(libataxx::Bitmask::Rank3)},
        {libataxx::Bitboard(libataxx::Bitmask::FileF), libataxx::Bitboard(libataxx::Bitmask::Rank2)},
        {libataxx::Bitboard(libataxx::Bitmask::FileG), libataxx::Bitboard(libataxx::Bitmask::Rank1)},
        {libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::F6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_diagA7G1() == bb2);
    }
}

TEST_CASE("flip_diagA1G7()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::Bitboard(libataxx::Bitmask::Empty), libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {libataxx::Bitboard(libataxx::Bitmask::All), libataxx::Bitboard(libataxx::Bitmask::All)},
        {libataxx::Bitboard(libataxx::Bitmask::FileA), libataxx::Bitboard(libataxx::Bitmask::Rank1)},
        {libataxx::Bitboard(libataxx::Bitmask::FileB), libataxx::Bitboard(libataxx::Bitmask::Rank2)},
        {libataxx::Bitboard(libataxx::Bitmask::FileC), libataxx::Bitboard(libataxx::Bitmask::Rank3)},
        {libataxx::Bitboard(libataxx::Bitmask::FileD), libataxx::Bitboard(libataxx::Bitmask::Rank4)},
        {libataxx::Bitboard(libataxx::Bitmask::FileE), libataxx::Bitboard(libataxx::Bitmask::Rank5)},
        {libataxx::Bitboard(libataxx::Bitmask::FileF), libataxx::Bitboard(libataxx::Bitmask::Rank6)},
        {libataxx::Bitboard(libataxx::Bitmask::FileG), libataxx::Bitboard(libataxx::Bitmask::Rank7)},
        {libataxx::Bitboard{libataxx::SquareIndex::B6}, libataxx::Bitboard{libataxx::SquareIndex::F2}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.flip_diagA1G7() == bb2);
    }
}

TEST_CASE("rot90()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::Bitboard(libataxx::Bitmask::Empty), libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {libataxx::Bitboard(libataxx::Bitmask::All), libataxx::Bitboard(libataxx::Bitmask::All)},
        {libataxx::Bitboard(libataxx::Bitmask::FileA), libataxx::Bitboard(libataxx::Bitmask::Rank7)},
        {libataxx::Bitboard(libataxx::Bitmask::FileB), libataxx::Bitboard(libataxx::Bitmask::Rank6)},
        {libataxx::Bitboard(libataxx::Bitmask::FileC), libataxx::Bitboard(libataxx::Bitmask::Rank5)},
        {libataxx::Bitboard(libataxx::Bitmask::FileD), libataxx::Bitboard(libataxx::Bitmask::Rank4)},
        {libataxx::Bitboard(libataxx::Bitmask::FileE), libataxx::Bitboard(libataxx::Bitmask::Rank3)},
        {libataxx::Bitboard(libataxx::Bitmask::FileF), libataxx::Bitboard(libataxx::Bitmask::Rank2)},
        {libataxx::Bitboard(libataxx::Bitmask::FileG), libataxx::Bitboard(libataxx::Bitmask::Rank1)},
        {libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::B6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.rot90() == bb2);
    }
}

TEST_CASE("rot180()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::Bitboard(libataxx::Bitmask::Empty), libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {libataxx::Bitboard(libataxx::Bitmask::All), libataxx::Bitboard(libataxx::Bitmask::All)},
        {libataxx::Bitboard(libataxx::Bitmask::FileA), libataxx::Bitboard(libataxx::Bitmask::FileG)},
        {libataxx::Bitboard(libataxx::Bitmask::FileB), libataxx::Bitboard(libataxx::Bitmask::FileF)},
        {libataxx::Bitboard(libataxx::Bitmask::FileC), libataxx::Bitboard(libataxx::Bitmask::FileE)},
        {libataxx::Bitboard(libataxx::Bitmask::FileD), libataxx::Bitboard(libataxx::Bitmask::FileD)},
        {libataxx::Bitboard(libataxx::Bitmask::FileE), libataxx::Bitboard(libataxx::Bitmask::FileC)},
        {libataxx::Bitboard(libataxx::Bitmask::FileF), libataxx::Bitboard(libataxx::Bitmask::FileB)},
        {libataxx::Bitboard(libataxx::Bitmask::FileG), libataxx::Bitboard(libataxx::Bitmask::FileA)},
        {libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::F6}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.rot180() == bb2);
    }
}

TEST_CASE("rot270()") {
    const std::pair<libataxx::Bitboard, libataxx::Bitboard> bitboards[] = {
        {libataxx::Bitboard(libataxx::Bitmask::Empty), libataxx::Bitboard(libataxx::Bitmask::Empty)},
        {libataxx::Bitboard(libataxx::Bitmask::All), libataxx::Bitboard(libataxx::Bitmask::All)},
        {libataxx::Bitboard(libataxx::Bitmask::FileA), libataxx::Bitboard(libataxx::Bitmask::Rank1)},
        {libataxx::Bitboard(libataxx::Bitmask::FileB), libataxx::Bitboard(libataxx::Bitmask::Rank2)},
        {libataxx::Bitboard(libataxx::Bitmask::FileC), libataxx::Bitboard(libataxx::Bitmask::Rank3)},
        {libataxx::Bitboard(libataxx::Bitmask::FileD), libataxx::Bitboard(libataxx::Bitmask::Rank4)},
        {libataxx::Bitboard(libataxx::Bitmask::FileE), libataxx::Bitboard(libataxx::Bitmask::Rank5)},
        {libataxx::Bitboard(libataxx::Bitmask::FileF), libataxx::Bitboard(libataxx::Bitmask::Rank6)},
        {libataxx::Bitboard(libataxx::Bitmask::FileG), libataxx::Bitboard(libataxx::Bitmask::Rank7)},
        {libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::F2}},
    };
    for (const auto& [bb1, bb2] : bitboards) {
        REQUIRE(bb1.rot270() == bb2);
    }
}

TEST_CASE("identity") {
    const libataxx::Bitboard bitboards[] = {
        libataxx::Bitboard(libataxx::Bitmask::Empty),  libataxx::Bitboard(libataxx::Bitmask::All),
        libataxx::Bitboard(libataxx::Bitmask::Edge),   libataxx::Bitboard(libataxx::Bitmask::Center),
        libataxx::Bitboard(libataxx::Bitmask::FileA),  libataxx::Bitboard(libataxx::Bitmask::FileB),
        libataxx::Bitboard(libataxx::Bitmask::FileC),  libataxx::Bitboard(libataxx::Bitmask::FileD),
        libataxx::Bitboard(libataxx::Bitmask::FileE),  libataxx::Bitboard(libataxx::Bitmask::FileF),
        libataxx::Bitboard(libataxx::Bitmask::FileG),  libataxx::Bitboard(libataxx::Bitmask::Rank1),
        libataxx::Bitboard(libataxx::Bitmask::Rank2),  libataxx::Bitboard(libataxx::Bitmask::Rank3),
        libataxx::Bitboard(libataxx::Bitmask::Rank4),  libataxx::Bitboard(libataxx::Bitmask::Rank5),
        libataxx::Bitboard(libataxx::Bitmask::Rank6),  libataxx::Bitboard(libataxx::Bitmask::Rank7),
        libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::B6},
        libataxx::Bitboard{libataxx::SquareIndex::F2}, libataxx::Bitboard{libataxx::SquareIndex::B6},
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
        libataxx::Bitboard(libataxx::Bitmask::Empty),  libataxx::Bitboard(libataxx::Bitmask::All),
        libataxx::Bitboard(libataxx::Bitmask::Edge),   libataxx::Bitboard(libataxx::Bitmask::Center),
        libataxx::Bitboard(libataxx::Bitmask::FileA),  libataxx::Bitboard(libataxx::Bitmask::FileB),
        libataxx::Bitboard(libataxx::Bitmask::FileC),  libataxx::Bitboard(libataxx::Bitmask::FileD),
        libataxx::Bitboard(libataxx::Bitmask::FileE),  libataxx::Bitboard(libataxx::Bitmask::FileF),
        libataxx::Bitboard(libataxx::Bitmask::FileG),  libataxx::Bitboard(libataxx::Bitmask::Rank1),
        libataxx::Bitboard(libataxx::Bitmask::Rank2),  libataxx::Bitboard(libataxx::Bitmask::Rank3),
        libataxx::Bitboard(libataxx::Bitmask::Rank4),  libataxx::Bitboard(libataxx::Bitmask::Rank5),
        libataxx::Bitboard(libataxx::Bitmask::Rank6),  libataxx::Bitboard(libataxx::Bitmask::Rank7),
        libataxx::Bitboard{libataxx::SquareIndex::B2}, libataxx::Bitboard{libataxx::SquareIndex::B6},
        libataxx::Bitboard{libataxx::SquareIndex::F2}, libataxx::Bitboard{libataxx::SquareIndex::B6},
    };
    for (const auto& bb : bitboards) {
        REQUIRE(bb.rot90().rot90() == bb.rot180());
        REQUIRE(bb.rot90().rot90().rot90() == bb.rot270());
        REQUIRE(bb.rot180().rot90() == bb.rot270());
        REQUIRE(bb.rot90().rot180() == bb.rot270());
    }
}
