#include <iostream>
#include <libataxx/libataxx.hpp>
#include <libataxx/uaiengine.hpp>

using namespace libataxx;
using namespace libataxx::engine;

int main(int argc, char **argv) {
    std::string fen = "startpos";
    std::string path = "";

    int param = 0;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--fen") {
            fen = "";
            param = 1;
        } else if (std::string(argv[i]) == "--engine") {
            path = "";
            param = 2;
        } else {
            if (param == 1) {
                fen += (fen == "" ? "" : " ") + std::string(argv[i]);
            } else if (param == 2) {
                path += (path == "" ? "" : " ") + std::string(argv[i]);
            }
        }
    }

    if (path == "") {
        return 1;
    }

    auto pos = Position(fen);
    auto engine = UAIEngine(path);

    engine.uai();
    engine.set_option("Hash", 1);
    engine.isready();
    engine.uainewgame();
    engine.position(pos);

    engine.add_info_callback([](const std::string &info) { std::cout << info << std::endl; });

    const auto settings = SearchSettings{.type = SearchSettings::Type::Movetime, .movetime = 3000};

    const auto bestmove = engine.go(settings);
    std::cout << "Bestmove: " << bestmove << std::endl;

    return 0;
}
