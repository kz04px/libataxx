#include <sstream>
#include <string>
#include "libataxx/position.hpp"

namespace libataxx {

void Position::set_fen(const std::string &fen) noexcept {
    if (fen == "startpos") {
        return set_fen("x5o/7/7/7/7/7/o5x x 0 1");
    }

    // Clear board
    pieces_[static_cast<int>(Side::Black)].clear();
    pieces_[static_cast<int>(Side::White)].clear();
    gaps_.clear();
    halfmoves_ = 0;
    fullmoves_ = 1;
    turn_ = Side::Black;

    std::stringstream ss{fen};
    std::string word;
    int y = 6;
    int x = 0;

    // Position
    if (ss >> word) {
        for (const auto &c : word) {
            const auto f = File{x};
            const auto r = Rank{y};
            const auto sq = Square{f, r};
            const auto bb = Bitboard{sq};

            switch (c) {
                case 'x':
                case 'X':
                case 'b':
                case 'B':
                    pieces_[static_cast<int>(Side::Black)] ^= bb;
                    x++;
                    break;
                case 'o':
                case 'O':
                case 'w':
                case 'W':
                    pieces_[static_cast<int>(Side::White)] ^= bb;
                    x++;
                    break;
                case '-':
                    gaps_ ^= bb;
                    x++;
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    x += c - '0';
                    break;
                case '/':
                    break;
                default:
                    return;
            }

            if (x > 6) {
                x = 0;
                y--;
            }
        }
    }

    // Turn
    if (ss >> word) {
        if (word == "b" || word == "B" || word == "x" || word == "X") {
            turn_ = Side::Black;
        } else {
            turn_ = Side::White;
        }
    }

    // Halfmove clock
    ss >> halfmoves_;

    // Fullmove counter
    ss >> fullmoves_;

    // Calculate initial hash
    hash_ = calculate_hash();
}

}  // namespace libataxx
