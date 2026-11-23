#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "=== TIC TAC TOE ===\n"
              << "1. Human vs Human\n"
              << "2. Human vs Computer\n"
              << "Choose mode: ";
    int mode;
    std::cin >> mode;

    std::string name1, name2;
    std::cout << "Name of player 1 (X): ";
    std::cin >> name1;

    std::unique_ptr<Player> p1 = std::make_unique<HumanPlayer>(name1, 'X');
    std::unique_ptr<Player> p2;

    if (mode == 1) {
        std::cout << "Name of player 2 (O): ";
        std::cin >> name2;
        p2 = std::make_unique<HumanPlayer>(name2, 'O');
    } else {
        p2 = std::make_unique<ComputerPlayer>("Computer", 'O');
    }

    try {
        Game game(std::move(p1), std::move(p2));
        game.run();
    } catch (const std::exception& e) {
        std::cout << "\nGame aborted: " << e.what() << "\n";
    }
    return 0;
}
