#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] bool Position::is_gameover() const noexcept {
    const Bitboard both = get_black() | get_white();
    const Bitboard moves = both.singles().singles();

    // No black pieces left
    if (!get_black()) {
        return true;
    }

    // No white pieces left
    if (!get_white()) {
        return true;
    }

    // Halfmove clock
    if (get_halfmoves() >= 100) {
        return true;
    }

    // Legal moves left
    if (moves & get_empty()) {
        return false;
    }

    return true;
}

}  // namespace libataxx
