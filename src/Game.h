#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Board.h"
#include "Player.h"

class Game {
public:
    Game(std::unique_ptr<Player> first, std::unique_ptr<Player> second);

    void run();                               // plays one full game

private:
    Board board_;
    std::unique_ptr<Player> players_[2];      // polymorphic: Human or Computer
};

#endif
