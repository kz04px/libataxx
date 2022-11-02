#ifndef LIBATAXX_SQUARE_HPP
#define LIBATAXX_SQUARE_HPP

#include <cstdint>
#include <ostream>
#include <string>
#include "file.hpp"
#include "rank.hpp"

namespace libataxx {

// clang-format off
enum class SquareIndex : std::uint8_t
{
    A1 = 0, B1, C1, D1, E1, F1, G1,
    A2 = 8, B2, C2, D2, E2, F2, G2,
    A3 = 16, B3, C3, D3, E3, F3, G3,
    A4 = 24, B4, C4, D4, E4, F4, G4,
    A5 = 32, B5, C5, D5, E5, F5, G5,
    A6 = 40, B6, C6, D6, E6, F6, G6,
    A7 = 48, B7, C7, D7, E7, F7, G7,
};
// clang-format on

class Square {
   public:
    [[nodiscard]] constexpr Square() = default;

    [[nodiscard]] explicit constexpr Square(const int sq) : data_(sq) {
    }

    [[nodiscard]] constexpr Square(const int f, const int r) : data_(8 * r + f) {
    }

    [[nodiscard]] constexpr Square(const File &f, const Rank &r) : data_(8 * int(r) + int(f)) {
    }

    [[nodiscard]] constexpr Square(const SquareIndex idx) : data_(static_cast<std::uint8_t>(idx)) {
    }

    [[nodiscard]] constexpr File file() const noexcept {
        return File{data_ % 8};
    }

    [[nodiscard]] constexpr Rank rank() const noexcept {
        return Rank{data_ / 8};
    }

    [[nodiscard]] constexpr int index() const noexcept {
        return 7 * static_cast<int>(rank()) + static_cast<int>(file());
    }

    [[nodiscard]] explicit constexpr operator int() const noexcept {
        return data_;
    }

    [[nodiscard]] explicit operator std::string() const noexcept {
        return std::string() + static_cast<char>(file()) + static_cast<char>(rank());
    }

    [[nodiscard]] constexpr bool operator==(const Square &rhs) const noexcept {
        return data_ == rhs.data_;
    }

    [[nodiscard]] constexpr bool operator!=(const Square &rhs) const noexcept {
        return data_ != rhs.data_;
    }

   private:
    std::uint8_t data_ = 0;
};

inline std::ostream &operator<<(std::ostream &os, const Square &sq) noexcept {
    os << static_cast<std::string>(sq);
    return os;
}

constexpr inline std::uint64_t operator<<(const uint64_t bb, const Square &sq) noexcept {
    return bb << static_cast<int>(sq);
}

constexpr inline std::uint64_t operator>>(const uint64_t bb, const Square &sq) noexcept {
    return bb >> static_cast<int>(sq);
}

static_assert(Square(SquareIndex::A1).file() == File(Files::FileA));

}  // namespace libataxx

#endif
