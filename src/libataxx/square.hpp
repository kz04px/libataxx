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

    constexpr Square(const int f, const int r) : data_(8 * r + f) {
    }

    constexpr Square(const File &f, const Rank &r) : data_(8 * int(r) + int(f)) {
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
    std::uint8_t data_;
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

namespace squares {

constexpr static Square A1 = Square(files::A, ranks::A);
constexpr static Square B1 = Square(files::B, ranks::A);
constexpr static Square C1 = Square(files::C, ranks::A);
constexpr static Square D1 = Square(files::D, ranks::A);
constexpr static Square E1 = Square(files::E, ranks::A);
constexpr static Square F1 = Square(files::F, ranks::A);
constexpr static Square G1 = Square(files::G, ranks::A);
constexpr static Square A2 = Square(files::A, ranks::B);
constexpr static Square B2 = Square(files::B, ranks::B);
constexpr static Square C2 = Square(files::C, ranks::B);
constexpr static Square D2 = Square(files::D, ranks::B);
constexpr static Square E2 = Square(files::E, ranks::B);
constexpr static Square F2 = Square(files::F, ranks::B);
constexpr static Square G2 = Square(files::G, ranks::B);
constexpr static Square A3 = Square(files::A, ranks::C);
constexpr static Square B3 = Square(files::B, ranks::C);
constexpr static Square C3 = Square(files::C, ranks::C);
constexpr static Square D3 = Square(files::D, ranks::C);
constexpr static Square E3 = Square(files::E, ranks::C);
constexpr static Square F3 = Square(files::F, ranks::C);
constexpr static Square G3 = Square(files::G, ranks::C);
constexpr static Square A4 = Square(files::A, ranks::D);
constexpr static Square B4 = Square(files::B, ranks::D);
constexpr static Square C4 = Square(files::C, ranks::D);
constexpr static Square D4 = Square(files::D, ranks::D);
constexpr static Square E4 = Square(files::E, ranks::D);
constexpr static Square F4 = Square(files::F, ranks::D);
constexpr static Square G4 = Square(files::G, ranks::D);
constexpr static Square A5 = Square(files::A, ranks::E);
constexpr static Square B5 = Square(files::B, ranks::E);
constexpr static Square C5 = Square(files::C, ranks::E);
constexpr static Square D5 = Square(files::D, ranks::E);
constexpr static Square E5 = Square(files::E, ranks::E);
constexpr static Square F5 = Square(files::F, ranks::E);
constexpr static Square G5 = Square(files::G, ranks::E);
constexpr static Square A6 = Square(files::A, ranks::F);
constexpr static Square B6 = Square(files::B, ranks::F);
constexpr static Square C6 = Square(files::C, ranks::F);
constexpr static Square D6 = Square(files::D, ranks::F);
constexpr static Square E6 = Square(files::E, ranks::F);
constexpr static Square F6 = Square(files::F, ranks::F);
constexpr static Square G6 = Square(files::G, ranks::F);
constexpr static Square A7 = Square(files::A, ranks::G);
constexpr static Square B7 = Square(files::B, ranks::G);
constexpr static Square C7 = Square(files::C, ranks::G);
constexpr static Square D7 = Square(files::D, ranks::G);
constexpr static Square E7 = Square(files::E, ranks::G);
constexpr static Square F7 = Square(files::F, ranks::G);
constexpr static Square G7 = Square(files::G, ranks::G);

// static_assert(A1 == "a1");
static_assert(A1.file() == files::A);

}  // namespace squares

}  // namespace libataxx

#endif
