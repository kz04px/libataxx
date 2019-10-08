#include "libataxx/libataxx.hpp"
#include "libataxx/move.hpp"

namespace libataxx {

[[nodiscard]] int Position::legal_captures(Move *movelist) const noexcept {
    assert(movelist);

    if (gameover()) {
        return 0;
    }

    int num_moves = 0;

    const Bitboard allowed = them().singles() & empty();

    // Single moves
    Bitboard singles = us().singles() & allowed;
    for (const auto &to : singles) {
        movelist[num_moves] = Move(to);
        num_moves++;
    }

    // Double moves
    for (const auto &from : us()) {
        Bitboard destinations = Bitboard{from}.doubles() & allowed;
        for (const auto &to : destinations) {
            movelist[num_moves] = Move(from, to);
            num_moves++;
        }
    }

    return num_moves;
}

}  // namespace libataxx
