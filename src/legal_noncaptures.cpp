#include <cassert>
#include "libataxx/move.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] int Position::legal_noncaptures(Move *movelist) const noexcept {
    assert(movelist);

    if (is_gameover()) {
        return 0;
    }

    if (must_pass()) {
        movelist[0] = Move::nullmove();
        return 1;
    }

    int num_moves = 0;

    const Bitboard allowed = ~(get_them().singles()) & get_empty();

    // Single moves
    const auto singles = get_us().singles() & allowed;
    for (const auto &to : singles) {
        movelist[num_moves] = Move(to);
        num_moves++;
    }

    // Double moves
    for (const auto &from : get_us()) {
        const auto destinations = Bitboard{from}.doubles() & allowed;
        for (const auto &to : destinations) {
            movelist[num_moves] = Move(from, to);
            num_moves++;
        }
    }

    return num_moves;
}

}  // namespace libataxx
