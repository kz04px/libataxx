#include <string>
#include "libataxx/bitboard.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] std::string Position::get_fen() const noexcept {
    std::string fen = "";
    int empty = 0;

    // Board
    int idx = 42;
    while (idx >= 0) {
        const auto sq = Square{idx};
        const Bitboard bb{sq};

        if (bb & pieces_[static_cast<int>(Side::Black)]) {
            if (empty) {
                fen += std::to_string(empty);
                empty = 0;
            }
            fen += "x";
        } else if (bb & pieces_[static_cast<int>(Side::White)]) {
            if (empty) {
                fen += std::to_string(empty);
                empty = 0;
            }
            fen += "o";
        } else if (bb & gaps_) {
            if (empty) {
                fen += std::to_string(empty);
                empty = 0;
            }
            fen += "-";
        } else {
            empty += 1;
        }

        if (sq.file() == files::G) {
            idx -= 14;
            if (empty) {
                fen += std::to_string(empty);
                empty = 0;
            }
            if (idx >= -1) {
                fen += "/";
            }
        }
        idx++;
    }

    // Turn
    if (turn_ == Side::Black) {
        fen += " x";
    } else {
        fen += " o";
    }

    // Halfmove clock
    fen += " " + std::to_string(halfmoves_);

    return fen;
}

}  // namespace libataxx
