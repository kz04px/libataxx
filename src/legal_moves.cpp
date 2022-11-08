#include "libataxx/libataxx.hpp"
#include "libataxx/lookup.hpp"
#include "libataxx/move.hpp"

namespace libataxx {

[[nodiscard]] int Position::pseudolegal_moves(Move *movelist) const noexcept {
    int num_moves = 0;

    // Single moves
    const Bitboard singles = get_us().singles() & get_empty();
    for (const auto &to : singles) {
        movelist[num_moves] = Move(to);
        num_moves++;
    }

    // Double moves
    for (const auto &from : get_us()) {
        const Bitboard destinations = lut::get_doubles(from) & get_empty();
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

[[nodiscard]] std::vector<Move> Position::pseudolegal_moves() const noexcept {
    std::vector<Move> moves;

    // Single moves
    const Bitboard singles = get_us().singles() & get_empty();
    for (const auto &to : singles) {
        moves.emplace_back(to);
    }

    // Double moves
    for (const auto &from : get_us()) {
        const Bitboard destinations = lut::get_doubles(from) & get_empty();
        for (const auto &to : destinations) {
            moves.emplace_back(from, to);
        }
    }

    if (moves.empty()) {
        moves.push_back(Move::nullmove());
    }

    return moves;
}

[[nodiscard]] int Position::legal_moves(Move *movelist) const noexcept {
    assert(movelist);

    if (is_gameover()) {
        return 0;
    }

    return pseudolegal_moves(movelist);
}

[[nodiscard]] std::vector<Move> Position::legal_moves() const noexcept {
    if (is_gameover()) {
        return {};
    }

    return pseudolegal_moves();
}

}  // namespace libataxx
