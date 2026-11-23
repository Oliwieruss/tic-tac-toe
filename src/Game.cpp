#include "Game.h"
#include <iostream>

Game::Game(std::unique_ptr<Player> first, std::unique_ptr<Player> second) {
    players_[0] = std::move(first);
    players_[1] = std::move(second);
}

const Player& Game::getPlayer(int index) const { return *players_[index]; }
const MoveHistory& Game::getHistory() const { return history_; }

void Game::undo(int& turn) {
    if (history_.isEmpty()) {
        std::cout << "Nothing to undo.\n";
        return;
    }
    // Take back the last move; if that leaves a computer to move,
    // also take back the human's own move so the human can play again.
    do {
        const Move& m = history_.last();
        board_.clearCell(m.getRow(), m.getCol());
        history_.removeLast();
        turn = 1 - turn;
    } while (!players_[turn]->isInteractive() && !history_.isEmpty());
    std::cout << "Move undone.\n";
}

const Player* Game::run() {
    board_.reset();
    history_.clear();
    int turn = 0;

    std::cout << "\n" << players_[0]->describe() << "  vs  " << players_[1]->describe() << "\n";

    while (true) {
        board_.print();
        Player& current = *players_[turn];

        // Polymorphism: we don't know (or care) whether this is human or computer.
        auto [row, col] = current.chooseMove(board_);

        if (row == Player::UNDO_MOVE) {
            undo(turn);
            continue;
        }

        if (!board_.placeMark(row, col, current.getSymbol())) {
            std::cout << "Invalid move, try again.\n";
            continue;
        }
        history_.add(Move(row, col, current.getSymbol()));

        if (board_.checkWinner() != ' ') {
            board_.print();
            std::cout << current.getName() << " wins!\n";
            return &current;
        }
        if (board_.isFull()) {
            board_.print();
            std::cout << "It's a draw!\n";
            return nullptr;
        }
        turn = 1 - turn;
    }
}
