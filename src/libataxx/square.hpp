#ifndef LIBATAXX_SQUARE_HPP
#define LIBATAXX_SQUARE_HPP

#include <cstdint>
#include <ostream>
#include <string>
#include "file.hpp"
#include "rank.hpp"

namespace libataxx {

class Square {
   public:
    constexpr Square() : data_{0} {
    }

    explicit constexpr Square(const int sq) : data_(sq) {
    }

    constexpr Square(const int f, const int r) : data_(7 * r + f) {
    }

    constexpr Square(const File &f, const Rank &r)
        : data_(7 * int(r) + int(f)) {
    }

    [[nodiscard]] constexpr File file() const noexcept {
        return File{data_ % 7};
    }

    [[nodiscard]] constexpr Rank rank() const noexcept {
        return Rank{data_ / 7};
    }

    [[nodiscard]] explicit constexpr operator int() const noexcept {
        return data_;
    }

    [[nodiscard]] explicit operator std::string() const noexcept {
        return std::string() + static_cast<char>(file()) +
               static_cast<char>(rank());
    }

    [[nodiscard]] constexpr bool operator==(const Square &rhs) const noexcept {
        return data_ == rhs.data_;
    }

    [[nodiscard]] constexpr bool operator!=(const Square &rhs) const noexcept {
        return data_ != rhs.data_;
    }

   private:
    std::uint8_t data_;
};

inline std::ostream &operator<<(std::ostream &os, const Square &sq) noexcept {
    os << static_cast<std::string>(sq);
    return os;
}

constexpr inline std::uint64_t operator<<(const uint64_t bb,
                                          const Square &sq) noexcept {
    return bb << sq;
}

constexpr inline std::uint64_t operator>>(const uint64_t bb,
                                          const Square &sq) noexcept {
    return bb >> sq;
}

namespace Squares {

constexpr static Square A1 = Square(0);
constexpr static Square B1 = Square(1);
constexpr static Square C1 = Square(2);
constexpr static Square D1 = Square(3);
constexpr static Square E1 = Square(4);
constexpr static Square F1 = Square(5);
constexpr static Square G1 = Square(6);
constexpr static Square A2 = Square(7);
constexpr static Square B2 = Square(8);
constexpr static Square C2 = Square(9);
constexpr static Square D2 = Square(10);
constexpr static Square E2 = Square(11);
constexpr static Square F2 = Square(12);
constexpr static Square G2 = Square(13);
constexpr static Square A3 = Square(14);
constexpr static Square B3 = Square(15);
constexpr static Square C3 = Square(16);
constexpr static Square D3 = Square(17);
constexpr static Square E3 = Square(18);
constexpr static Square F3 = Square(19);
constexpr static Square G3 = Square(20);
constexpr static Square A4 = Square(21);
constexpr static Square B4 = Square(22);
constexpr static Square C4 = Square(23);
constexpr static Square D4 = Square(24);
constexpr static Square E4 = Square(25);
constexpr static Square F4 = Square(26);
constexpr static Square G4 = Square(27);
constexpr static Square A5 = Square(28);
constexpr static Square B5 = Square(29);
constexpr static Square C5 = Square(30);
constexpr static Square D5 = Square(31);
constexpr static Square E5 = Square(32);
constexpr static Square F5 = Square(33);
constexpr static Square G5 = Square(34);
constexpr static Square A6 = Square(35);
constexpr static Square B6 = Square(36);
constexpr static Square C6 = Square(37);
constexpr static Square D6 = Square(38);
constexpr static Square E6 = Square(39);
constexpr static Square F6 = Square(40);
constexpr static Square G6 = Square(41);
constexpr static Square A7 = Square(42);
constexpr static Square B7 = Square(43);
constexpr static Square C7 = Square(44);
constexpr static Square D7 = Square(45);
constexpr static Square E7 = Square(46);
constexpr static Square F7 = Square(47);
constexpr static Square G7 = Square(48);

// static_assert(A1 == "a1");
static_assert(A1.file() == files::A);

}  // namespace Squares

}  // namespace libataxx

#endif
