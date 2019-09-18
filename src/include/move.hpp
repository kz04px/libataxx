#ifndef LIBATAXX_MOVE_HPP
#define LIBATAXX_MOVE_HPP

#include <cstdint>
#include <ostream>
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

    static constexpr Move nullmove() {
        return Move{};
    }

    constexpr bool operator==(const Move &rhs) const noexcept {
        return from_ == rhs.from_ && to_ == rhs.to_;
    }

   private:
    Square from_;
    Square to_;
};

inline std::ostream &operator<<(std::ostream &os, const Move &m) {
    if (m == Move::nullmove()) {
        os << "0000";
    } else if (m.type() == Move::Type::Single) {
        os << m.from();
    } else {
        os << m.from() << m.to();
    }

    return os;
}

static_assert(Move{Squares::A1}.type() == Move::Type::Single);
// static_assert(Move{Squares::A1, Squares::A2}.type() == Move::Type::Single);
static_assert(Move{Squares::A1, Squares::A3}.type() == Move::Type::Double);

}  // namespace libataxx

#endif
