#include <cstdint>
#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::perft()") {
    const std::pair<std::string, std::uint64_t> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0", 155888},
        {"x5o/7/2-1-2/7/2-1-2/7/o5x x 0", 86528},
        {"x5o/7/3-3/2-1-2/3-3/7/o5x x 0", 133264},
    };

    for (const auto& [fen, nodes] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.perft(4) == nodes);
    }
}
