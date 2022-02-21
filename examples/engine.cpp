#include <iostream>
#include <libataxx/libataxx.hpp>
#include <libataxx/uaiengine.hpp>

int main(int argc, char **argv) {
    std::string fen = "startpos";
    std::string path;

    int param = 0;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--fen") {
            fen.clear();
            param = 1;
        } else if (std::string(argv[i]) == "--engine") {
            param = 2;
        } else {
            if (param == 1) {
                fen += (fen.empty() ? "" : " ") + std::string(argv[i]);
            } else if (param == 2) {
                path += (path.empty() ? "" : " ") + std::string(argv[i]);
            }
        }
    }

    if (path.empty()) {
        return 1;
    }

    try {
        auto pos = libataxx::Position(fen);
        auto engine = libataxx::engine::UAIEngine(path);

        engine.uai();
        engine.set_option("Hash", 1);
        engine.isready();
        engine.uainewgame();
        engine.position(pos);

        engine.add_info_callback([](const std::string &info) { std::cout << info << std::endl; });

        const auto settings = libataxx::engine::SearchSettings{.type = libataxx::engine::SearchSettings::Type::Movetime,
                                                               .movetime = 3000};

        const auto bestmove = engine.go(settings);
        std::cout << "Bestmove: " << bestmove << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
