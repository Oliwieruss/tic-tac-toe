#include "MoveHistory.h"
#include <iostream>
#include <stdexcept>

void MoveHistory::add(const Move& move) {
    moves_.push_back(move);
}

bool MoveHistory::removeLast() {
    if (moves_.empty())
        return false;
    moves_.pop_back();
    return true;
}

const Move* MoveHistory::findByTurn(int turn) const {
    if (turn < 1 || turn > static_cast<int>(moves_.size()))
        return nullptr;
    return &moves_[turn - 1];
}

const Move& MoveHistory::last() const {
    if (moves_.empty())
        throw std::out_of_range("The move history is empty.");
    return moves_.back();
}

bool MoveHistory::isEmpty() const { return moves_.empty(); }
std::size_t MoveHistory::size() const { return moves_.size(); }
void MoveHistory::clear() { moves_.clear(); }

void MoveHistory::print() const {
    if (moves_.empty()) {
        std::cout << "No moves yet.\n";
        return;
    }
    for (std::size_t i = 0; i < moves_.size(); ++i)
        std::cout << "  Turn " << (i + 1) << ": " << moves_[i] << "\n";
}
