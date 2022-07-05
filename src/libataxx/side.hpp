#ifndef LIBATAXX_SIDE_HPP
#define LIBATAXX_SIDE_HPP

#include <ostream>

namespace libataxx {

enum class Side : bool
{
    Black = false,
    White
};

inline std::ostream &operator<<(std::ostream &os, const Side &s) {
    if (s == Side::Black) {
        os << "Black";
    } else {
        os << "White";
    }
    return os;
}

constexpr inline Side operator!(const Side &side) {
    return static_cast<Side>(!static_cast<bool>(side));
}

static_assert((!Side::Black) == Side::White);
static_assert((!Side::White) == Side::Black);
static_assert(Side::Black == Side::Black);
static_assert(Side::White == Side::White);

}  // namespace libataxx

#endif
