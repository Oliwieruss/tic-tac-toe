#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <vector>
#include "PlayerRecord.h"

// A list of players with their results. Supports add, find, rename, remove and show.
class ScoreBoard {
public:
    ScoreBoard() = default;

    bool addPlayer(const std::string& name);                           // ADD (false if name taken)
    PlayerRecord* findPlayer(const std::string& name);                 // SEARCH (nullptr if missing)
    const PlayerRecord* findPlayer(const std::string& name) const;
    bool renamePlayer(const std::string& oldName, const std::string& newName);  // MODIFY
    bool removePlayer(const std::string& name);                        // REMOVE

    // Records a finished game; unknown players are added automatically.
    void recordWin(const std::string& winner, const std::string& loser);
    void recordDraw(const std::string& first, const std::string& second);

    bool isEmpty() const;
    void print() const;

private:
    std::vector<PlayerRecord> records_;
    PlayerRecord& getOrCreate(const std::string& name);
};

#endif
