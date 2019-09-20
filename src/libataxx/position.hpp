#ifndef LIBATAXX_POSITION_HPP
#define LIBATAXX_POSITION_HPP

#include <cstdint>
#include <string>
#include "bitboard.hpp"
#include "piece.hpp"
#include "side.hpp"

namespace libataxx {

class Move;

class Position {
   public:
    constexpr Position()
        : pieces_{}, gaps_{}, halfmoves_{0}, turn_{Side::Black} {
    }

    constexpr Position(const std::string &fen)
        : pieces_{}, gaps_{}, halfmoves_{0}, turn_{Side::Black} {
        set_fen(fen);
    }

    void set_fen(const std::string &fen) noexcept;

    [[nodiscard]] std::string get_fen() const noexcept;

    [[nodiscard]] constexpr Side turn() const noexcept {
        return turn_;
    }

    [[nodiscard]] std::uint64_t perft(const int depth) const noexcept;

    [[nodiscard]] std::uint64_t count_moves() const noexcept;

    [[nodiscard]] int legal_moves(Move *movelist) const noexcept;

    [[nodiscard]] bool gameover() const noexcept;

    [[nodiscard]] constexpr Bitboard black() const noexcept {
        return pieces_[static_cast<int>(Side::Black)];
    }

    [[nodiscard]] constexpr Bitboard white() const noexcept {
        return pieces_[static_cast<int>(Side::White)];
    }

    void makemove(const Move &move) noexcept;

    [[nodiscard]] constexpr Piece get(const Square &sq) const noexcept {
        const Bitboard bb{sq};
        if (pieces_[static_cast<int>(Side::Black)] & bb) {
            return Piece::Black;
        } else if (pieces_[static_cast<int>(Side::White)] & bb) {
            return Piece::White;
        } else if (gaps_ & bb) {
            return Piece::Gap;
        } else {
            return Piece::Empty;
        }
    }

    [[nodiscard]] constexpr Bitboard empty() const noexcept {
        return ~(pieces_[static_cast<int>(Side::Black)] |
                 pieces_[static_cast<int>(Side::White)] | gaps_);
    }

   private:
    Bitboard pieces_[2];
    Bitboard gaps_;
    unsigned int halfmoves_;
    Side turn_;
};

inline std::ostream &operator<<(std::ostream &os, const Position &pos) {
    int idx = 42;
    while (idx >= 0) {
        const auto sq = Square{idx};
        const Bitboard bb{sq};
        const Piece piece{pos.get(sq)};

        switch (piece) {
            case Piece::Black:
                os << 'x';
                break;
            case Piece::White:
                os << 'o';
                break;
            case Piece::Gap:
                os << ' ';
                break;
            case Piece::Empty:
                os << '-';
                break;
        }

        if (sq.file() == files::G) {
            idx -= 14;
            os << '\n';
        }
        idx++;
    }
    os << "Turn: " << pos.turn() << std::endl;
    return os;
}

}  // namespace libataxx

#endif
