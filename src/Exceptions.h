#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Base class for all errors caused by the rules of the game or by bad user data.
class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
};

// A move outside the board, or text instead of numbers.
class InvalidMoveException : public GameException {
public:
    explicit InvalidMoveException(const std::string& message) : GameException(message) {}
};

// A move onto a cell that is already taken (a special kind of invalid move).
class CellOccupiedException : public InvalidMoveException {
public:
    explicit CellOccupiedException(const std::string& message) : InvalidMoveException(message) {}
};

// Adding a duplicate player, renaming or removing a player that does not exist, etc.
class ScoreBoardException : public GameException {
public:
    explicit ScoreBoardException(const std::string& message) : GameException(message) {}
};

// Standard input was closed (Ctrl+Z / Ctrl+D). Not a GameException: the program cannot continue.
class InputClosedException : public std::runtime_error {
public:
    InputClosedException() : std::runtime_error("Input stream closed.") {}
};

#endif
