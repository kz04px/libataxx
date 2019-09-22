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
    Bitboard singles = pieces_[static_cast<int>(turn_)].singles() & empty();
    for (const auto &bb : singles) {
        const Square to{bb.lsbll()};
        movelist[num_moves] = Move(to);
        num_moves++;
    }

    // Double moves
    Bitboard copy = pieces_[static_cast<int>(turn_)];
    for (const auto &from : copy) {
        Bitboard destinations = from.doubles() & empty();
        const Square fromsq{from.lsbll()};
        for (const auto &to : destinations) {
            const Square tosq{to.lsbll()};
            movelist[num_moves] = Move(fromsq, tosq);
            num_moves++;
        }
    }

    if (num_moves == 0) {
        movelist[0] = Move::nullmove();
        num_moves++;
    }

    return num_moves;
}

}  // namespace libataxx
