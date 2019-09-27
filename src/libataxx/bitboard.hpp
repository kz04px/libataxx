#ifndef LIBATAXX_BITBOARD_HPP
#define LIBATAXX_BITBOARD_HPP

#include <cassert>
#include <cstdint>
#include "square.hpp"

namespace libataxx {

class BitboardIterator {
   public:
    constexpr BitboardIterator(const std::uint64_t &data) : data_{data} {
    }

    constexpr Square operator*() const noexcept {
        return Square{__builtin_ctzll(data_)};
    }

    constexpr BitboardIterator operator++() noexcept {
        data_ &= data_ - 1;
        return *this;
    }

    constexpr bool operator!=(const BitboardIterator &rhs) const noexcept {
        return data_ != rhs.data_;
    }

   private:
    std::uint64_t data_;
};

class Bitboard {
   public:
    constexpr Bitboard() : data_{0} {
    }

    constexpr explicit Bitboard(const Square sq)
        : data_{1ULL << static_cast<int>(sq)} {
    }

    constexpr explicit Bitboard(const std::uint64_t bb) : data_{bb} {
    }

    [[nodiscard]] constexpr int count() const noexcept {
        return __builtin_popcountll(data_);
    }

    constexpr void set(const Square &sq) noexcept {
        data_ |= 1ULL << sq;
    }

    constexpr bool get(const Square &sq) const noexcept {
        return (data_ >> sq) & 1;
    }

    constexpr Bitboard north() const noexcept {
        return ((*this) << 7) & Bitboard::all();
    }

    constexpr Bitboard south() const noexcept {
        return (*this) >> 7;
    }

    constexpr Bitboard east() const noexcept {
        return ((*this) << 1) & Bitboard::NotFileA();
    }

    constexpr Bitboard west() const noexcept {
        return ((*this) >> 1) & Bitboard::NotFileG();
    }

    constexpr Bitboard singles() const noexcept {
        return north() | south() | east() | west() | north().west() |
               north().east() | south().west() | south().east();
    }

    constexpr Bitboard doubles() const noexcept {
        // clang-format off
        return // North
               north().north().west().west() |
               north().north().west() |
               north().north() |
               north().north().east() |
               north().north().east().east() |
               // East
               east().east().north() |
               east().east() |
               east().east().south() |
               // West
               west().west().north() |
               west().west() |
               west().west().south() |
               // South
               south().south().west().west() |
               south().south().west() |
               south().south() |
               south().south().east() |
               south().south().east().east();
        // clang-format on
    }

    constexpr void clear() noexcept {
        data_ = 0;
    }

    constexpr Bitboard operator&(const Bitboard &rhs) const noexcept {
        return Bitboard{data_ & rhs.data_};
    }

    constexpr Bitboard operator^(const Bitboard &rhs) const noexcept {
        return Bitboard{data_ ^ rhs.data_};
    }

    constexpr Bitboard operator|(const Bitboard &rhs) const noexcept {
        return Bitboard{data_ | rhs.data_};
    }

    constexpr Bitboard operator~() const noexcept {
        return Bitboard{~data_} & all();
    }

    constexpr Bitboard operator<<(const int n) const noexcept {
        return Bitboard{data_ << n} & all();
    }

    constexpr Bitboard operator>>(const int n) const noexcept {
        return Bitboard{data_ >> n};
    }

    constexpr Bitboard operator^=(const Bitboard &rhs) {
        data_ ^= rhs.data_;
        return *this;
    }

    constexpr Bitboard operator|=(const Bitboard &rhs) {
        data_ |= rhs.data_;
        return *this;
    }

    constexpr Bitboard operator&=(const Bitboard &rhs) {
        data_ &= rhs.data_;
        return *this;
    }

    constexpr bool operator==(const Bitboard &rhs) const noexcept {
        return data_ == rhs.data_;
    }

    constexpr bool operator!=(const Bitboard &rhs) const noexcept {
        return data_ != rhs.data_;
    }

    constexpr operator bool() const noexcept {
        return data_;
    }

    constexpr BitboardIterator begin() const noexcept {
        return BitboardIterator{data_};
    }

    constexpr BitboardIterator end() const noexcept {
        return BitboardIterator{0};
    }

    constexpr int lsbll() const noexcept {
        return __builtin_ctzll(data_);
    }

    static constexpr Bitboard all() noexcept {
        return Bitboard{0x1FFFFFFFFFFFFULL};
    }

    static constexpr Bitboard FileA() noexcept {
        return Bitboard{0x0040810204081ULL};
    }

    static constexpr Bitboard FileB() noexcept {
        return Bitboard{0x0081020408102ULL};
    }

    static constexpr Bitboard FileC() noexcept {
        return Bitboard{0x0102040810204ULL};
    }

    static constexpr Bitboard FileD() noexcept {
        return Bitboard{0x0204081020408ULL};
    }

    static constexpr Bitboard FileE() noexcept {
        return Bitboard{0x0408102040810ULL};
    }

    static constexpr Bitboard FileF() noexcept {
        return Bitboard{0x0810204081020ULL};
    }

    static constexpr Bitboard FileG() noexcept {
        return Bitboard{0x1020408102040ULL};
    }

    static constexpr Bitboard NotFileA() noexcept {
        return Bitboard{0x1fbf7efdfbf7eULL};
    }

    static constexpr Bitboard NotFileB() noexcept {
        return Bitboard{0x1f7efdfbf7efdULL};
    }

    static constexpr Bitboard NotFileC() noexcept {
        return Bitboard{0x1efdfbf7efdfbULL};
    }

    static constexpr Bitboard NotFileD() noexcept {
        return Bitboard{0x1dfbf7efdfbf7ULL};
    }

    static constexpr Bitboard NotFileE() noexcept {
        return Bitboard{0x1bf7efdfbf7efULL};
    }

    static constexpr Bitboard NotFileF() noexcept {
        return Bitboard{0x17efdfbf7efdfULL};
    }

    static constexpr Bitboard NotFileG() noexcept {
        return Bitboard{0x0fdfbf7efdfbfULL};
    }

   private:
    std::uint64_t data_;
};

inline std::ostream &operator<<(std::ostream &os, const Bitboard &bb) {
    int idx = 42;
    while (idx >= 0) {
        const auto sq = Square{idx};
        const Bitboard sq_bb{sq};

        if (sq_bb & bb) {
            os << '1';
        } else {
            os << '0';
        }

        if (sq.file() == files::G) {
            idx -= 14;
            os << '\n';
        }
        idx++;
    }
    return os;
}

static_assert(sizeof(Bitboard) == sizeof(std::uint64_t));
static_assert(Bitboard::all().count() == 49);
static_assert(Bitboard{}.count() == 0);
static_assert(Bitboard{Squares::A1}.count() == 1);
static_assert((Bitboard{Squares::A1} | Bitboard{Squares::B1}).count() == 2);
static_assert(Bitboard::FileA().west() == Bitboard{0});
static_assert(Bitboard::FileG().east() == Bitboard{0});
static_assert(Bitboard::FileA().east() == Bitboard::FileB());
static_assert(Bitboard::FileB().east() == Bitboard::FileC());
static_assert(Bitboard::FileC().east() == Bitboard::FileD());
static_assert(Bitboard::FileD().east() == Bitboard::FileE());
static_assert(Bitboard::FileE().east() == Bitboard::FileF());
static_assert(Bitboard::FileF().east() == Bitboard::FileG());
static_assert(Bitboard{Squares::A1}.north() == Bitboard{Squares::A2});
static_assert(Bitboard{Squares::A1}.south() == Bitboard{0});
static_assert(Bitboard{Squares::A1}.east() == Bitboard{Squares::B1});
static_assert(Bitboard{Squares::A1}.west() == Bitboard{0});
static_assert(Bitboard{Squares::G1}.north() == Bitboard{Squares::G2});
static_assert(Bitboard{Squares::G1}.south() == Bitboard{0});
static_assert(Bitboard{Squares::G1}.east() == Bitboard{0});
static_assert(Bitboard{Squares::G1}.west() == Bitboard{Squares::F1});
static_assert(Bitboard{Squares::A1}.north().north() == Bitboard{Squares::A3});
static_assert(Bitboard{Squares::A1}.north().east() == Bitboard{Squares::B2});
static_assert(Bitboard{Squares::A1}.north().south() == Bitboard{Squares::A1});
static_assert(Bitboard{Squares::D4}.singles().count() == 8);
static_assert(Bitboard{Squares::D4}.doubles().count() == 16);
static_assert(Bitboard{Squares::A1}.singles().count() == 3);
static_assert(Bitboard{Squares::A1}.doubles().count() == 5);
static_assert(Bitboard{Squares::G1}.singles().count() == 3);
static_assert(Bitboard{Squares::G1}.doubles().count() == 5);
static_assert(Bitboard{Squares::A7}.singles().count() == 3);
static_assert(Bitboard{Squares::A7}.doubles().count() == 5);
static_assert(Bitboard{Squares::G7}.singles().count() == 3);
static_assert(Bitboard{Squares::G7}.doubles().count() == 5);
static_assert(Bitboard::all().singles() == Bitboard::all());
static_assert(Bitboard::all().doubles() == Bitboard::all());
static_assert(Bitboard{0}.singles() == Bitboard{0});
static_assert(Bitboard{0}.doubles() == Bitboard{0});
static_assert(~Bitboard{0} == Bitboard::all());
static_assert(~Bitboard::all() == Bitboard{0});

}  // namespace libataxx

#endif
