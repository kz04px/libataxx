#ifndef LIBATAXX_LOOKUP_HPP
#define LIBATAXX_LOOKUP_HPP

#include "bitboard.hpp"
#include "square.hpp"

namespace libataxx::lut {

[[nodiscard]] auto get_singles(const Square sq) noexcept -> Bitboard;

[[nodiscard]] auto get_doubles(const Square sq) noexcept -> Bitboard;

}  // namespace libataxx::lut

#endif
