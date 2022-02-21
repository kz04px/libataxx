#ifndef LIBATAXX_MOVE_HPP
#define LIBATAXX_MOVE_HPP

#include <cstdint>
#include <ostream>
#include <string>
#include "square.hpp"

namespace libataxx {

constexpr int max_moves = 256;

class Move {
   public:
    enum class Type : bool
    {
        Single = 0,
        Double
    };

    constexpr Move() : from_{0xFF}, to_{0xFF} {
    }

    constexpr explicit Move(const Square to) : from_{to}, to_{to} {
    }

    constexpr Move(const Square from, const Square to) : from_{from}, to_{to} {
    }

    [[nodiscard]] constexpr Type type() const noexcept {
        if (from_ == to_) {
            return Type::Single;
        } else {
            return Type::Double;
        }
    }

    [[nodiscard]] constexpr bool is_single() const noexcept {
        return from_ == to_;
    }

    [[nodiscard]] constexpr bool is_double() const noexcept {
        return !is_single();
    }

    [[nodiscard]] constexpr Square from() const noexcept {
        return from_;
    }

    [[nodiscard]] constexpr Square to() const noexcept {
        return to_;
    }

    [[nodiscard]] static constexpr Move nullmove() {
        return Move{0xFE, 0xFE};
    }

    [[nodiscard]] static constexpr Move nomove() {
        return Move{};
    }

    [[nodiscard]] constexpr bool operator==(const Move &rhs) const noexcept {
        return from_ == rhs.from_ && to_ == rhs.to_;
    }

    [[nodiscard]] constexpr bool operator!=(const Move &rhs) const noexcept {
        return from_ != rhs.from_ || to_ != rhs.to_;
    }

    [[nodiscard]] constexpr operator bool() const noexcept {
        return *this != nomove();
    }

    [[nodiscard]] explicit operator std::string() const noexcept {
        if (*this == Move::nullmove()) {
            return "0000";
        } else if (*this == Move::nomove()) {
            return "NONE";
        } else if (type() == Move::Type::Single) {
            return static_cast<std::string>(from());
        } else {
            return static_cast<std::string>(from()) + static_cast<std::string>(to());
        }
    }

    [[nodiscard]] static Move from_uai(const std::string &str) {
        if (str == "0000" || str == "null") {
            return Move::nullmove();
        } else if (str.length() == 2) {
            const int x = str[0] - 'a';
            const int y = str[1] - '1';

            if (x < 0 || x > 6 || y < 0 || y > 6) {
                throw std::invalid_argument("Not a move. (" + str + ")");
            }

            return Move(Square{x, y});
        } else if (str.length() == 4) {
            const int x1 = str[0] - 'a';
            const int y1 = str[1] - '1';
            const int x2 = str[2] - 'a';
            const int y2 = str[3] - '1';

            if (x1 < 0 || x1 > 6 || y1 < 0 || y1 > 6) {
                throw std::invalid_argument("Invalid move. (" + str + ")");
            }

            if (x2 < 0 || x2 > 6 || y2 < 0 || y2 > 6) {
                throw std::invalid_argument("Invalid move. (" + str + ")");
            }

            const auto sq1 = Square{x1, y1};
            const auto sq2 = Square{x2, y2};
            const int dx = std::abs(x1 - x2);
            const int dy = std::abs(y1 - y2);

            if (sq1 == sq2) {
                throw std::invalid_argument("Source and destination square are the same");
            }

            if (dx > 2 || dy > 2) {
                throw std::invalid_argument("Invalid move. (" + str + ")");
            }

            // We were just given a single jump in longhand notation
            // e.g. "b2b3" instead of "b3"
            if (dx <= 1 && dy <= 1) {
                throw std::invalid_argument("Single move given as double move");
            }

            return Move(sq1, sq2);
        }

        throw std::invalid_argument("Invalid move. (" + str + ")");
    }

   private:
    constexpr Move(const int f, const int t) : from_{f}, to_{t} {
    }

   private:
    Square from_;
    Square to_;
};

inline std::ostream &operator<<(std::ostream &os, const Move &m) {
    os << static_cast<std::string>(m);
    return os;
}

static_assert(Move{squares::A1}.type() == Move::Type::Single);
// static_assert(Move{squares::A1, squares::A2}.type() ==
// Move::Type::Single);
static_assert(Move{squares::A1, squares::A3}.type() == Move::Type::Double);

}  // namespace libataxx

#endif
