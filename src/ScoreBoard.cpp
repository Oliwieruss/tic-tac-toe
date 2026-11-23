#include "ScoreBoard.h"
#include <iomanip>
#include <iostream>

PlayerRecord* ScoreBoard::findPlayer(const std::string& name) {
    for (auto& r : records_)
        if (r.getName() == name) return &r;
    return nullptr;
}

const PlayerRecord* ScoreBoard::findPlayer(const std::string& name) const {
    for (const auto& r : records_)
        if (r.getName() == name) return &r;
    return nullptr;
}

bool ScoreBoard::addPlayer(const std::string& name) {
    if (name.empty() || findPlayer(name) != nullptr)
        return false;
    records_.push_back(PlayerRecord(name));
    return true;
}

bool ScoreBoard::renamePlayer(const std::string& oldName, const std::string& newName) {
    PlayerRecord* record = findPlayer(oldName);
    if (record == nullptr || newName.empty() || findPlayer(newName) != nullptr)
        return false;
    record->setName(newName);
    return true;
}

bool ScoreBoard::removePlayer(const std::string& name) {
    for (auto it = records_.begin(); it != records_.end(); ++it) {
        if (it->getName() == name) {
            records_.erase(it);
            return true;
        }
    }
    return false;
}

PlayerRecord& ScoreBoard::getOrCreate(const std::string& name) {
    PlayerRecord* record = findPlayer(name);
    if (record == nullptr) {
        records_.push_back(PlayerRecord(name));
        record = &records_.back();
    }
    return *record;
}

void ScoreBoard::recordWin(const std::string& winner, const std::string& loser) {
    getOrCreate(winner).addWin();
    getOrCreate(loser).addLoss();
}

void ScoreBoard::recordDraw(const std::string& first, const std::string& second) {
    getOrCreate(first).addDraw();
    getOrCreate(second).addDraw();
}

bool ScoreBoard::isEmpty() const { return records_.empty(); }

void ScoreBoard::print() const {
    if (records_.empty()) {
        std::cout << "The scoreboard is empty.\n";
        return;
    }
    std::cout << "\n" << std::left << std::setw(16) << "Player"
              << std::right << std::setw(6) << "Wins" << std::setw(8) << "Losses"
              << std::setw(7) << "Draws" << std::setw(8) << "Games" << "\n";
    std::cout << std::string(45, '-') << "\n";
    for (const auto& r : records_) {
        std::cout << std::left << std::setw(16) << r.getName()
                  << std::right << std::setw(6) << r.getWins() << std::setw(8) << r.getLosses()
                  << std::setw(7) << r.getDraws() << std::setw(8) << r.getGamesPlayed() << "\n";
    }
    std::cout << "\n";
}
