#include <sstream>
#include <string>
#include "libataxx/position.hpp"

namespace libataxx {

void Position::set_fen(const std::string &fen) noexcept {
    if (fen == "startpos") {
        return set_fen("x5o/7/7/7/7/7/o5x x");
    }

    // Clear board
    pieces_[static_cast<int>(Side::Black)].clear();
    pieces_[static_cast<int>(Side::White)].clear();
    gaps_.clear();
    turn_ = Side::Black;

    std::stringstream ss{fen};
    std::string word;
    int sq = 42;

    // Position
    if (ss >> word) {
        for (const auto &c : word) {
            switch (c) {
                case 'x':
                case 'X':
                case 'b':
                case 'B':
                    pieces_[static_cast<int>(Side::Black)] ^=
                        Bitboard(Square{sq});
                    sq++;
                    break;
                case 'o':
                case 'O':
                case 'w':
                case 'W':
                    pieces_[static_cast<int>(Side::White)] ^=
                        Bitboard(Square{sq});
                    sq++;
                    break;
                case '-':
                    gaps_ ^= Bitboard(Square{sq});
                    sq++;
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    sq += c - '0';
                    break;
                case '/':
                    sq -= 14;
                    break;
                default:
                    return;
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
}

}  // namespace libataxx
