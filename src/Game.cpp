#include "Game.h"
#include <iostream>
#include "Exceptions.h"

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
        std::cout << board_;
        Player& current = *players_[turn];

        std::pair<int, int> move;
        try {
            // Polymorphism: we don't know (or care) whether this is human or computer.
            move = current.chooseMove(board_);

            if (move.first == Player::UNDO_MOVE) {
                undo(turn);
                continue;
            }
            board_.placeMark(move.first, move.second, current.getSymbol());   // may throw
        } catch (const InvalidMoveException& e) {
            std::cout << "Invalid move: " << e.what() << " Try again.\n";
            continue;
        }
        history_.add(Move(move.first, move.second, current.getSymbol()));

        if (board_.checkWinner() != ' ') {
            std::cout << board_;
            std::cout << current.getName() << " wins!\n";
            return &current;
        }
        if (board_.isFull()) {
            std::cout << board_;
            std::cout << "It's a draw!\n";
            return nullptr;
        }
        turn = 1 - turn;
    }
}
