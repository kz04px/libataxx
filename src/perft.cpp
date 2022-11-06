#include "libataxx/move.hpp"
#include "libataxx/position.hpp"

namespace libataxx {

[[nodiscard]] std::uint64_t Position::perft(const int depth) const noexcept {
    if (depth == 1) {
        return count_legal_moves();
    }
    if (depth == 0) {
        return 1;
    }

    std::uint64_t nodes = 0;
    Move moves[max_moves];
    const int num_moves = legal_moves(moves);

    for (int i = 0; i < num_moves; ++i) {
        const auto npos = after_move<false>(moves[i]);
        nodes += npos.perft(depth - 1);
    }

    return nodes;
}

}  // namespace libataxx
