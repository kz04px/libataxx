#ifndef LIBATAXX_PGN_HPP
#define LIBATAXX_PGN_HPP

#include <optional>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "move.hpp"

namespace libataxx {

namespace pgn {

static const std::string header_order[] = {"Event",
                                           "Site",
                                           "Date",
                                           "Round",
                                           "Black",
                                           "White",
                                           "Result",
                                           "Score",
                                           "FEN",
                                           "TimeControl"};

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
        comment_ = comment;
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

   private:
    const Node *parent_;
    Move move_;
    int ply_;
    std::string comment_;
    std::vector<Node> children_;
};

class Header {
   public:
    Header() : stuff_{{"Event", "*"}, {"Result", "*"}} {
    }

    void add(const std::string &key, const std::string &value) noexcept {
        stuff_[key] = value;
    }

    [[nodiscard]] bool has(const std::string &key) const noexcept {
        return stuff_.find(key) != stuff_.end();
    }

    [[nodiscard]] std::optional<std::string> get(const std::string &key) const
        noexcept {
        if (!has(key)) {
            return {};
        }
        return stuff_.at(key);
    }

    [[nodiscard]] const auto &items() const noexcept {
        return stuff_;
    }

   private:
    std::unordered_map<std::string, std::string> stuff_;
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

inline std::ostream &operator<<(std::ostream &os, const Node &node) {
    // Move number
    if (node.parent() &&
        (node.ply() % 2 == 1 || node.parent()->num_children() > 1 ||
         node.parent()->has_comment())) {
        const int move_num = (node.ply() + 1) / 2;

        if (node.ply() % 2 == 1) {
            os << move_num << ". ";
        } else {
            os << move_num << "... ";
        }
    }

    // Move
    if (!node.is_root()) {
        os << node.move();
    }

    // Comment
    if (node.has_comment()) {
        os << " { " << node.comment() << " }";
    }

    // Variations
    for (std::size_t i = 1; i < node.num_children(); ++i) {
        os << " (" << node.children().at(i) << ")";
    }

    // Spacer
    if (!node.is_root() && (node.has_comment() || node.has_children())) {
        os << " ";
    }

    // Mainline
    if (node.has_children()) {
        os << node.children().at(0);
    }

    return os;
}

inline std::ostream &operator<<(std::ostream &os, const PGN &pgn) {
    // Header -- Event
    os << "[Event \"" << pgn.header().get("Event").value() << "\"]\n";

    // Header -- unordered
    for (const auto &[key, value] : pgn.header().items()) {
        if (key == "Event") {
            continue;
        }
        os << "[" << key << " \"" << value << "\"]\n";
    }
    os << '\n';

    // Nodes
    os << pgn.root() << " " << pgn.header().get("Result").value();
    os << "\n\n";

    return os;
}

}  // namespace pgn

}  // namespace libataxx

#endif
