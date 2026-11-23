#include "Game.h"
#include <iostream>

Game::Game(std::unique_ptr<Player> first, std::unique_ptr<Player> second) {
    players_[0] = std::move(first);
    players_[1] = std::move(second);
}

void Game::run() {
    board_.reset();
    int turn = 0;

    std::cout << "\n" << players_[0]->describe() << "  vs  " << players_[1]->describe() << "\n";

    while (true) {
        board_.print();
        Player& current = *players_[turn];

        // Polymorphism: we don't know (or care) whether this is human or computer.
        auto [row, col] = current.chooseMove(board_);

        if (!board_.placeMark(row, col, current.getSymbol())) {
            std::cout << "Invalid move, try again.\n";
            continue;
        }

        if (board_.checkWinner() != ' ') {
            board_.print();
            std::cout << current.getName() << " wins!\n";
            return;
        }
        if (board_.isFull()) {
            board_.print();
            std::cout << "It's a draw!\n";
            return;
        }
        turn = 1 - turn;
    }
}
