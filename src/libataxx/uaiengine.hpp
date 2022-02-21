#ifndef LIBATAXX_UAIENGINE_HPP
#define LIBATAXX_UAIENGINE_HPP

#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>
#include <vector>
#include "engine.hpp"

namespace libataxx {

namespace engine {

class UAIEngine : public Engine {
   public:
    explicit UAIEngine(const std::string &path) : Engine{path} {
        listen();
    }

    void uai() noexcept {
        if (uaiok_received) {
            return;
        }
        std::unique_lock<std::mutex> lock(mtx_);
        send("uai");
        cv_uaiok_.wait(lock, [&] { return uaiok_received; });
    }

    void isready() noexcept {
        std::unique_lock<std::mutex> lock(mtx_);
        readyok_received = false;
        send("isready");
        cv_readyok_.wait(lock, [&] { return readyok_received; });
    }

    void uainewgame() noexcept {
        send("uainewgame");
    }

    [[nodiscard]] Move go(const SearchSettings &settings) override {
        std::unique_lock<std::mutex> lock(mtx_);
        bestmove_received = false;

        switch (settings.type) {
            case SearchSettings::Type::Depth:
                if (settings.depth < 1) {
                    throw std::invalid_argument("Depth must be >= 1");
                }
                send("go depth " + std::to_string(settings.depth));
                break;
            case SearchSettings::Type::Movetime:
                if (settings.movetime < 1) {
                    throw std::invalid_argument("Movetime must be >= 1");
                }
                send("go movetime " + std::to_string(settings.movetime));
                break;
            case SearchSettings::Type::Nodes:
                if (settings.nodes == 0ULL) {
                    throw std::invalid_argument("Nodes must be >= 1");
                }
                send("go nodes " + std::to_string(settings.nodes));
                break;
            case SearchSettings::Type::Time:
                if (settings.btime < 0 || settings.wtime < 0) {
                    throw std::invalid_argument("btime and wtime must be >= 0");
                }
                send("go btime " + std::to_string(settings.btime) + " wtime " + std::to_string(settings.wtime) +
                     " binc " + std::to_string(settings.binc) + " winc " + std::to_string(settings.winc));
                break;
            default:
                throw std::invalid_argument("Invalid search type");
        }

        cv_bestmove_.wait(lock, [&] { return bestmove_received; });
        return bestmove_;
    }

    [[nodiscard]] std::uint64_t perft(const int depth) noexcept override {
        std::unique_lock<std::mutex> lock(mtx_);
        nodes_received = false;
        send("perft " + std::to_string(depth));
        cv_nodes_.wait(lock, [&] { return nodes_received; });
        return nodes_;
    }

    void position(const Position &pos) noexcept override {
        send("position fen " + pos.get_fen());
    }

    void quit() noexcept override {
        send("quit");
    }

    bool set_option(const std::string &name, const int value) noexcept override {
        if (!uaiok_received) {
            return false;
        }
        send("setoption name " + name + " value " + std::to_string(value));
        return true;
    }

    bool set_option(const std::string &name, const std::string &value) noexcept override {
        if (!uaiok_received) {
            return false;
        }
        send("setoption name " + name + " value " + value);
        return true;
    }

    bool set_option(const std::string &name, const char *value) noexcept override {
        return set_option(name, std::string(value));
    }

    bool set_option(const std::string &name, const bool value) noexcept override {
        if (!uaiok_received) {
            return false;
        }
        send("setoption name " + name + " value " + (value ? "true" : "false"));
        return true;
    }

    void add_info_callback(const std::function<void(const std::string &info)> func) noexcept {
        info_callbacks_.push_back(func);
    }

   private:
    void recv(const std::string &line) override {
        std::stringstream ss{line};

        std::string word;
        if (ss >> word) {
            if (word == "uaiok") {
                std::lock_guard<std::mutex> lock(mtx_);
                uaiok_received = true;
                cv_uaiok_.notify_one();
            } else if (word == "readyok") {
                std::lock_guard<std::mutex> lock(mtx_);
                readyok_received = true;
                cv_readyok_.notify_one();
            } else if (word == "bestmove") {
                ss >> word;
                bestmove_ = Move::from_uai(word);
                std::lock_guard<std::mutex> lock(mtx_);
                bestmove_received = true;
                cv_bestmove_.notify_one();
            } else if (word == "nodes") {
                ss >> word;
                nodes_ = std::stoull(word);
                std::lock_guard<std::mutex> lock(mtx_);
                nodes_received = true;
                cv_nodes_.notify_one();
            } else if (word == "info") {
                for (const auto &func : info_callbacks_) {
                    func(line);
                }
            }
        }
    }

   private:
    Move bestmove_;
    std::uint64_t nodes_;
    std::mutex mtx_;
    std::condition_variable cv_uaiok_;
    std::condition_variable cv_readyok_;
    std::condition_variable cv_bestmove_;
    std::condition_variable cv_nodes_;
    bool uaiok_received{false};
    bool readyok_received{false};
    bool bestmove_received{false};
    bool nodes_received{false};
    std::vector<std::function<void(const std::string &info)>> info_callbacks_;
};

}  // namespace engine

}  // namespace libataxx

#endif
