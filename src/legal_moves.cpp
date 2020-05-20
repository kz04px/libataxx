#include "libataxx/libataxx.hpp"
#include "libataxx/move.hpp"

namespace libataxx {

[[nodiscard]] int Position::legal_moves(Move *movelist) const noexcept {
    assert(movelist);

    if (gameover()) {
        return 0;
    }

    int num_moves = 0;

    // Single moves
    const Bitboard singles = us().singles() & empty();
    for (const auto &to : singles) {
        movelist[num_moves] = Move(to);
        num_moves++;
    }

    // Double moves
    for (const auto &from : us()) {
        const Bitboard destinations = Bitboard{from}.doubles() & empty();
        for (const auto &to : destinations) {
            movelist[num_moves] = Move(from, to);
            num_moves++;
        }
    }

    if (num_moves == 0) {
        movelist[0] = Move::nullmove();
        num_moves++;
    }

    return num_moves;
}

[[nodiscard]] std::vector<Move> Position::legal_moves() const noexcept {
    if (gameover()) {
        return {};
    }

    std::vector<Move> moves;

    // Single moves
    const Bitboard singles = us().singles() & empty();
    for (const auto &to : singles) {
        moves.emplace_back(to);
    }

    // Double moves
    for (const auto &from : us()) {
        const Bitboard destinations = Bitboard{from}.doubles() & empty();
        for (const auto &to : destinations) {
            moves.emplace_back(from, to);
        }
    }

    if (moves.empty()) {
        moves.push_back(Move::nullmove());
    }

    return moves;
}

}  // namespace libataxx
