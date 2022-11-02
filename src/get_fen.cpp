#include <string>
#include "libataxx/bitboard.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] std::string Position::get_fen() const noexcept {
    std::string fen;

    // Board
    for (int y = 6; y >= 0; --y) {
        int empty = 0;

        for (int x = 0; x < 7; ++x) {
            const auto f = File{x};
            const auto r = Rank{y};
            const auto sq = Square{f, r};
            const auto bb = Bitboard{sq};

            if (bb & get_black()) {
                if (empty > 0) {
                    fen += std::to_string(empty);
                    empty = 0;
                }
                fen += "x";
            } else if (bb & get_white()) {
                if (empty > 0) {
                    fen += std::to_string(empty);
                    empty = 0;
                }
                fen += "o";
            } else if (bb & get_gaps()) {
                if (empty > 0) {
                    fen += std::to_string(empty);
                    empty = 0;
                }
                fen += "-";
            } else {
                empty += 1;
            }
        }

        if (empty > 0) {
            fen += std::to_string(empty);
        }
        if (y > 0) {
            fen += "/";
        }
    }

    // Turn
    if (get_turn() == Side::Black) {
        fen += " x";
    } else {
        fen += " o";
    }

    // Halfmove clock
    fen += " " + std::to_string(halfmoves_);

    // Fullmove number
    fen += " " + std::to_string(fullmoves_);

    return fen;
}

}  // namespace libataxx
