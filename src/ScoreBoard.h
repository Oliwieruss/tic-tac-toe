#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <vector>
#include "PlayerRecord.h"

// A list of players with their results. Supports add, find, rename, remove and show.
// Errors (duplicate name, unknown player) are reported with ScoreBoardException.
class ScoreBoard {
public:
    ScoreBoard() = default;

    void addPlayer(const std::string& name);                           // ADD
    PlayerRecord* findPlayer(const std::string& name);                 // SEARCH (nullptr if missing)
    const PlayerRecord* findPlayer(const std::string& name) const;
    void renamePlayer(const std::string& oldName, const std::string& newName);  // MODIFY
    void removePlayer(const std::string& name);                        // REMOVE

    // Records a finished game; unknown players are added automatically.
    void recordWin(const std::string& winner, const std::string& loser);
    void recordDraw(const std::string& first, const std::string& second);

    bool isEmpty() const;
    void print() const;                                                // ranking, best first

private:
    std::vector<PlayerRecord> records_;
    PlayerRecord& getOrCreate(const std::string& name);
};

#endif
