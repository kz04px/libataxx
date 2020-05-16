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

    [[nodiscard]] constexpr Square operator*() const noexcept {
        const int n = __builtin_ctzll(data_);
        return Square{File{n % 8}, Rank{n / 8}};
    }

    constexpr BitboardIterator operator++() noexcept {
        data_ &= data_ - 1;
        return *this;
    }

    [[nodiscard]] constexpr bool operator!=(const BitboardIterator &rhs) const
        noexcept {
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

    [[nodiscard]] constexpr bool get(const Square &sq) const noexcept {
        return (data_ >> sq) & 1;
    }

    [[nodiscard]] constexpr Bitboard north() const noexcept {
        return ((*this) << 8) & Bitboard::all();
    }

    [[nodiscard]] constexpr Bitboard south() const noexcept {
        return (*this) >> 8;
    }

    [[nodiscard]] constexpr Bitboard east() const noexcept {
        return ((*this) << 1) & Bitboard::NotFileA();
    }

    [[nodiscard]] constexpr Bitboard west() const noexcept {
        return ((*this) >> 1) & Bitboard::NotFileG();
    }

    [[nodiscard]] constexpr Bitboard singles() const noexcept {
        return north() | south() | east() | west() | north().west() |
               north().east() | south().west() | south().east();
    }

    [[nodiscard]] constexpr Bitboard doubles() const noexcept {
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

    [[nodiscard]] constexpr Bitboard operator&(const Bitboard &rhs) const
        noexcept {
        return Bitboard{data_ & rhs.data_};
    }

    [[nodiscard]] constexpr Bitboard operator^(const Bitboard &rhs) const
        noexcept {
        return Bitboard{data_ ^ rhs.data_};
    }

    [[nodiscard]] constexpr Bitboard operator|(const Bitboard &rhs) const
        noexcept {
        return Bitboard{data_ | rhs.data_};
    }

    [[nodiscard]] constexpr Bitboard operator~() const noexcept {
        return Bitboard{~data_} & all();
    }

    [[nodiscard]] constexpr Bitboard operator<<(const int n) const noexcept {
        return Bitboard{data_ << n} & all();
    }

    [[nodiscard]] constexpr Bitboard operator>>(const int n) const noexcept {
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

    [[nodiscard]] constexpr bool operator==(const Bitboard &rhs) const
        noexcept {
        return data_ == rhs.data_;
    }

    [[nodiscard]] constexpr bool operator!=(const Bitboard &rhs) const
        noexcept {
        return data_ != rhs.data_;
    }

    [[nodiscard]] constexpr operator bool() const noexcept {
        return data_;
    }

    [[nodiscard]] constexpr BitboardIterator begin() const noexcept {
        return BitboardIterator{data_};
    }

    [[nodiscard]] constexpr BitboardIterator end() const noexcept {
        return BitboardIterator{0};
    }

    [[nodiscard]] constexpr int lsbll() const noexcept {
        return __builtin_ctzll(data_);
    }

    [[nodiscard]] constexpr Bitboard flip_vertical() const noexcept {
        return Bitboard{
                   ((data_ << 56)) | ((data_ << 40) & 0x00ff000000000000ULL) |
                   ((data_ << 24) & 0x0000ff0000000000ULL) |
                   ((data_ << 8) & 0x000000ff00000000ULL) |
                   ((data_ >> 8) & 0x00000000ff000000ULL) |
                   ((data_ >> 24) & 0x0000000000ff0000ULL) |
                   ((data_ >> 40) & 0x000000000000ff00ULL) | ((data_ >> 56))} >>
               8;
    }

    [[nodiscard]] constexpr Bitboard flip_horizontal() const noexcept {
        constexpr std::uint64_t k1 = 0x5555555555555555ULL;
        constexpr std::uint64_t k2 = 0x3333333333333333ULL;
        constexpr std::uint64_t k4 = 0x0f0f0f0f0f0f0f0fULL;
        auto x = data_;
        x = ((x >> 1) & k1) + 2 * (x & k1);
        x = ((x >> 2) & k2) + 4 * (x & k2);
        x = ((x >> 4) & k4) + 16 * (x & k4);
        return Bitboard{x >> 1};
    }

    [[nodiscard]] constexpr Bitboard flip_diagA7G1() const noexcept {
        constexpr std::uint64_t k1 = 0xaa00aa00aa00aa00ULL;
        constexpr std::uint64_t k2 = 0xcccc0000cccc0000ULL;
        constexpr std::uint64_t k4 = 0xf0f0f0f00f0f0f0fULL;
        std::uint64_t t = 0;
        std::uint64_t x = data_;
        t = x ^ (x << 36);
        x ^= k4 & (t ^ (x >> 36));
        t = k2 & (x ^ (x << 18));
        x ^= t ^ (t >> 18);
        t = k1 & (x ^ (x << 9));
        x ^= t ^ (t >> 9);
        return Bitboard{x >> 9};
    }

    [[nodiscard]] constexpr Bitboard flip_diagA1G7() const noexcept {
        constexpr std::uint64_t k1 = 0x5500550055005500ULL;
        constexpr std::uint64_t k2 = 0x3333000033330000ULL;
        constexpr std::uint64_t k4 = 0x0f0f0f0f00000000ULL;
        std::uint64_t t = 0;
        std::uint64_t x = data_;
        t = k4 & (x ^ (x << 28));
        x ^= t ^ (t >> 28);
        t = k2 & (x ^ (x << 14));
        x ^= t ^ (t >> 14);
        t = k1 & (x ^ (x << 7));
        x ^= t ^ (t >> 7);
        return Bitboard{x};
    }

    [[nodiscard]] constexpr Bitboard rot90() const noexcept {
        return ((*this).flip_diagA1G7()).flip_vertical();
    }

    [[nodiscard]] constexpr Bitboard rot180() const noexcept {
        return ((*this).flip_vertical()).flip_horizontal();
    }

    [[nodiscard]] constexpr Bitboard rot270() const noexcept {
        return ((*this).flip_vertical()).flip_diagA1G7();
    }

    [[nodiscard]] static constexpr Bitboard all() noexcept {
        return Bitboard{0x7f7f7f7f7f7f7fULL};
    }

    [[nodiscard]] static constexpr Bitboard Empty() noexcept {
        return Bitboard{0x0ULL};
    }

    [[nodiscard]] static constexpr Bitboard FileA() noexcept {
        return Bitboard{0x1010101010101ULL};
    }

    [[nodiscard]] static constexpr Bitboard FileB() noexcept {
        return Bitboard{0x2020202020202ULL};
    }

    [[nodiscard]] static constexpr Bitboard FileC() noexcept {
        return Bitboard{0x4040404040404ULL};
    }

    [[nodiscard]] static constexpr Bitboard FileD() noexcept {
        return Bitboard{0x8080808080808ULL};
    }

    [[nodiscard]] static constexpr Bitboard FileE() noexcept {
        return Bitboard{0x10101010101010ULL};
    }

    [[nodiscard]] static constexpr Bitboard FileF() noexcept {
        return Bitboard{0x20202020202020ULL};
    }

    [[nodiscard]] static constexpr Bitboard FileG() noexcept {
        return Bitboard{0x40404040404040ULL};
    }

    [[nodiscard]] static constexpr Bitboard Rank1() noexcept {
        return Bitboard{0x7fULL};
    }

    [[nodiscard]] static constexpr Bitboard Rank2() noexcept {
        return Bitboard{0x7f00ULL};
    }

    [[nodiscard]] static constexpr Bitboard Rank3() noexcept {
        return Bitboard{0x7f0000ULL};
    }

    [[nodiscard]] static constexpr Bitboard Rank4() noexcept {
        return Bitboard{0x7f000000ULL};
    }

    [[nodiscard]] static constexpr Bitboard Rank5() noexcept {
        return Bitboard{0x7f00000000ULL};
    }

    [[nodiscard]] static constexpr Bitboard Rank6() noexcept {
        return Bitboard{0x7f0000000000ULL};
    }

    [[nodiscard]] static constexpr Bitboard Rank7() noexcept {
        return Bitboard{0x7f000000000000ULL};
    }

    [[nodiscard]] static constexpr Bitboard Center() noexcept {
        return Bitboard{0x3e3e3e3e3e00ULL};
    }

    [[nodiscard]] static constexpr Bitboard Edge() noexcept {
        return Bitboard{0x7f41414141417fULL};
    }

    [[nodiscard]] static constexpr Bitboard NotFileA() noexcept {
        return Bitboard{0x7e7e7e7e7e7e7eULL};
    }

    [[nodiscard]] static constexpr Bitboard NotFileB() noexcept {
        return Bitboard{0x7d7d7d7d7d7d7dULL};
    }

    [[nodiscard]] static constexpr Bitboard NotFileC() noexcept {
        return Bitboard{0x7b7b7b7b7b7b7bULL};
    }

    [[nodiscard]] static constexpr Bitboard NotFileD() noexcept {
        return Bitboard{0x77777777777777ULL};
    }

    [[nodiscard]] static constexpr Bitboard NotFileE() noexcept {
        return Bitboard{0x6f6f6f6f6f6f6fULL};
    }

    [[nodiscard]] static constexpr Bitboard NotFileF() noexcept {
        return Bitboard{0x5f5f5f5f5f5f5fULL};
    }

    [[nodiscard]] static constexpr Bitboard NotFileG() noexcept {
        return Bitboard{0x3f3f3f3f3f3f3fULL};
    }

   private:
    std::uint64_t data_;
};

inline std::ostream &operator<<(std::ostream &os, const Bitboard &bb) {
    for (int y = 6; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            const auto f = File{x};
            const auto r = Rank{y};
            const auto sq = Square{f, r};
            const auto nbb = Bitboard{sq};

            if (nbb & bb) {
                os << '1';
            } else {
                os << '0';
            }
        }
        os << '\n';
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
static_assert((Bitboard::Center() | Bitboard::Edge()) == Bitboard::all());
static_assert((Bitboard::Center() & Bitboard::Edge()) == Bitboard{0});
static_assert(Bitboard::Center().count() == 25);
static_assert(Bitboard::Edge().count() == 24);
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
