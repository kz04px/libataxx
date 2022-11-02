#include <cstdint>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

std::uint64_t nodes = 0;
std::uint64_t chunks[8][256] = {};

void test(const libataxx::Position &pos, const int depth) {
    REQUIRE(pos.get_hash());
    REQUIRE(pos.get_hash() == pos.calculate_hash());

    // Track hash distribution
    nodes++;
    for (int i = 0; i < 8; ++i) {
        chunks[i][(pos.get_hash() >> (64 - (8 * i + 8))) & 0xFF]++;
    }

    if (depth == 0) {
        return;
    }

    libataxx::Move moves[libataxx::max_moves];
    const int num_moves = pos.legal_moves(moves);

    for (int i = 0; i < num_moves; ++i) {
        const auto npos = pos.after_move(moves[i]);
        REQUIRE(npos.get_hash() != pos.get_hash());
        REQUIRE(npos.get_hash() == pos.predict_hash(moves[i]));
        test(npos, depth - 1);
    }
}

TEST_CASE("Position::get_hash()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0 1",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0 1",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0 1",
        "3xx-1/-2ooxx/2oo1o1/1-xoo2/1-4o/x4-1/1x2xx1 x 0 1",
        "4o2/2x1o2/2x4/1o5/7/3o1oo/-x3-1 o 0 1",
        "4o-o/1xo1x2/2-2-1/6-/1o1xx2/2x4/4oo1 x 0 1",
        "6x/7/2x3x/o6/2-2oo/o3-2/-6 x 0 1",
        "2x4/5o1/4o2/1o3o1/1o5/7/5o1 x 0 1",
        "1oo1o2/7/7/3xo2/1x5/7/7 x 0 1",
        "o2o3/2o4/2-4/1x5/4o2/1-2x-1/5xo o 0 1",
        "5-o/2-1-2/xo5/x1o1-2/o5-/o1-o2x/x5- o 0 1",
        "x2x2-/x4o1/7/5x1/4-2/5x1/-2oxo1 o 0 1",
        "3xo2/4o2/2x2-1/3-ox1/xx5/6o/1x3o1 x 0 1",
        "---4/1o5/o-1ox2/x6/2xo3/4xx1/o3-o1 o 0 1",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        test(pos, 4);
    }

    // Test hash distribution
    const std::uint64_t expected = nodes / 256;
    for (int c = 0; c < 8; ++c) {
        for (int i = 0; i < 256; ++i) {
            if (chunks[c][i] >= expected) {
                REQUIRE(chunks[c][i] - expected < expected * 0.05);
            } else {
                REQUIRE(expected - chunks[c][i] < expected * 0.05);
            }
        }
    }
}
