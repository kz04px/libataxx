#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] bool Position::is_gameover() const noexcept {
    const Bitboard both = black() | white();
    const Bitboard moves = both.singles().singles();

    // No black pieces left
    if (!black()) {
        return true;
    }

    // No white pieces left
    if (!white()) {
        return true;
    }

    // Halfmove clock
    if (halfmoves() >= 100) {
        return true;
    }

    // Legal moves left
    if (moves & empty()) {
        return false;
    }

    return true;
}

}  // namespace libataxx
