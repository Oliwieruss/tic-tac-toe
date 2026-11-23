#include "HumanPlayer.h"
#include <iostream>
#include <limits>
#include <stdexcept>

HumanPlayer::HumanPlayer(const std::string& name, char symbol)
    : Player(name, symbol) {}

std::pair<int, int> HumanPlayer::chooseMove(const Board& /*board*/) const {
    int row, col;
    std::cout << getName() << " (" << getSymbol() << "), enter row and column (1-3), or 0 0 to undo: ";
    if (!(std::cin >> row >> col)) {
        if (std::cin.eof())
            throw std::runtime_error("Input stream closed.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return {-1, -1};                      // invalid -> Game will ask again
    }
    if (row == 0 && col == 0)
        return {UNDO_MOVE, UNDO_MOVE};        // player asked to undo
    return {row - 1, col - 1};                // convert to 0-based
}

bool HumanPlayer::isInteractive() const { return true; }

std::string HumanPlayer::describe() const {
    return "Human: " + Player::describe();
}
