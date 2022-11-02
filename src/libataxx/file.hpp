#ifndef LIBATAXX_FILE_HPP
#define LIBATAXX_FILE_HPP

#include <cstdint>
#include <ostream>

namespace libataxx {

enum class Files : int
{
    FileA = 0,
    FileB,
    FileC,
    FileD,
    FileE,
    FileF,
    FileG,
};

class File {
   public:
    constexpr explicit File(const int f) : data_(f) {
    }

    constexpr explicit File(const Files f) : data_(static_cast<int>(f)) {
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

static_assert(static_cast<char>(File(Files::FileA)) == 'a');
static_assert(static_cast<char>(File(Files::FileB)) == 'b');
static_assert(static_cast<char>(File(Files::FileC)) == 'c');
static_assert(static_cast<char>(File(Files::FileD)) == 'd');
static_assert(static_cast<char>(File(Files::FileE)) == 'e');
static_assert(static_cast<char>(File(Files::FileF)) == 'f');
static_assert(static_cast<char>(File(Files::FileG)) == 'g');

static_assert(static_cast<int>(File(Files::FileA)) == 0);
static_assert(static_cast<int>(File(Files::FileB)) == 1);
static_assert(static_cast<int>(File(Files::FileC)) == 2);
static_assert(static_cast<int>(File(Files::FileD)) == 3);
static_assert(static_cast<int>(File(Files::FileE)) == 4);
static_assert(static_cast<int>(File(Files::FileF)) == 5);
static_assert(static_cast<int>(File(Files::FileG)) == 6);

}  // namespace libataxx

#endif
