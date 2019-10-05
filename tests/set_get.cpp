#include <libataxx/position.hpp>
#include "catch.hpp"

TEST_CASE("Position::set() Position::get()") {
    libataxx::Position pos;

    pos.set_fen("7/7/7/7/7/7/7 x 0");
    for (const auto &sq : libataxx::Bitboard::all()) {
        REQUIRE(pos.get(sq) == libataxx::Piece::Empty);
        for (const auto &piece : {libataxx::Piece::Black,
                                  libataxx::Piece::White,
                                  libataxx::Piece::Gap,
                                  libataxx::Piece::Empty}) {
            pos.set(sq, piece);
            REQUIRE(pos.get(sq) == piece);
        }
    }

    pos.set_fen("xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx x 0");
    for (const auto &sq : libataxx::Bitboard::all()) {
        REQUIRE(pos.get(sq) == libataxx::Piece::Black);
        for (const auto &piece : {libataxx::Piece::Black,
                                  libataxx::Piece::White,
                                  libataxx::Piece::Gap,
                                  libataxx::Piece::Empty}) {
            pos.set(sq, piece);
            REQUIRE(pos.get(sq) == piece);
        }
    }

    pos.set_fen("ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo x 0");
    for (const auto &sq : libataxx::Bitboard::all()) {
        REQUIRE(pos.get(sq) == libataxx::Piece::White);
        for (const auto &piece : {libataxx::Piece::Black,
                                  libataxx::Piece::White,
                                  libataxx::Piece::Gap,
                                  libataxx::Piece::Empty}) {
            pos.set(sq, piece);
            REQUIRE(pos.get(sq) == piece);
        }
    }

    pos.set_fen("-------/-------/-------/-------/-------/-------/------- x 0");
    for (const auto &sq : libataxx::Bitboard::all()) {
        REQUIRE(pos.get(sq) == libataxx::Piece::Gap);
        for (const auto &piece : {libataxx::Piece::Black,
                                  libataxx::Piece::White,
                                  libataxx::Piece::Gap,
                                  libataxx::Piece::Empty}) {
            pos.set(sq, piece);
            REQUIRE(pos.get(sq) == piece);
        }
    }
}
