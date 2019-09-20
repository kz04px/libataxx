#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] bool Position::gameover() const noexcept {
    const Bitboard both = pieces_[static_cast<int>(Side::Black)] |
                          pieces_[static_cast<int>(Side::White)];
    const Bitboard moves = both.singles().singles();

    // No black pieces left
    if (!pieces_[static_cast<int>(Side::Black)]) {
        return true;
    }

    // No white pieces left
    if (!pieces_[static_cast<int>(Side::White)]) {
        return true;
    }

    // Legal moves left
    if (moves & empty()) {
        return false;
    }

    return true;
}

}  // namespace libataxx
