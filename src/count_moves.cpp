#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] std::uint64_t Position::count_moves() const noexcept {
    if (gameover()) {
        return 0;
    }

    const Bitboard filled = pieces_[static_cast<int>(Side::Black)] |
                            pieces_[static_cast<int>(Side::White)] | gaps_;
    const Bitboard empty = Bitboard::all() ^ filled;
    int num_moves = 0;

    // Single moves
    const Bitboard singles = pieces_[static_cast<int>(turn_)].singles() & empty;
    num_moves += singles.count();

    // Double moves
    Bitboard copy = pieces_[static_cast<int>(turn_)];
    for (const auto &bb : copy) {
        const Bitboard destinations = bb.doubles() & empty;
        num_moves += destinations.count();
    }

    // Nullmove
    if (num_moves == 0) {
        num_moves++;
    }

    return num_moves;
}

}  // namespace libataxx
