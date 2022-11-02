#ifndef LIBATAXX_BITBOARD_HPP
#define LIBATAXX_BITBOARD_HPP

#include <cassert>
#include <cstdint>
#include "square.hpp"

namespace libataxx {

enum class Bitmask : std::uint64_t
{
    All = 0x7f7f7f7f7f7f7fULL,
    Empty = 0x0ULL,
    Center = 0x3e3e3e3e3e00ULL,
    Edge = 0x7f41414141417fULL,
    Corners = 0x41000000000041ULL,
    // Files
    FileA = 0x1010101010101ULL,
    FileB = 0x2020202020202ULL,
    FileC = 0x4040404040404ULL,
    FileD = 0x8080808080808ULL,
    FileE = 0x10101010101010ULL,
    FileF = 0x20202020202020ULL,
    FileG = 0x40404040404040ULL,
    // Ranks
    Rank1 = 0x7fULL,
    Rank2 = 0x7f00ULL,
    Rank3 = 0x7f0000ULL,
    Rank4 = 0x7f000000ULL,
    Rank5 = 0x7f00000000ULL,
    Rank6 = 0x7f0000000000ULL,
    Rank7 = 0x7f000000000000ULL,
};

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
    [[nodiscard]] constexpr Bitboard() = default;

    [[nodiscard]] constexpr explicit Bitboard(const Square sq) : data_{1ULL << static_cast<int>(sq)} {
    }

    [[nodiscard]] constexpr explicit Bitboard(const std::uint64_t bb) : data_{bb} {
    }

    [[nodiscard]] constexpr explicit Bitboard(const Bitmask mask) : data_{static_cast<std::uint64_t>(mask)} {
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
        return Bitboard(
            (data_ << 1 | data_ << 9 | data_ >> 7 | data_ << 8 | data_ >> 8 | data_ >> 1 | data_ >> 9 | data_ << 7) &
            0x7f7f7f7f7f7f7fULL);
    }

    [[nodiscard]] constexpr Bitboard doubles() const noexcept {
        // clang-format off
        return Bitboard(
                 // right
                 ((data_ << 2 | data_ << 10 | data_ << 18 | data_ >> 6 | data_ >> 14 | data_ << 17 | data_ >> 15) & 0x7e7e7e7e7e7e7eull) |
                 // center
                 ((data_ << 16 | data_ >> 16) & 0x7f7f7f7f7f7f7fULL) |
                 // left
                 ((data_ >> 2 | data_ >> 10 | data_ >> 18 | data_ << 6 | data_ << 14 | data_ << 15 | data_ >> 17) & 0x3f3f3f3f3f3f3full)
              );
        // clang-format on
    }

    constexpr void clear() noexcept {
        data_ = 0;
    }

    [[nodiscard]] constexpr bool get_empty() const noexcept {
        return data_ == 0ULL;
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
        return !get_empty();
    }

    [[nodiscard]] constexpr std::uint64_t data() const noexcept {
        return data_;
    }

    [[nodiscard]] constexpr BitboardIterator begin() const noexcept {
        return BitboardIterator{data_};
    }

    [[nodiscard]] static constexpr BitboardIterator end() noexcept {
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
    std::uint64_t data_ = 0;
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
static_assert(Bitboard().data() == 0x0);
static_assert(Bitboard(Bitmask::All).count() == 49);
static_assert(Bitboard(Bitmask::Empty).count() == 0);
static_assert(Bitboard(Bitmask::Corners).count() == 4);
static_assert(Bitboard{SquareIndex::A1}.count() == 1);
static_assert((Bitboard{SquareIndex::A1} | Bitboard{SquareIndex::B1}).count() == 2);
static_assert(Bitboard(Bitmask::FileA).east() == Bitboard(Bitmask::FileB));
static_assert(Bitboard(Bitmask::FileB).east() == Bitboard(Bitmask::FileC));
static_assert(Bitboard(Bitmask::FileC).east() == Bitboard(Bitmask::FileD));
static_assert(Bitboard(Bitmask::FileD).east() == Bitboard(Bitmask::FileE));
static_assert(Bitboard(Bitmask::FileE).east() == Bitboard(Bitmask::FileF));
static_assert(Bitboard(Bitmask::FileF).east() == Bitboard(Bitmask::FileG));
static_assert(Bitboard(Bitmask::FileG).east() == Bitboard(Bitmask::Empty));
static_assert(Bitboard(Bitmask::FileA).west() == Bitboard(Bitmask::Empty));
static_assert(Bitboard(Bitmask::FileB).west() == Bitboard(Bitmask::FileA));
static_assert(Bitboard(Bitmask::FileC).west() == Bitboard(Bitmask::FileB));
static_assert(Bitboard(Bitmask::FileD).west() == Bitboard(Bitmask::FileC));
static_assert(Bitboard(Bitmask::FileE).west() == Bitboard(Bitmask::FileD));
static_assert(Bitboard(Bitmask::FileF).west() == Bitboard(Bitmask::FileE));
static_assert(Bitboard(Bitmask::FileG).west() == Bitboard(Bitmask::FileF));
static_assert(Bitboard(Bitmask::Rank1).north() == Bitboard(Bitmask::Rank2));
static_assert(Bitboard(Bitmask::Rank2).north() == Bitboard(Bitmask::Rank3));
static_assert(Bitboard(Bitmask::Rank3).north() == Bitboard(Bitmask::Rank4));
static_assert(Bitboard(Bitmask::Rank4).north() == Bitboard(Bitmask::Rank5));
static_assert(Bitboard(Bitmask::Rank5).north() == Bitboard(Bitmask::Rank6));
static_assert(Bitboard(Bitmask::Rank6).north() == Bitboard(Bitmask::Rank7));
static_assert(Bitboard(Bitmask::Rank7).north() == Bitboard(Bitmask::Empty));
static_assert(Bitboard(Bitmask::Rank1).south() == Bitboard(Bitmask::Empty));
static_assert(Bitboard(Bitmask::Rank2).south() == Bitboard(Bitmask::Rank1));
static_assert(Bitboard(Bitmask::Rank3).south() == Bitboard(Bitmask::Rank2));
static_assert(Bitboard(Bitmask::Rank4).south() == Bitboard(Bitmask::Rank3));
static_assert(Bitboard(Bitmask::Rank5).south() == Bitboard(Bitmask::Rank4));
static_assert(Bitboard(Bitmask::Rank6).south() == Bitboard(Bitmask::Rank5));
static_assert(Bitboard(Bitmask::Rank7).south() == Bitboard(Bitmask::Rank6));
static_assert((Bitboard(Bitmask::Center) | Bitboard(Bitmask::Edge)) == Bitboard(Bitmask::All));
static_assert((Bitboard(Bitmask::Center) & Bitboard(Bitmask::Edge)) == Bitboard(Bitmask::Empty));
static_assert(Bitboard(Bitmask::Center).count() == 25);
static_assert(Bitboard(Bitmask::Edge).count() == 24);
static_assert(Bitboard{SquareIndex::A1}.north() == Bitboard{SquareIndex::A2});
static_assert(Bitboard{SquareIndex::A1}.south() == Bitboard(Bitmask::Empty));
static_assert(Bitboard{SquareIndex::A1}.east() == Bitboard{SquareIndex::B1});
static_assert(Bitboard{SquareIndex::A1}.west() == Bitboard(Bitmask::Empty));
static_assert(Bitboard{SquareIndex::G1}.north() == Bitboard{SquareIndex::G2});
static_assert(Bitboard{SquareIndex::G1}.south() == Bitboard(Bitmask::Empty));
static_assert(Bitboard{SquareIndex::G1}.east() == Bitboard(Bitmask::Empty));
static_assert(Bitboard{SquareIndex::G1}.west() == Bitboard{SquareIndex::F1});
static_assert(Bitboard{SquareIndex::A1}.north().north() == Bitboard{SquareIndex::A3});
static_assert(Bitboard{SquareIndex::A1}.north().east() == Bitboard{SquareIndex::B2});
static_assert(Bitboard{SquareIndex::A1}.north().south() == Bitboard{SquareIndex::A1});
static_assert(Bitboard{SquareIndex::D4}.singles().count() == 8);
static_assert(Bitboard{SquareIndex::D4}.doubles().count() == 16);
static_assert(Bitboard{SquareIndex::A1}.singles().count() == 3);
static_assert(Bitboard{SquareIndex::A1}.doubles().count() == 5);
static_assert(Bitboard{SquareIndex::G1}.singles().count() == 3);
static_assert(Bitboard{SquareIndex::G1}.doubles().count() == 5);
static_assert(Bitboard{SquareIndex::A7}.singles().count() == 3);
static_assert(Bitboard{SquareIndex::A7}.doubles().count() == 5);
static_assert(Bitboard{SquareIndex::G7}.singles().count() == 3);
static_assert(Bitboard{SquareIndex::G7}.doubles().count() == 5);
static_assert(Bitboard(Bitmask::All).singles() == Bitboard(Bitmask::All));
static_assert(Bitboard(Bitmask::All).doubles() == Bitboard(Bitmask::All));
static_assert(Bitboard(Bitmask::Empty).singles() == Bitboard(Bitmask::Empty));
static_assert(Bitboard(Bitmask::Empty).doubles() == Bitboard(Bitmask::Empty));
static_assert(~Bitboard(Bitmask::Empty) == Bitboard(Bitmask::All));
static_assert(~Bitboard(Bitmask::All) == Bitboard(Bitmask::Empty));

}  // namespace libataxx

#endif
