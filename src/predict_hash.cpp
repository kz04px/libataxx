#include "libataxx/move.hpp"
#include "libataxx/position.hpp"
#include "libataxx/zobrist.hpp"

namespace libataxx {

std::uint64_t Position::predict_hash(const Move &move) const noexcept {
    assert(move != Move::nomove());

    auto hash = hash_;

    // Update hash -- turn
    hash ^= zobrist::turn_key();

    // Handle nullmove
    if (move == Move::nullmove()) {
        return hash;
    }

    const Square to = move.to();
    const Square from = move.from();
    const Bitboard to_bb = Bitboard(to);
    const Bitboard from_bb = Bitboard(from);
    const Bitboard neighbours = to_bb.singles();
    const Bitboard captured = neighbours & them();
    const Piece our_piece = turn() == Side::Black ? Piece::Black : Piece::White;
    const Piece their_piece =
        turn() == Side::Black ? Piece::White : Piece::Black;

    // Update hash -- our pieces
    for (const auto &sq : from_bb | to_bb) {
        hash ^= zobrist::get_key(our_piece, sq);
    }

    // Update hash -- captured pieces
    for (const auto &sq : captured) {
        hash ^= zobrist::get_key(their_piece, sq);
        hash ^= zobrist::get_key(our_piece, sq);
    }

    return hash;
}

}  // namespace libataxx
