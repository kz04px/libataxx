#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] int Position::count_moves() const noexcept {
    if (is_gameover()) {
        return 0;
    }

    const Bitboard filled = get_black() | get_white() | get_gaps();
    const Bitboard empty = Bitboard(Bitmask::All) ^ filled;
    int num_moves = 0;

    // Single moves
    const Bitboard singles = get_us().singles() & empty;
    num_moves += singles.count();

    // Double moves
    for (const auto &sq : get_us()) {
        const Bitboard destinations = Bitboard{sq}.doubles() & empty;
        num_moves += destinations.count();
    }

    // Nullmove
    if (num_moves == 0) {
        num_moves++;
    }

    return num_moves;
}

}  // namespace libataxx
