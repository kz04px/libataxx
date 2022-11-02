#include "libataxx/bitboard.hpp"
#include "libataxx/move.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] bool Position::is_pseudolegal_move(const Move &move) const noexcept {
    assert(move != Move::nomove());

    if (move == Move::nullmove()) {
        return must_pass();
    }

    const Square from = move.from();
    const Square to = move.to();
    const Bitboard filled = get_black() | get_white() | get_gaps();

    // Make sure the destination square is empty
    if (Bitboard{to} & filled) {
        return false;
    }

    // Single moves
    if (move.type() == Move::Type::Single) {
        return Bitboard{to}.singles() & get_us();
    }

    // Double moves
    return Bitboard{to}.doubles() & get_us() & Bitboard{from};
}

[[nodiscard]] bool Position::is_legal_move(const Move &move) const noexcept {
    assert(move != Move::nomove());

    if (is_gameover()) {
        return false;
    }

    return is_pseudolegal_move(move);
}

}  // namespace libataxx
