#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] int Position::count_moves() const noexcept {
    if (gameover()) {
        return 0;
    }

    const Bitboard filled = black() | white() | gaps();
    const Bitboard empty = Bitboard::all() ^ filled;
    int num_moves = 0;

    // Single moves
    const Bitboard singles = us().singles() & empty;
    num_moves += singles.count();

    // Double moves
    for (const auto &sq : us()) {
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
