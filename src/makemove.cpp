#include "libataxx/move.hpp"
#include "libataxx/position.hpp"
#include "libataxx/zobrist.hpp"

namespace libataxx {

void Position::makemove(const Move &move) noexcept {
    assert(move != Move::nomove());

    // Increment halfmove clock
    halfmoves_++;

    // Increment fullmove counter after player 2 moves
    fullmoves_ += (turn() == Side::White);

    // Update hash -- turn
    hash_ ^= zobrist::turn_key();

    // Handle nullmove
    if (move == Move::nullmove()) {
        turn_ = !turn();
        return;
    }

    const Square to = move.to();
    const Square from = move.from();
    const Bitboard to_bb = Bitboard(to);
    const Bitboard from_bb = Bitboard(from);
    const Bitboard neighbours = to_bb.singles();
    const Bitboard captured = neighbours & them();

    // Remove and replace our stone
    pieces_[static_cast<int>(turn())] ^= from_bb | to_bb;

    // Flip any captured stones
    pieces_[static_cast<int>(!turn())] ^= captured;
    pieces_[static_cast<int>(turn())] ^= captured;

    // Update hash -- our pieces
    for (const auto &sq : from_bb | to_bb) {
        hash_ ^= zobrist::get_key(turn(), sq);
    }

    // Update hash -- captured pieces
    for (const auto &sq : captured) {
        hash_ ^= zobrist::get_key(!turn(), sq);
        hash_ ^= zobrist::get_key(turn(), sq);
    }

    // Reset halfmove clock on single moves
    if (move.type() == Move::Type::Single) {
        halfmoves_ = 0;
    }

    turn_ = !turn();
}

}  // namespace libataxx
