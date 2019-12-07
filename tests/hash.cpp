#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

std::uint64_t nodes = 0;
std::uint64_t chunks[8][256] = {};

void test(const libataxx::Position &pos, const int depth) {
    REQUIRE(pos.hash());
    REQUIRE(pos.hash() == pos.calculate_hash());

    // Track hash distribution
    nodes++;
    for (int i = 0; i < 8; ++i) {
        chunks[i][(pos.hash() >> (64 - 8 * i + 8)) & 0xFF]++;
    }

    if (depth == 0) {
        return;
    }

    libataxx::Move moves[libataxx::max_moves];
    const int num_moves = pos.legal_moves(moves);

    for (int i = 0; i < num_moves; ++i) {
        auto npos = pos;
        npos.makemove(moves[i]);
        REQUIRE(npos.hash() != pos.hash());
        REQUIRE(npos.hash() == pos.predict_hash(moves[i]));
        test(npos, depth - 1);
    }
}

TEST_CASE("Move::hash()") {
    const std::string fens[] = {
        "x5o/7/7/7/7/7/o5x x 0 1",
        "x5o/7/2-1-2/7/2-1-2/7/o5x x 0 1",
        "x5o/7/3-3/2-1-2/3-3/7/o5x x 0 1",
        "7/7/7/7/4ooo/4ooo/4oox x 0 1",
        "7/7/7/7/4ooo/4ooo/4oox o 0 1",
        "7/7/7/7/4xxx/4xxx/4xxo x 0 1",
        "7/7/7/7/4xxx/4xxx/4xxo o 0 1",
        "7/7/2x1o2/2x1o2/2x1o2/7/7 x 0 1",
        "7/7/2x1o2/2x1o2/2x1o2/7/7 o 0 1",
    };

    for (const auto &fen : fens) {
        libataxx::Position pos{fen};
        test(pos, 4);
    }

    // Test hash distribution
    const uint64_t expected = nodes / 256;
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
