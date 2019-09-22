#include "libataxx/move.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

void Position::makemove(const Move &move) noexcept {
    if (move == Move::nullmove()) {
        turn_ = static_cast<Side>(!turn_);
        return;
    }

    const Side us = turn_;
    const Side them = static_cast<Side>(!us);
    const Square to = move.to();
    const Square from = move.from();
    const Bitboard to_bb = Bitboard(to);
    const Bitboard from_bb = Bitboard(from);
    const Bitboard neighbours = to_bb.singles();
    const Bitboard captured = neighbours & pieces_[static_cast<int>(them)];

    // Remove and replace our stone
    pieces_[static_cast<int>(us)] ^= from_bb | to_bb;

    // Flip any captured stones
    pieces_[static_cast<int>(them)] ^= captured;
    pieces_[static_cast<int>(us)] ^= captured;

    turn_ = them;
}

}  // namespace libataxx
