#include "libataxx/position.hpp"
#include "libataxx/zobrist.hpp"

namespace libataxx {

[[nodiscard]] std::uint64_t Position::calculate_hash() const noexcept {
    std::uint64_t key = 0ULL;

    if (turn() == Side::Black) {
        key ^= zobrist::turn_key();
    }

    for (const auto &sq : black()) {
        key ^= zobrist::get_key(Piece::Black, sq);
    }

    for (const auto &sq : white()) {
        key ^= zobrist::get_key(Piece::White, sq);
    }

    for (const auto &sq : gaps()) {
        key ^= zobrist::get_key(Piece::Gap, sq);
    }

    return key;
}

}  // namespace libataxx
