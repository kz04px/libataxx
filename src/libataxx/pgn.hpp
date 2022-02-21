#ifndef LIBATAXX_PGN_HPP
#define LIBATAXX_PGN_HPP

#include <optional>
#include <ostream>
#include <string>
#include <vector>
#include "move.hpp"

namespace libataxx::pgn {

class Node {
   public:
    Node() : parent_{}, move_{}, ply_{0}, comment_{}, children_{} {
    }

    Node(const Node *parent, const Move move, const int ply)
        : parent_{parent}, move_{move}, ply_{ply}, comment_{}, children_{} {
    }

    [[nodiscard]] constexpr bool is_root() const noexcept {
        return parent_ == nullptr;
    }

    [[nodiscard]] bool has_children() const noexcept {
        return !children_.empty();
    }

    [[nodiscard]] bool has_comment() const noexcept {
        return !comment_.empty();
    }

    [[nodiscard]] const std::string &comment() const noexcept {
        return comment_;
    }

    void add_comment(const std::string &comment) noexcept {
        if (comment_.empty()) {
            comment_ = comment;
        } else {
            comment_ += " " + comment;
        }
    }

    [[nodiscard]] std::vector<Move> mainline() const noexcept {
        std::vector<Move> pv;
        const Node *current = this;
        while (current->has_children()) {
            current = &current->children_[0];
            pv.push_back(current->move_);
        }
        return pv;
    }

    [[nodiscard]] constexpr const std::vector<Node> &children() const noexcept {
        return children_;
    }

    [[nodiscard]] constexpr Move move() const noexcept {
        return move_;
    }

    [[nodiscard]] constexpr int ply() const noexcept {
        return ply_;
    }

    [[nodiscard]] constexpr const Node *parent() const noexcept {
        return parent_;
    }

    [[nodiscard]] std::size_t num_children() const noexcept {
        return children_.size();
    }

    Node *add_mainline(const Move &move) noexcept {
        children_.insert(children_.begin(), Node{this, move, ply_ + 1});
        return &children_.front();
    }

    Node *add_variation(const Move &move) {
        children_.push_back(Node{this, move, ply_});
        return &children_.back();
    }

    [[nodiscard]] explicit operator std::string() const noexcept {
        std::string str;

        // Move number
        if (parent() && (ply() % 2 == 1 || parent()->num_children() > 1 || parent()->has_comment())) {
            const int move_num = (ply() + 1) / 2;

            if (ply() % 2 == 1) {
                str += std::to_string(move_num) + ". ";
            } else {
                str += std::to_string(move_num) + "... ";
            }
        }

        // Move
        if (!is_root()) {
            str += static_cast<std::string>(move());
        }

        // Comment
        if (has_comment()) {
            str += " { " + comment() + " }";
        }

        // Variations
        for (std::size_t i = 1; i < num_children(); ++i) {
            str += " (" + static_cast<std::string>(children().at(i)) + ")";
        }

        // Spacer
        if (!is_root() && has_children()) {
            str += " ";
        }

        // Mainline
        if (has_children()) {
            str += static_cast<std::string>(children().at(0));
        }

        return str;
    }

   private:
    const Node *parent_;
    Move move_;
    int ply_;
    std::string comment_;
    std::vector<Node> children_;
};

class Header {
   public:
    Header() {
    }

    void add(const std::string &key, const std::string &value) noexcept {
        stuff_.push_back({key, value});
    }

    [[nodiscard]] std::optional<std::string> get(const std::string &k) const noexcept {
        for (const auto &[key, val] : stuff_) {
            if (key == k) {
                return val;
            }
        }
        return {};
    }

    [[nodiscard]] const auto &items() const noexcept {
        return stuff_;
    }

   private:
    std::vector<std::pair<std::string, std::string>> stuff_;
};

class PGN {
   public:
    PGN() {
    }

    [[nodiscard]] Header &header() noexcept {
        return header_;
    }

    [[nodiscard]] const Header &header() const noexcept {
        return header_;
    }

    [[nodiscard]] Node *root() noexcept {
        return &root_;
    }

    [[nodiscard]] const Node &root() const noexcept {
        return root_;
    }

   private:
    Header header_;
    Node root_;
};

inline std::ostream &operator<<(std::ostream &os, const PGN &pgn) {
    std::string str;

    // Header
    for (const auto &[key, value] : pgn.header().items()) {
        str += "[" + key + " \"" + value + "\"]\n";
    }
    str += '\n';

    // Nodes
    str += static_cast<std::string>(pgn.root());

    // Result
    str += " " + pgn.header().get("Result").value_or("*") + "\n\n";

    // Write
    os << str;

    return os;
}

}  // namespace libataxx::pgn

#endif
