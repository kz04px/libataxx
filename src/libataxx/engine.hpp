#ifndef LIBATAXX_ENGINE_HPP
#define LIBATAXX_ENGINE_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/process.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include <thread>
#include "move.hpp"
#include "position.hpp"

namespace libataxx::engine {

struct SearchSettings {
   public:
    enum class Type
    {
        Depth = 0,
        Movetime,
        Nodes,
        Time
    };

    Type type = Type::Depth;
    // SearchType::Depth
    int depth = 0;
    // SearchType::Movetime
    int movetime = 0;
    // SearchType::Nodes
    std::uint64_t nodes = 0;
    // SearchType::Time
    int btime = 0;
    int wtime = 0;
    int binc = 0;
    int winc = 0;
    int movestogo = 0;
};

class Engine {
   public:
    [[nodiscard]] bool running() noexcept {
        std::error_code ec;
        child_.running(ec);
        return !static_cast<bool>(ec);
    }

   protected:
    explicit Engine(const std::string &path)
        : out_{ios_}, child_{path, boost::process::std_out > out_, boost::process::std_in < in_} {
    }

    virtual ~Engine() noexcept {
        try {
            ios_.stop();
            if (ios_thread_.joinable()) {
                ios_thread_.join();
            }
            child_.terminate();
        } catch (...) {
        }
    }

    void listen() noexcept {
        start();
        ios_thread_ = std::thread([&]() {
            for (;;) {
                try {
                    ios_.run();
                    break;
                } catch (std::exception &e) {
                    std::cerr << "io_service exception: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "io_service exception" << std::endl;
                }
            }
        });
    }

    void send(const std::string &line) noexcept {
        in_ << line << std::endl;
    }

    void start() {
        boost::asio::async_read_until(out_,
                                      buf_,
                                      '\n',
                                      boost::bind(&Engine::handle_recv,
                                                  this,
                                                  boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred));
    }

    virtual void recv(const std::string &line) = 0;

    [[nodiscard]] virtual Move go(const SearchSettings &settings) = 0;

    [[nodiscard]] virtual std::uint64_t perft(const int depth) noexcept = 0;

    virtual void position(const Position &pos) noexcept = 0;

    virtual void quit() noexcept = 0;

    virtual bool set_option(const std::string &name, const int value) noexcept = 0;

    virtual bool set_option(const std::string &name, const std::string &value) noexcept = 0;

    virtual bool set_option(const std::string &name, const char *value) noexcept = 0;

    virtual bool set_option(const std::string &name, const bool value) noexcept = 0;

   private:
    void handle_recv(const boost::system::error_code &ec, [[maybe_unused]] const std::size_t size) {
        if (!ec) {
            std::istream is(&buf_);
            std::string line;
            std::getline(is, line);
            recv(line);
        }

        start();
    }

    // Process
    std::thread ios_thread_;
    boost::asio::io_service ios_;
    boost::asio::streambuf buf_;
    boost::process::opstream in_;
    boost::process::async_pipe out_;
    boost::process::child child_;
};

}  // namespace libataxx::engine

#endif
