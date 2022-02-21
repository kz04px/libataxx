#ifndef LIBATAXX_BITBOARD_HPP
#define LIBATAXX_BITBOARD_HPP

#include <cassert>
#include <cstdint>
#include "square.hpp"

namespace libataxx {

class BitboardIterator {
   public:
    constexpr explicit BitboardIterator(const std::uint64_t &data) : data_{data} {
    }

    [[nodiscard]] constexpr Square operator*() const noexcept {
        const int n = __builtin_ctzll(data_);
        return Square{File{n % 8}, Rank{n / 8}};
    }

    constexpr BitboardIterator operator++() noexcept {
        data_ &= data_ - 1;
        return *this;
    }

    [[nodiscard]] constexpr bool operator!=(const BitboardIterator &rhs) const noexcept {
        return data_ != rhs.data_;
    }

   private:
    std::uint64_t data_;
};

class Bitboard {
   public:
    constexpr Bitboard() : data_{0} {
    }

    constexpr explicit Bitboard(const Square sq) : data_{1ULL << static_cast<int>(sq)} {
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
        return Bitboard{(data_ << 8) & 0x7f7f7f7f7f7f7fULL};
    }

    [[nodiscard]] constexpr Bitboard south() const noexcept {
        return Bitboard{data_ >> 8};
    }

    [[nodiscard]] constexpr Bitboard east() const noexcept {
        return Bitboard{(data_ << 1) & 0x7e7e7e7e7e7e7eULL};
    }

    [[nodiscard]] constexpr Bitboard west() const noexcept {
        return Bitboard{(data_ >> 1) & 0x3f3f3f3f3f3f3fULL};
    }

    [[nodiscard]] constexpr Bitboard singles() const noexcept {
        return north() | south() | east() | west() | north().west() | north().east() | south().west() | south().east();
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

    [[nodiscard]] constexpr Bitboard operator&(const Bitboard &rhs) const noexcept {
        return Bitboard{data_ & rhs.data_};
    }

    [[nodiscard]] constexpr Bitboard operator^(const Bitboard &rhs) const noexcept {
        return Bitboard{data_ ^ rhs.data_};
    }

    [[nodiscard]] constexpr Bitboard operator|(const Bitboard &rhs) const noexcept {
        return Bitboard{data_ | rhs.data_};
    }

    [[nodiscard]] constexpr Bitboard operator~() const noexcept {
        return Bitboard{~data_ & 0x7f7f7f7f7f7f7fULL};
    }

    [[nodiscard]] constexpr bool operator<(const Bitboard &rhs) const noexcept {
        return data_ < rhs.data_;
    }

    [[nodiscard]] constexpr Bitboard operator<<(const int n) const noexcept {
        return Bitboard{(data_ << n) & 0x7f7f7f7f7f7f7fULL};
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

    [[nodiscard]] constexpr bool operator==(const Bitboard &rhs) const noexcept {
        return data_ == rhs.data_;
    }

    [[nodiscard]] constexpr bool operator!=(const Bitboard &rhs) const noexcept {
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
        return Bitboard{((data_ << 56)) | ((data_ << 40) & 0x00ff000000000000ULL) |
                        ((data_ << 24) & 0x0000ff0000000000ULL) | ((data_ << 8) & 0x000000ff00000000ULL) |
                        ((data_ >> 8) & 0x00000000ff000000ULL) | ((data_ >> 24) & 0x0000000000ff0000ULL) |
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
        return flip_diagA1G7().flip_vertical();
    }

    [[nodiscard]] constexpr Bitboard rot180() const noexcept {
        return flip_vertical().flip_horizontal();
    }

    [[nodiscard]] constexpr Bitboard rot270() const noexcept {
        return flip_vertical().flip_diagA1G7();
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

namespace bitboards {

constexpr Bitboard All = Bitboard{0x7f7f7f7f7f7f7fULL};
constexpr Bitboard Empty = Bitboard{0x0ULL};
constexpr Bitboard Center = Bitboard{0x3e3e3e3e3e00ULL};
constexpr Bitboard Edge = Bitboard{0x7f41414141417fULL};
constexpr Bitboard Corners = Bitboard{0x41000000000041ULL};
// Files
constexpr Bitboard FileA = Bitboard{0x1010101010101ULL};
constexpr Bitboard FileB = Bitboard{0x2020202020202ULL};
constexpr Bitboard FileC = Bitboard{0x4040404040404ULL};
constexpr Bitboard FileD = Bitboard{0x8080808080808ULL};
constexpr Bitboard FileE = Bitboard{0x10101010101010ULL};
constexpr Bitboard FileF = Bitboard{0x20202020202020ULL};
constexpr Bitboard FileG = Bitboard{0x40404040404040ULL};
// Ranks
constexpr Bitboard Rank1 = Bitboard{0x7fULL};
constexpr Bitboard Rank2 = Bitboard{0x7f00ULL};
constexpr Bitboard Rank3 = Bitboard{0x7f0000ULL};
constexpr Bitboard Rank4 = Bitboard{0x7f000000ULL};
constexpr Bitboard Rank5 = Bitboard{0x7f00000000ULL};
constexpr Bitboard Rank6 = Bitboard{0x7f0000000000ULL};
constexpr Bitboard Rank7 = Bitboard{0x7f000000000000ULL};

}  // namespace bitboards

static_assert(sizeof(Bitboard) == sizeof(std::uint64_t));
static_assert(Bitboard{} == bitboards::Empty);
static_assert(bitboards::All.count() == 49);
static_assert(bitboards::Empty.count() == 0);
static_assert(bitboards::Corners.count() == 4);
static_assert(Bitboard{squares::A1}.count() == 1);
static_assert((Bitboard{squares::A1} | Bitboard{squares::B1}).count() == 2);
static_assert(bitboards::FileA.east() == bitboards::FileB);
static_assert(bitboards::FileB.east() == bitboards::FileC);
static_assert(bitboards::FileC.east() == bitboards::FileD);
static_assert(bitboards::FileD.east() == bitboards::FileE);
static_assert(bitboards::FileE.east() == bitboards::FileF);
static_assert(bitboards::FileF.east() == bitboards::FileG);
static_assert(bitboards::FileG.east() == bitboards::Empty);
static_assert(bitboards::FileA.west() == bitboards::Empty);
static_assert(bitboards::FileB.west() == bitboards::FileA);
static_assert(bitboards::FileC.west() == bitboards::FileB);
static_assert(bitboards::FileD.west() == bitboards::FileC);
static_assert(bitboards::FileE.west() == bitboards::FileD);
static_assert(bitboards::FileF.west() == bitboards::FileE);
static_assert(bitboards::FileG.west() == bitboards::FileF);
static_assert(bitboards::Rank1.north() == bitboards::Rank2);
static_assert(bitboards::Rank2.north() == bitboards::Rank3);
static_assert(bitboards::Rank3.north() == bitboards::Rank4);
static_assert(bitboards::Rank4.north() == bitboards::Rank5);
static_assert(bitboards::Rank5.north() == bitboards::Rank6);
static_assert(bitboards::Rank6.north() == bitboards::Rank7);
static_assert(bitboards::Rank7.north() == bitboards::Empty);
static_assert(bitboards::Rank1.south() == bitboards::Empty);
static_assert(bitboards::Rank2.south() == bitboards::Rank1);
static_assert(bitboards::Rank3.south() == bitboards::Rank2);
static_assert(bitboards::Rank4.south() == bitboards::Rank3);
static_assert(bitboards::Rank5.south() == bitboards::Rank4);
static_assert(bitboards::Rank6.south() == bitboards::Rank5);
static_assert(bitboards::Rank7.south() == bitboards::Rank6);
static_assert((bitboards::Center | bitboards::Edge) == bitboards::All);
static_assert((bitboards::Center & bitboards::Edge) == bitboards::Empty);
static_assert(bitboards::Center.count() == 25);
static_assert(bitboards::Edge.count() == 24);
static_assert(Bitboard{squares::A1}.north() == Bitboard{squares::A2});
static_assert(Bitboard{squares::A1}.south() == bitboards::Empty);
static_assert(Bitboard{squares::A1}.east() == Bitboard{squares::B1});
static_assert(Bitboard{squares::A1}.west() == bitboards::Empty);
static_assert(Bitboard{squares::G1}.north() == Bitboard{squares::G2});
static_assert(Bitboard{squares::G1}.south() == bitboards::Empty);
static_assert(Bitboard{squares::G1}.east() == bitboards::Empty);
static_assert(Bitboard{squares::G1}.west() == Bitboard{squares::F1});
static_assert(Bitboard{squares::A1}.north().north() == Bitboard{squares::A3});
static_assert(Bitboard{squares::A1}.north().east() == Bitboard{squares::B2});
static_assert(Bitboard{squares::A1}.north().south() == Bitboard{squares::A1});
static_assert(Bitboard{squares::D4}.singles().count() == 8);
static_assert(Bitboard{squares::D4}.doubles().count() == 16);
static_assert(Bitboard{squares::A1}.singles().count() == 3);
static_assert(Bitboard{squares::A1}.doubles().count() == 5);
static_assert(Bitboard{squares::G1}.singles().count() == 3);
static_assert(Bitboard{squares::G1}.doubles().count() == 5);
static_assert(Bitboard{squares::A7}.singles().count() == 3);
static_assert(Bitboard{squares::A7}.doubles().count() == 5);
static_assert(Bitboard{squares::G7}.singles().count() == 3);
static_assert(Bitboard{squares::G7}.doubles().count() == 5);
static_assert(bitboards::All.singles() == bitboards::All);
static_assert(bitboards::All.doubles() == bitboards::All);
static_assert(bitboards::Empty.singles() == bitboards::Empty);
static_assert(bitboards::Empty.doubles() == bitboards::Empty);
static_assert(~bitboards::Empty == bitboards::All);
static_assert(~bitboards::All == bitboards::Empty);

}  // namespace libataxx

#endif
