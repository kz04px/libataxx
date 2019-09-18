#ifndef LIBATAXX_RANK_HPP
#define LIBATAXX_RANK_HPP

#include <cstdint>
#include <ostream>

namespace libataxx {

class Rank {
   public:
    constexpr explicit Rank(const uint8_t f) : data_{f} {
    }

    constexpr operator char() const noexcept {
        return '1' + data_;
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

}  // namespace ranks

}  // namespace libataxx

#endif
