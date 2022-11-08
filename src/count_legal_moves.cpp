#include "libataxx/lookup.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] int Position::count_pseudolegal_moves() const noexcept {
    const Bitboard filled = get_black() | get_white() | get_gaps();
    const Bitboard empty = Bitboard(Bitmask::All) ^ filled;
    int num_moves = 0;

    // Single moves
    const Bitboard singles = get_us().singles() & empty;
    num_moves += singles.count();

    // Double moves
    for (const auto &sq : get_us()) {
        num_moves += (lut::get_doubles(sq) & empty).count();
    }

    // Nullmove
    if (num_moves == 0) {
        num_moves++;
    }

    return num_moves;
}

[[nodiscard]] int Position::count_legal_moves() const noexcept {
    if (is_gameover()) {
        return 0;
    }

    return count_pseudolegal_moves();
}

}  // namespace libataxx
