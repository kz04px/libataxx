#include "libataxx/position.hpp"
#include "libataxx/zobrist.hpp"

namespace libataxx {

[[nodiscard]] std::uint64_t Position::calculate_hash() const noexcept {
    std::uint64_t key = 0ULL;

    if (turn_ == Side::Black) {
        key ^= zobrist::turn_key();
    }

    for (const auto &sq : pieces_[static_cast<int>(Side::Black)]) {
        key ^= zobrist::get_key(Side::Black, sq);
    }

    for (const auto &sq : pieces_[static_cast<int>(Side::White)]) {
        key ^= zobrist::get_key(Side::White, sq);
    }

    return key;
}

}  // namespace libataxx
