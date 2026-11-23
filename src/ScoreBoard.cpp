#include "ScoreBoard.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "Exceptions.h"

// Uses PlayerRecord::operator== (records are equal when the names are equal).
PlayerRecord* ScoreBoard::findPlayer(const std::string& name) {
    auto it = std::find(records_.begin(), records_.end(), PlayerRecord(name));
    return it == records_.end() ? nullptr : &*it;
}

const PlayerRecord* ScoreBoard::findPlayer(const std::string& name) const {
    auto it = std::find(records_.begin(), records_.end(), PlayerRecord(name));
    return it == records_.end() ? nullptr : &*it;
}

void ScoreBoard::addPlayer(const std::string& name) {
    if (name.empty())
        throw ScoreBoardException("The name cannot be empty.");
    if (findPlayer(name) != nullptr)
        throw ScoreBoardException("Player \"" + name + "\" already exists.");
    records_.push_back(PlayerRecord(name));
}

void ScoreBoard::renamePlayer(const std::string& oldName, const std::string& newName) {
    PlayerRecord* record = findPlayer(oldName);
    if (record == nullptr)
        throw ScoreBoardException("Player \"" + oldName + "\" not found.");
    if (newName.empty())
        throw ScoreBoardException("The new name cannot be empty.");
    if (findPlayer(newName) != nullptr)
        throw ScoreBoardException("Player \"" + newName + "\" already exists.");
    record->setName(newName);
}

void ScoreBoard::removePlayer(const std::string& name) {
    for (auto it = records_.begin(); it != records_.end(); ++it) {
        if (it->getName() == name) {
            records_.erase(it);
            return;
        }
    }
    throw ScoreBoardException("Player \"" + name + "\" not found.");
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
    // Sort a copy with PlayerRecord::operator< (best player first).
    std::vector<PlayerRecord> ranking = records_;
    std::sort(ranking.begin(), ranking.end(),
              [](const PlayerRecord& a, const PlayerRecord& b) { return b < a; });

    std::cout << "\n" << std::left << std::setw(16) << "Player"
              << std::right << std::setw(6) << "Wins" << std::setw(8) << "Losses"
              << std::setw(7) << "Draws" << std::setw(8) << "Games" << "\n";
    std::cout << std::string(45, '-') << "\n";
    for (const auto& r : ranking) {
        std::cout << std::left << std::setw(16) << r.getName()
                  << std::right << std::setw(6) << r.getWins() << std::setw(8) << r.getLosses()
                  << std::setw(7) << r.getDraws() << std::setw(8) << r.getGamesPlayed() << "\n";
    }
    std::cout << "\n";
}
