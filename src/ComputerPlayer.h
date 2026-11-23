#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer(const std::string& name, char symbol);

    std::pair<int, int> chooseMove(const Board& board) const override;
    std::string describe() const override;
};

#endif
