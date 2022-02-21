#include <iostream>
#include <libataxx/pgn.hpp>
#include <sstream>
#include <string>
#include "catch.hpp"

const std::string expected =
    "[Event \"PGN Test\"]\n"
    "[FEN \"x5o/7/7/7/7/7/o5x x 0 1\"]\n"
    "[White \"PlayerWhite\"]\n"
    "[Black \"PlayerBlack\"]\n"
    "[Result \"*\"]\n"
    "\n"
    "1. g2 { Test comment } 1... a2 2. g3 a3 (2... b2 { Alternate line } 3. "
    "g4 a3 { done }) 3. g4 *\n"
    "\n";

TEST_CASE("PGN") {
    libataxx::pgn::PGN pgn;
    pgn.header().add("Event", "PGN Test");
    pgn.header().add("FEN", "x5o/7/7/7/7/7/o5x x 0 1");
    pgn.header().add("White", "PlayerWhite");
    pgn.header().add("Black", "PlayerBlack");
    pgn.header().add("Result", "*");

    auto *node = pgn.root();

    node = node->add_mainline(libataxx::Move::from_uai("g2"));
    node->add_comment("Test comment");
    node = node->add_mainline(libataxx::Move::from_uai("a2"));
    node = node->add_mainline(libataxx::Move::from_uai("g3"));
    node = node->add_mainline(libataxx::Move::from_uai("a3"));
    auto *altnode = node->add_variation(libataxx::Move::from_uai("b2"));
    altnode->add_comment("Alternate line");
    altnode = altnode->add_mainline(libataxx::Move::from_uai("g4"));
    altnode = altnode->add_mainline(libataxx::Move::from_uai("a3"));
    altnode->add_comment("done");
    node->add_mainline(libataxx::Move::from_uai("g4"));

    std::stringstream ss;
    ss << pgn;

    REQUIRE(ss.str() == expected);
}
