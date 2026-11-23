#include "PlayerRecord.h"

PlayerRecord::PlayerRecord() : name_("Unknown"), wins_(0), losses_(0), draws_(0) {}

PlayerRecord::PlayerRecord(const std::string& name)
    : name_(name), wins_(0), losses_(0), draws_(0) {}

const std::string& PlayerRecord::getName() const { return name_; }
int PlayerRecord::getWins() const { return wins_; }
int PlayerRecord::getLosses() const { return losses_; }
int PlayerRecord::getDraws() const { return draws_; }
int PlayerRecord::getGamesPlayed() const { return wins_ + losses_ + draws_; }

void PlayerRecord::setName(const std::string& name) { name_ = name; }
void PlayerRecord::addWin() { ++wins_; }
void PlayerRecord::addLoss() { ++losses_; }
void PlayerRecord::addDraw() { ++draws_; }
