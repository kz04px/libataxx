#include "libataxx/bitboard.hpp"
#include "libataxx/move.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] bool Position::legal_move(const Move &move) const noexcept {
    assert(move != Move::nomove());

    if (move == Move::nullmove()) {
        return must_pass() && !gameover();
    }

    const Square from = move.from();
    const Square to = move.to();
    const Bitboard filled = black() | white() | gaps();

    // Make sure the destination square is empty
    if (Bitboard{to} & filled) {
        return false;
    }

    // Single moves
    if (move.type() == Move::Type::Single) {
        return Bitboard{to}.singles() & us();
    }

    // Double moves
    return Bitboard{to}.doubles() & us() & Bitboard{from};
}

}  // namespace libataxx
