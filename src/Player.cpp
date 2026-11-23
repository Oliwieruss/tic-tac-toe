#include "Player.h"

Player::Player() : name_("Player"), symbol_('X') {}

Player::Player(const std::string& name, char symbol)
    : name_(name), symbol_(symbol) {}

std::string Player::describe() const {
    return name_ + " (" + symbol_ + ")";
}

const std::string& Player::getName() const { return name_; }
char Player::getSymbol() const { return symbol_; }
void Player::setName(const std::string& name) { name_ = name; }
void Player::setSymbol(char symbol) { symbol_ = symbol; }
