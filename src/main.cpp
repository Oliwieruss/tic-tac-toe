#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "ComputerPlayer.h"
#include "Game.h"
#include "HumanPlayer.h"
#include "ScoreBoard.h"

// Reads one non-empty line (skips blank lines left over from earlier input).
static std::string readLine(const std::string& prompt) {
    std::string line;
    do {
        std::cout << prompt;
        if (!std::getline(std::cin, line))
            throw std::runtime_error("Input stream closed.");
    } while (line.empty());
    return line;
}

static int readInt(const std::string& prompt) {
    while (true) {
        std::string line = readLine(prompt);
        try {
            return std::stoi(line);
        } catch (const std::exception&) {
            std::cout << "Please enter a number.\n";
        }
    }
}

static void playGame(ScoreBoard& scoreBoard) {
    int mode = 0;
    while (mode != 1 && mode != 2)
        mode = readInt("1. Human vs Human\n2. Human vs Computer\nChoose mode: ");

    std::string name1 = readLine("Name of player 1 (X): ");
    std::unique_ptr<Player> p1 = std::make_unique<HumanPlayer>(name1, 'X');
    std::unique_ptr<Player> p2;

    if (mode == 1) {
        std::string name2 = readLine("Name of player 2 (O): ");
        p2 = std::make_unique<HumanPlayer>(name2, 'O');
    } else {
        p2 = std::make_unique<ComputerPlayer>("Computer", 'O');
    }

    Game game(std::move(p1), std::move(p2));
    const Player* winner = game.run();

    const Player& a = game.getPlayer(0);
    const Player& b = game.getPlayer(1);
    if (winner == nullptr)
        scoreBoard.recordDraw(a.getName(), b.getName());
    else if (winner == &a)
        scoreBoard.recordWin(a.getName(), b.getName());
    else
        scoreBoard.recordWin(b.getName(), a.getName());

    // Move history: list it and let the user look up a single turn.
    std::cout << "\nMove history:\n";
    game.getHistory().print();
    while (true) {
        int turn = readInt("Look up a turn (0 to continue): ");
        if (turn == 0) break;
        const Move* m = game.getHistory().findByTurn(turn);
        if (m)
            std::cout << "  Turn " << turn << ": " << m->describe() << "\n";
        else
            std::cout << "  No such turn.\n";
    }
}

static void showMenu() {
    std::cout << "\n=== TIC TAC TOE ===\n"
              << "1. Play a game\n"
              << "2. Show scoreboard\n"
              << "3. Add player\n"
              << "4. Find player\n"
              << "5. Rename player\n"
              << "6. Remove player\n"
              << "0. Exit\n";
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    ScoreBoard scoreBoard;

    try {
        while (true) {
            showMenu();
            int choice = readInt("Choose: ");
            if (choice == 0) break;

            switch (choice) {
            case 1:
                playGame(scoreBoard);
                break;
            case 2:
                scoreBoard.print();
                break;
            case 3: {
                std::string name = readLine("Name: ");
                std::cout << (scoreBoard.addPlayer(name) ? "Player added.\n"
                                                         : "That name is empty or already taken.\n");
                break;
            }
            case 4: {
                std::string name = readLine("Name: ");
                const PlayerRecord* r = scoreBoard.findPlayer(name);
                if (r)
                    std::cout << r->getName() << ": " << r->getWins() << " wins, "
                              << r->getLosses() << " losses, " << r->getDraws() << " draws\n";
                else
                    std::cout << "Player not found.\n";
                break;
            }
            case 5: {
                std::string oldName = readLine("Current name: ");
                std::string newName = readLine("New name: ");
                std::cout << (scoreBoard.renamePlayer(oldName, newName)
                                  ? "Player renamed.\n"
                                  : "Could not rename (not found, or new name taken).\n");
                break;
            }
            case 6: {
                std::string name = readLine("Name: ");
                std::cout << (scoreBoard.removePlayer(name) ? "Player removed.\n"
                                                             : "Player not found.\n");
                break;
            }
            default:
                std::cout << "Unknown option.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cout << "\nProgram aborted: " << e.what() << "\n";
    }
    return 0;
}
