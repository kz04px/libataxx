#ifndef LIBATAXX_POSITION_HPP
#define LIBATAXX_POSITION_HPP

#include <cstdint>
#include <string>
#include "bitboard.hpp"
#include "move.hpp"
#include "piece.hpp"
#include "side.hpp"

namespace libataxx {

enum class Result
{
    None = 0,
    BlackWin,
    WhiteWin,
    Draw
};

class Position {
   public:
    constexpr Position()
        : pieces_{},
          gaps_{},
          hash_{0},
          halfmoves_{0},
          fullmoves_{0},
          turn_{Side::Black} {
    }

    constexpr Position(const std::string &fen)
        : pieces_{},
          gaps_{},
          hash_{0},
          halfmoves_{0},
          fullmoves_{0},
          turn_{Side::Black} {
        set_fen(fen);
    }

    void set_fen(const std::string &fen) noexcept;

    [[nodiscard]] std::string get_fen() const noexcept;

    [[nodiscard]] constexpr Side turn() const noexcept {
        return turn_;
    }

    constexpr void set_turn(const Side &side) noexcept {
        turn_ = side;
    }

    [[nodiscard]] std::uint64_t perft(const int depth) const noexcept;

    [[nodiscard]] std::uint64_t count_moves() const noexcept;

    [[nodiscard]] int legal_moves(Move *movelist) const noexcept;

    [[nodiscard]] int legal_captures(Move *movelist) const noexcept;

    [[nodiscard]] int legal_noncaptures(Move *movelist) const noexcept;

    [[nodiscard]] bool legal_move(const Move &move) const noexcept;

    [[nodiscard]] bool gameover() const noexcept;

    [[nodiscard]] constexpr Bitboard black() const noexcept {
        return pieces_[static_cast<int>(Side::Black)];
    }

    [[nodiscard]] constexpr Bitboard white() const noexcept {
        return pieces_[static_cast<int>(Side::White)];
    }

    [[nodiscard]] constexpr Bitboard gaps() const noexcept {
        return gaps_;
    }

    [[nodiscard]] constexpr Bitboard us() const noexcept {
        return pieces_[static_cast<int>(turn_)];
    }

    [[nodiscard]] constexpr Bitboard them() const noexcept {
        return pieces_[static_cast<int>(!turn_)];
    }

    [[nodiscard]] constexpr bool must_pass() const noexcept {
        return !(empty() & (us().singles() | us().doubles()));
    }

    [[nodiscard]] constexpr int score() const noexcept {
        return black().count() - white().count();
    }

    [[nodiscard]] constexpr int count_captures(const Move &move) const
        noexcept {
        const auto neighbours = Bitboard{move.to()}.singles() & them();
        return neighbours.count();
    }

    [[nodiscard]] constexpr bool is_capture(const Move &move) const noexcept {
        const auto neighbours = Bitboard{move.to()}.singles() & them();
        return neighbours != 0;
    }

    [[nodiscard]] Result result() const noexcept {
        if (!gameover()) {
            return Result::None;
        }

        const auto both = black() | white();
        const auto moves = (both.singles() | both.doubles()) & empty();

        // No legal moves or no pieces left
        if (!moves || !black() || !white()) {
            const int s = score();
            if (s > 0) {
                return Result::BlackWin;
            } else if (s < 0) {
                return Result::WhiteWin;
            } else {
                return Result::Draw;
            }
        }

        // 50 move draw
        if (halfmoves_ >= 100) {
            return Result::Draw;
        }

        return Result::None;
    }

    void makemove(const Move &move) noexcept;

    [[nodiscard]] constexpr Piece get(const Square &sq) const noexcept {
        const Bitboard bb{sq};
        if (black() & bb) {
            return Piece::Black;
        } else if (white() & bb) {
            return Piece::White;
        } else if (gaps() & bb) {
            return Piece::Gap;
        } else {
            return Piece::Empty;
        }
    }

    constexpr void set(const Square &sq, const Piece &piece) noexcept {
        const Bitboard bb{sq};
        switch (piece) {
            case Piece::Black:
                pieces_[static_cast<int>(Side::Black)] |= bb;
                pieces_[static_cast<int>(Side::White)] &= ~bb;
                gaps_ &= ~bb;
                break;
            case Piece::White:
                pieces_[static_cast<int>(Side::Black)] &= ~bb;
                pieces_[static_cast<int>(Side::White)] |= bb;
                gaps_ &= ~bb;
                break;
            case Piece::Gap:
                pieces_[static_cast<int>(Side::Black)] &= ~bb;
                pieces_[static_cast<int>(Side::White)] &= ~bb;
                gaps_ |= bb;
                break;
            case Piece::Empty:
                pieces_[static_cast<int>(Side::Black)] &= ~bb;
                pieces_[static_cast<int>(Side::White)] &= ~bb;
                gaps_ &= ~bb;
                break;
            default:
                break;
        }
    }

    [[nodiscard]] constexpr Bitboard empty() const noexcept {
        return ~(black() | white() | gaps());
    }

    [[nodiscard]] constexpr std::uint64_t hash() const noexcept {
        return hash_;
    }

    [[nodiscard]] unsigned int halfmoves() const noexcept {
        return halfmoves_;
    }

    [[nodiscard]] unsigned int fullmoves() const noexcept {
        return fullmoves_;
    }

    [[nodiscard]] constexpr Bitboard reachable() const noexcept {
        Bitboard all = black() | white();
        Bitboard remaining = empty();
        Bitboard moves;
        do {
            moves = (all.singles() | all.doubles()) & remaining;
            all |= moves;
            remaining &= ~moves;
        } while (moves);
        return all;
    }

    [[nodiscard]] std::uint64_t calculate_hash() const noexcept;

   private:
    Bitboard pieces_[2];
    Bitboard gaps_;
    std::uint64_t hash_;
    unsigned int halfmoves_;
    unsigned int fullmoves_;
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
