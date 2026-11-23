#ifndef PLAYERRECORD_H
#define PLAYERRECORD_H

#include <string>

// Score of one player: wins, losses and draws.
class PlayerRecord {
public:
    PlayerRecord();                                   // default constructor
    explicit PlayerRecord(const std::string& name);   // parametric constructor

    const std::string& getName() const;
    int getWins() const;
    int getLosses() const;
    int getDraws() const;
    int getGamesPlayed() const;

    void setName(const std::string& name);
    void addWin();
    void addLoss();
    void addDraw();

private:
    std::string name_;
    int wins_;
    int losses_;
    int draws_;
};

#endif
