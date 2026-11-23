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

bool operator==(const PlayerRecord& a, const PlayerRecord& b) {
    return a.getName() == b.getName();
}

bool operator<(const PlayerRecord& a, const PlayerRecord& b) {
    if (a.getWins() != b.getWins())
        return a.getWins() < b.getWins();
    if (a.getLosses() != b.getLosses())
        return a.getLosses() > b.getLosses();
    return a.getName() > b.getName();             // alphabetical order when everything else is equal
}

std::ostream& operator<<(std::ostream& os, const PlayerRecord& record) {
    return os << record.getName() << ": " << record.getWins() << " wins, "
              << record.getLosses() << " losses, " << record.getDraws() << " draws";
}
