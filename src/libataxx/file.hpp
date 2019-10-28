#ifndef LIBATAXX_FILE_HPP
#define LIBATAXX_FILE_HPP

#include <cstdint>
#include <ostream>

namespace libataxx {

class File {
   public:
    constexpr explicit File(const int f) : data_(f) {
    }

    [[nodiscard]] explicit constexpr operator char() const noexcept {
        return 'a' + data_;
    }

    [[nodiscard]] explicit constexpr operator int() const noexcept {
        return data_;
    }

    [[nodiscard]] constexpr bool operator==(const File &rhs) const noexcept {
        return data_ == rhs.data_;
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

static_assert(static_cast<char>(A) == 'a');
static_assert(static_cast<char>(B) == 'b');
static_assert(static_cast<char>(C) == 'c');
static_assert(static_cast<char>(D) == 'd');
static_assert(static_cast<char>(E) == 'e');
static_assert(static_cast<char>(F) == 'f');
static_assert(static_cast<char>(G) == 'g');

static_assert(static_cast<int>(A) == 0);
static_assert(static_cast<int>(B) == 1);
static_assert(static_cast<int>(C) == 2);
static_assert(static_cast<int>(D) == 3);
static_assert(static_cast<int>(E) == 4);
static_assert(static_cast<int>(F) == 5);
static_assert(static_cast<int>(G) == 6);

}  // namespace files

}  // namespace libataxx

#endif
