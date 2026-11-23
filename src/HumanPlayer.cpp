#include "HumanPlayer.h"
#include <iostream>
#include <limits>
#include "Exceptions.h"

HumanPlayer::HumanPlayer(const std::string& name, char symbol)
    : Player(name, symbol) {}

std::pair<int, int> HumanPlayer::chooseMove(const Board& /*board*/) const {
    int row, col;
    std::cout << getName() << " (" << getSymbol() << "), enter row and column (1-3), or 0 0 to undo: ";
    if (!(std::cin >> row >> col)) {
        if (std::cin.eof())
            throw InputClosedException();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidMoveException("Please enter two numbers, e.g. 2 3.");
    }
    if (row == 0 && col == 0)
        return {UNDO_MOVE, UNDO_MOVE};        // player asked to undo
    return {row - 1, col - 1};                // convert to 0-based
}

bool HumanPlayer::isInteractive() const { return true; }

std::string HumanPlayer::describe() const {
    return "Human: " + Player::describe();
}
