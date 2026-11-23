#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <utility>
#include "Board.h"

// Abstract base class. Derived classes decide HOW a move is chosen.
class Player {
public:
    Player();                                         // default constructor
    Player(const std::string& name, char symbol);     // parametric constructor
    virtual ~Player() = default;                      // virtual destructor (needed for polymorphism)

    // Pure virtual: every derived class must implement it.
    // Returns {row, col} (0-based).
    virtual std::pair<int, int> chooseMove(const Board& board) const = 0;

    // Virtual with a default implementation, can be overridden.
    virtual std::string describe() const;

    // True for players that type their moves (and may ask for undo). Default: false.
    virtual bool isInteractive() const;

    // Special value returned by chooseMove when the player asks to undo.
    static constexpr int UNDO_MOVE = -2;

    // Accessors and mutators (encapsulation)
    const std::string& getName() const;
    char getSymbol() const;
    void setName(const std::string& name);
    void setSymbol(char symbol);

private:
    std::string name_;
    char symbol_;
};

#endif
