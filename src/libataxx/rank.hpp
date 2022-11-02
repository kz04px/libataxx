#ifndef LIBATAXX_RANK_HPP
#define LIBATAXX_RANK_HPP

#include <cstdint>
#include <ostream>

namespace libataxx {

enum class Ranks : int
{
    Rank1 = 0,
    Rank2,
    Rank3,
    Rank4,
    Rank5,
    Rank6,
    Rank7,
};

class Rank {
   public:
    constexpr explicit Rank(const int r) : data_(r) {
    }

    constexpr explicit Rank(const Ranks r) : data_(static_cast<int>(r)) {
    }

    [[nodiscard]] explicit constexpr operator char() const noexcept {
        return '1' + data_;
    }

    [[nodiscard]] explicit constexpr operator int() const noexcept {
        return data_;
    }

    [[nodiscard]] constexpr bool operator==(const Rank &rhs) const noexcept {
        return data_ == rhs.data_;
    }

   private:
    const std::uint8_t data_;
};

inline std::ostream &operator<<(std::ostream &os, const Rank &r) {
    os << static_cast<char>(r);
    return os;
}

static_assert(static_cast<char>(Rank(Ranks::Rank1)) == '1');
static_assert(static_cast<char>(Rank(Ranks::Rank2)) == '2');
static_assert(static_cast<char>(Rank(Ranks::Rank3)) == '3');
static_assert(static_cast<char>(Rank(Ranks::Rank4)) == '4');
static_assert(static_cast<char>(Rank(Ranks::Rank5)) == '5');
static_assert(static_cast<char>(Rank(Ranks::Rank6)) == '6');
static_assert(static_cast<char>(Rank(Ranks::Rank7)) == '7');

static_assert(static_cast<int>(Rank(Ranks::Rank1)) == 0);
static_assert(static_cast<int>(Rank(Ranks::Rank2)) == 1);
static_assert(static_cast<int>(Rank(Ranks::Rank3)) == 2);
static_assert(static_cast<int>(Rank(Ranks::Rank4)) == 3);
static_assert(static_cast<int>(Rank(Ranks::Rank5)) == 4);
static_assert(static_cast<int>(Rank(Ranks::Rank6)) == 5);
static_assert(static_cast<int>(Rank(Ranks::Rank7)) == 6);

}  // namespace libataxx

#endif
