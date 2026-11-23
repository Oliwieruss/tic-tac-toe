#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Board.h"
#include "MoveHistory.h"
#include "Player.h"

class Game {
public:
    Game(std::unique_ptr<Player> first, std::unique_ptr<Player> second);

    // Plays one full game. Returns the winner, or nullptr for a draw.
    const Player* run();

    const Player& getPlayer(int index) const;         // index 0 or 1
    const MoveHistory& getHistory() const;

private:
    Board board_;
    MoveHistory history_;
    std::unique_ptr<Player> players_[2];              // polymorphic: Human or Computer

    void undo(int& turn);                             // takes back moves until a human is to move
};

#endif
