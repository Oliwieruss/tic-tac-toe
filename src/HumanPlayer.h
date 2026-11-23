#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& name, char symbol);

    std::pair<int, int> chooseMove(const Board& board) const override;
    std::string describe() const override;
    bool isInteractive() const override;
};

#endif
