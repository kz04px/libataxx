#include <iostream>
#include <libataxx/libataxx.hpp>
#include <libataxx/uaiengine.hpp>

using namespace libataxx;
using namespace libataxx::engine;

int main(int argc, char **argv) {
    auto pos = Position("startpos");
    auto engine = UAIEngine("./engine");

    engine.uai();
    engine.set_option("Hash", 1);
    engine.isready();
    engine.uainewgame();
    engine.position(pos);

    engine.add_info_callback(
        [](const std::string &info) { std::cout << info << std::endl; });

    const auto settings = SearchSettings{.type = SearchSettings::Type::Movetime,
                                         .movetime = 3000};

    const auto bestmove = engine.go(settings);
    std::cout << "Bestmove: " << bestmove << std::endl;

    const auto nodes = engine.perft(6);
    std::cout << "Perft 6: " << nodes << std::endl;

    return 0;
}
