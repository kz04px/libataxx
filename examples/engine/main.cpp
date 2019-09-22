#include <iostream>
#include <libataxx/libataxx.hpp>
#include <libataxx/uaiengine.hpp>

using namespace libataxx;
using namespace libataxx::engine;

int main(int argc, char **argv) {
    auto pos = Position("startpos");
    auto engine = UAIEngine("./engine");

    engine.uai();
    engine.isready();
    engine.uainewgame();
    engine.position(pos);

    const auto settings = SearchSettings{.type = SearchSettings::Type::Movetime,
                                         .movetime = 3000};
    std::cout << "Bestmove: " << engine.go(settings) << std::endl;
    std::cout << "Perft 6: " << engine.perft(6) << std::endl;

    return 0;
}
