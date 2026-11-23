#include "ComputerPlayer.h"
#include <cstdlib>
#include <vector>

ComputerPlayer::ComputerPlayer(const std::string& name, char symbol)
    : Player(name, symbol) {}

// Picks a random free cell.
std::pair<int, int> ComputerPlayer::chooseMove(const Board& board) const {
    std::vector<std::pair<int, int>> freeCells;
    for (int r = 0; r < Board::SIZE; ++r)
        for (int c = 0; c < Board::SIZE; ++c)
            if (board.isCellFree(r, c))
                freeCells.push_back({r, c});

    if (freeCells.empty())
        return {-1, -1};
    return freeCells[std::rand() % freeCells.size()];
}

std::string ComputerPlayer::describe() const {
    return "Computer: " + Player::describe();
}
