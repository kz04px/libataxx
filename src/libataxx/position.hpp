#ifndef LIBATAXX_POSITION_HPP
#define LIBATAXX_POSITION_HPP

#include <cstdint>
#include <string>
#include <vector>
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

    constexpr Position(const Bitboard &b,
                       const Bitboard &w,
                       const Bitboard &g,
                       const unsigned int hm,
                       const unsigned int fm,
                       const Side &t)
        : pieces_{b, w},
          gaps_{g},
          hash_{0},
          halfmoves_{hm},
          fullmoves_{fm},
          turn_{t} {
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

    [[nodiscard]] int count_moves() const noexcept;

    [[nodiscard]] int legal_moves(Move *movelist) const noexcept;

    [[nodiscard]] std::vector<Move> legal_moves() const noexcept;

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

    [[nodiscard]] constexpr std::uint64_t minimal_hash() const noexcept {
        enum Transform
        {
            None = 0,
            Rot90,
            Rot180,
            Rot270,
            FlipH,
            FlipV,
            A7G1,
            A1G7
        };

        auto transformation = Transform::None;
        auto n = pieces_[0];

        // Find minimal transformation
        if (pieces_[0].rot90() < n) {
            n = pieces_[0].rot90();
            transformation = Transform::Rot90;
        }
        if (pieces_[0].rot180() < n) {
            n = pieces_[0].rot180();
            transformation = Transform::Rot180;
        }
        if (pieces_[0].rot270() < n) {
            n = pieces_[0].rot270();
            transformation = Transform::Rot270;
        }
        if (pieces_[0].flip_horizontal() < n) {
            n = pieces_[0].flip_horizontal();
            transformation = Transform::FlipH;
        }
        if (pieces_[0].flip_vertical() < n) {
            n = pieces_[0].flip_vertical();
            transformation = Transform::FlipV;
        }
        if (pieces_[0].flip_diagA7G1() < n) {
            n = pieces_[0].flip_diagA7G1();
            transformation = Transform::A7G1;
        }
        if (pieces_[0].flip_diagA1G7() < n) {
            n = pieces_[0].flip_diagA1G7();
            transformation = Transform::A1G7;
        }

        // Return minimal transformation's hash
        switch (transformation) {
            case None:
                return hash_;
            case Rot90:
                return rot90().calculate_hash();
            case Rot180:
                return rot180().calculate_hash();
            case Rot270:
                return rot270().calculate_hash();
            case FlipH:
                return flip_horizontal().calculate_hash();
            case FlipV:
                return flip_vertical().calculate_hash();
            case A7G1:
                return flip_diagA7G1().calculate_hash();
            case A1G7:
                return flip_diagA1G7().calculate_hash();
            default:
                return hash_;
        }
    }

    [[nodiscard]] constexpr Position rot90() const noexcept {
        return Position{pieces_[0].rot90(),
                        pieces_[1].rot90(),
                        gaps_.rot90(),
                        halfmoves_,
                        fullmoves_,
                        turn_};
    }

    [[nodiscard]] constexpr Position rot180() const noexcept {
        return Position{pieces_[0].rot180(),
                        pieces_[1].rot180(),
                        gaps_.rot180(),
                        halfmoves_,
                        fullmoves_,
                        turn_};
    }

    [[nodiscard]] constexpr Position rot270() const noexcept {
        return Position{pieces_[0].rot270(),
                        pieces_[1].rot270(),
                        gaps_.rot270(),
                        halfmoves_,
                        fullmoves_,
                        turn_};
    }

    [[nodiscard]] constexpr Position flip_horizontal() const noexcept {
        return Position{pieces_[0].flip_horizontal(),
                        pieces_[1].flip_horizontal(),
                        gaps_.flip_horizontal(),
                        halfmoves_,
                        fullmoves_,
                        turn_};
    }

    [[nodiscard]] constexpr Position flip_vertical() const noexcept {
        return Position{pieces_[0].flip_vertical(),
                        pieces_[1].flip_vertical(),
                        gaps_.flip_vertical(),
                        halfmoves_,
                        fullmoves_,
                        turn_};
    }

    [[nodiscard]] constexpr Position flip_diagA7G1() const noexcept {
        return Position{pieces_[0].flip_diagA7G1(),
                        pieces_[1].flip_diagA7G1(),
                        gaps_.flip_diagA7G1(),
                        halfmoves_,
                        fullmoves_,
                        turn_};
    }

    [[nodiscard]] constexpr Position flip_diagA1G7() const noexcept {
        return Position{pieces_[0].flip_diagA1G7(),
                        pieces_[1].flip_diagA1G7(),
                        gaps_.flip_diagA1G7(),
                        halfmoves_,
                        fullmoves_,
                        turn_};
    }

    [[nodiscard]] std::uint64_t calculate_hash() const noexcept;

    [[nodiscard]] std::uint64_t predict_hash(const Move &move) const noexcept;

   private:
    Bitboard pieces_[2];
    Bitboard gaps_;
    std::uint64_t hash_;
    unsigned int halfmoves_;
    unsigned int fullmoves_;
    Side turn_;
};

inline std::ostream &operator<<(std::ostream &os, const Position &pos) {
    for (int y = 6; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            const auto f = File{x};
            const auto r = Rank{y};
            const auto sq = Square{f, r};
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
        }
        os << '\n';
    }
    os << "Turn: " << pos.turn();
    return os;
}

}  // namespace libataxx

#endif
