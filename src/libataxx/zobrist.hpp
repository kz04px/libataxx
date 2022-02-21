#ifndef ZOBRIST_HPP
#define ZOBRIST_HPP

#include <cstdint>
#include "piece.hpp"
#include "square.hpp"

namespace {

constexpr const std::uint64_t turn = 0x2e98304a94e1000d;
constexpr const std::uint64_t piece[3][49] = {
    {
        0xddd67db865dc92f9, 0x31ad7f3d49884764, 0xfc810e82600d77ed, 0xa329bc2fe9a585c2, 0x0dd7013c7b5f9ee0,
        0xcbfb18e330c5152b, 0x5ca13c8237e969f0, 0xcfe82be3298f4860, 0xd74ee79ab8cd59d4, 0x76c9804b3dd3dd9a,
        0x62fe43ac3416344b, 0x84f44cfc5640f1fb, 0xee80f44f274d194f, 0x9e132307eaa1062a, 0x8ef3b83e05104b8c,
        0x7458cb4e38a56b1b, 0x496ae857824032b5, 0x297892ab4aed9139, 0x2c63a6ed1e5c503b, 0xb806e46b057da75c,
        0x8e3ee3fc5ea21f4d, 0x7bb71073c6b32631, 0xa34cbc35fea7986d, 0x2cf34121f29c2073, 0x3ff14ac1cfb3ac44,
        0x9a1f60c67467b9eb, 0x4f69347f2d665427, 0x4d51d73c213217bc, 0x6b3089c84d5d78e3, 0xa2923e3c0bbc0f50,
        0xe4931d122c14c947, 0xa1b03c639fe421a7, 0x2789a4dc1574310c, 0x4e3f96a633e0ede0, 0xe4f29bf5ff2869df,
        0x72e7fe1c77af10b3, 0x245e4d0677acbd90, 0x5eb16a0a6cff1f55, 0x26e93216b330c067, 0x0eced566d7522ad3,
        0xdc64bc04aa39e421, 0x401987ae3cb114db, 0xd0d0b88ece5f0c16, 0x13275209f4ddff5a, 0xffb20d8b83a2ce28,
        0x8f2100bf98b54217, 0x3769a2d70b7209e7, 0x61b3cca215f1a975, 0x8d1158e421453a0f,
    },
    {
        0xd33fd8453c18380c, 0xd7949af7fa5e24ca, 0xa75e294be7913781, 0x3b615f1e3322be8c, 0xe4c885ecb48d6187,
        0x9b92f432a8d105f3, 0xbff867477fb93a23, 0x5ff3e0b5e6e72ab4, 0xe60144f2900bc655, 0xf29a0de00bdc3aee,
        0xde9e042c06230fd8, 0x4264ec62f70ba708, 0x5f175b53ebb138c7, 0x439e71025499179e, 0xcf39b10d6a8437fd,
        0x0fcf1fc30f9e0de4, 0x6a502645f6a31fef, 0xd47dd00cf21ddfdd, 0x7e4ca0ec0c2e7f68, 0x37401f0941e5a469,
        0x3efddb557fd01cb4, 0x846bfb50b6965c90, 0xc0fa4a424c735605, 0xe5fbff674c562239, 0x3826959008ef40f0,
        0x4a712b5964a4b7a1, 0x68f594a0740c456f, 0x1ee9e39d56bd32e6, 0x08ebd76592898d31, 0x3df7c91613fb946d,
        0xef3e760a57d5a399, 0x6ef3128154e16b88, 0x15e27065e3d4c108, 0xd5fe096a16b5eed2, 0xb2964fa8f1bddad1,
        0x3ebb6f3af8a61dc5, 0x9776dc9ebc5243d2, 0x4660bff8b53c4a78, 0x73507ecb48163932, 0x05967644e76ae2f8,
        0x9c53ce9f0fdcb066, 0xcf6e214c6acea558, 0x53ee7540169475d8, 0xc8a49004b87946b8, 0x1d75d48ff9dc94b2,
        0xec4f8821305bbd96, 0x43ed7506a2bd6b16, 0xf0eb5d0784e3eb03, 0xe578cac94b342a86,
    },
    {
        0x389334c091fb178b, 0xc49c74fe672eef1b, 0x47b26673e8ecc2c9, 0x9517104b5b229a11, 0x7a1539922694facb,
        0x001c0d1c373673c9, 0x19581df3ba523ca3, 0xf93dd0859efb8f2d, 0x650a5e8c62abbc36, 0x344ed312359ba06b,
        0xac1bdf2dbfa24510, 0xe78cde9f2c94bbf7, 0xe99f05db53ad88e5, 0xe5de28e3f5427a54, 0x40cf50c653126026,
        0x0798412d65bc843a, 0x4d61778f9912d6b8, 0xc41d7c84d36878df, 0xe82b78b989bd55f4, 0x1190749dddf654a2,
        0x65dc06cc2f2bfa20, 0x3144a986fd0d7827, 0x0db1ce137155befc, 0x4d2653580bf0680d, 0x93aea07a37dd1736,
        0x15796cdff212d202, 0x461c4b3999ce2ed6, 0x331fb5d0ea1a69fa, 0xef87dadc7f28dde8, 0x22dca43f46365b6a,
        0x623a22e748384539, 0x5dd89fd95c4d5ec6, 0x790d810b6bd0dcbc, 0xe06e78818f6864f6, 0xd4378e7b03088634,
        0x6ceb024e247cd217, 0x93f15442fcce0a55, 0x154eab5e8620744c, 0x65d3884620d69fb0, 0xb1fed42a7eb9f02b,
        0xf8e0a7acdfdd769d, 0x5b660b56b0e029d5, 0x81d29d5e7aad71e9, 0xb444e414c4573be8, 0xea73727ec09846e1,
        0xb561a7c25264c71a, 0x7feda459b0c22d55, 0x788e4b767d5f8b00, 0x36995517712d9e10,
    },
};

}  // namespace

namespace libataxx::zobrist {

[[nodiscard]] constexpr std::uint64_t turn_key() {
    return turn;
}

[[nodiscard]] constexpr std::uint64_t get_key(const Piece &p, const Square &sq) {
    return piece[static_cast<int>(p)][sq.index()];
}

}  // namespace libataxx::zobrist

#endif
