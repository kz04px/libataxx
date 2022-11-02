#include <libataxx/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::get_result()") {
    const std::pair<std::string, libataxx::Result> positions[] = {
        {"x5o/7/7/7/7/7/o5x x 0 1", libataxx::Result::None},
        {"7/7/7/7/7/7/7 x 0 1", libataxx::Result::Draw},
        {"7/7/7/7/7/7/7 o 0 1", libataxx::Result::Draw},
        // All captured
        {"x6/7/7/7/7/7/7 x 0 1", libataxx::Result::BlackWin},
        {"x6/7/7/7/7/7/7 o 0 1", libataxx::Result::BlackWin},
        {"o6/7/7/7/7/7/7 x 0 1", libataxx::Result::WhiteWin},
        {"o6/7/7/7/7/7/7 o 0 1", libataxx::Result::WhiteWin},
        // No empty squares left
        {"xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx x 0 1", libataxx::Result::BlackWin},
        {"xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx/xxxxxxx o 0 1", libataxx::Result::BlackWin},
        {"ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo x 0 1", libataxx::Result::WhiteWin},
        {"ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo/ooooooo o 0 1", libataxx::Result::WhiteWin},
        {"ooooooo/ooooooo/ooooooo/oooxxxx/xxxxxxx/xxxxxxx/xxxxxxx x 0 1", libataxx::Result::BlackWin},
        {"ooooooo/ooooooo/ooooooo/oooxxxx/xxxxxxx/xxxxxxx/xxxxxxx o 0 1", libataxx::Result::BlackWin},
        {"ooooooo/ooooooo/ooooooo/ooooxxx/xxxxxxx/xxxxxxx/xxxxxxx x 0 1", libataxx::Result::WhiteWin},
        {"ooooooo/ooooooo/ooooooo/ooooxxx/xxxxxxx/xxxxxxx/xxxxxxx o 0 1", libataxx::Result::WhiteWin},
        {"ooooooo/ooooooo/ooooooo/ooo-xxx/xxxxxxx/xxxxxxx/xxxxxxx x 0 1", libataxx::Result::Draw},
        {"ooooooo/ooooooo/ooooooo/ooo-xxx/xxxxxxx/xxxxxxx/xxxxxxx o 0 1", libataxx::Result::Draw},
        // 50 move rule
        {"x5o/7/7/7/7/7/o5x x 99 1", libataxx::Result::None},
        {"x5o/7/7/7/7/7/o5x x 100 1", libataxx::Result::Draw},
        {"xxo4/7/7/7/7/7/7 x 100 1", libataxx::Result::Draw},
        {"xxo4/7/7/7/7/7/7 o 100 1", libataxx::Result::Draw},
        {"oox4/7/7/7/7/7/7 x 100 1", libataxx::Result::Draw},
        {"oox4/7/7/7/7/7/7 o 100 1", libataxx::Result::Draw},
        // Wins take priority over the 50 move rule
        {"7/7/7/7/-------/-------/xxxxooo x 100 1", libataxx::Result::BlackWin},
        {"7/7/7/7/-------/-------/xxxxooo o 100 1", libataxx::Result::BlackWin},
        {"7/7/7/7/-------/-------/xxxoooo x 100 1", libataxx::Result::WhiteWin},
        {"7/7/7/7/-------/-------/xxxoooo o 100 1", libataxx::Result::WhiteWin},
        // No moves left
        {"7/7/7/7/-------/-------/xxxxooo x 0 1", libataxx::Result::BlackWin},
        {"7/7/7/7/-------/-------/xxxxooo o 0 1", libataxx::Result::BlackWin},
        {"7/7/7/7/-------/-------/xxxoooo x 0 1", libataxx::Result::WhiteWin},
        {"7/7/7/7/-------/-------/xxxoooo o 0 1", libataxx::Result::WhiteWin},
        {"7/7/7/7/-------/-------/xxx-ooo x 0 1", libataxx::Result::Draw},
        {"7/7/7/7/-------/-------/xxx-ooo o 0 1", libataxx::Result::Draw},
    };

    for (const auto& [fen, result] : positions) {
        libataxx::Position pos{fen};
        REQUIRE(pos.get_result() == result);
    }
}
