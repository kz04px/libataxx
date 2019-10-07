#ifndef LIBATAXX_RANK_HPP
#define LIBATAXX_RANK_HPP

#include <cstdint>
#include <ostream>

namespace libataxx {

class Rank {
   public:
    constexpr explicit Rank(const int r) : data_(r) {
    }

    explicit constexpr operator char() const noexcept {
        return '1' + data_;
    }

    explicit constexpr operator int() const noexcept {
        return data_;
    }

    constexpr bool operator==(const Rank &rhs) const noexcept {
        return data_ == rhs.data_;
    }

   private:
    const std::uint8_t data_;
};

inline std::ostream &operator<<(std::ostream &os, const Rank &r) {
    os << static_cast<char>(r);
    return os;
}

namespace ranks {

constexpr static Rank A = Rank{0};
constexpr static Rank B = Rank{1};
constexpr static Rank C = Rank{2};
constexpr static Rank D = Rank{3};
constexpr static Rank E = Rank{4};
constexpr static Rank F = Rank{5};
constexpr static Rank G = Rank{6};

static_assert(static_cast<char>(A) == '1');
static_assert(static_cast<char>(B) == '2');
static_assert(static_cast<char>(C) == '3');
static_assert(static_cast<char>(D) == '4');
static_assert(static_cast<char>(E) == '5');
static_assert(static_cast<char>(F) == '6');
static_assert(static_cast<char>(G) == '7');

static_assert(static_cast<int>(A) == 0);
static_assert(static_cast<int>(B) == 1);
static_assert(static_cast<int>(C) == 2);
static_assert(static_cast<int>(D) == 3);
static_assert(static_cast<int>(E) == 4);
static_assert(static_cast<int>(F) == 5);
static_assert(static_cast<int>(G) == 6);

}  // namespace ranks

}  // namespace libataxx

#endif
