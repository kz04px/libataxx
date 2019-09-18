#ifndef LIBATAXX_FILE_HPP
#define LIBATAXX_FILE_HPP

#include <cstdint>
#include <ostream>

namespace libataxx {

class File {
   public:
    constexpr explicit File(const uint8_t f) : data_{f} {
    }

    constexpr operator char() const noexcept {
        return 'a' + data_;
    }

   private:
    const std::uint8_t data_;
};

inline std::ostream &operator<<(std::ostream &os, const File &f) {
    os << static_cast<char>(f);
    return os;
}

namespace files {

constexpr static File A = File{0};
constexpr static File B = File{1};
constexpr static File C = File{2};
constexpr static File D = File{3};
constexpr static File E = File{4};
constexpr static File F = File{5};
constexpr static File G = File{6};

static_assert(A == 'a');
static_assert(B == 'b');
static_assert(C == 'c');
static_assert(D == 'd');
static_assert(E == 'e');
static_assert(F == 'f');
static_assert(G == 'g');

}  // namespace files

}  // namespace libataxx

#endif
