#ifndef MOVE_H
#define MOVE_H

#include <ostream>
#include <string>

// One move made during a game: who played, and where.
class Move {
public:
    Move();                                           // default constructor
    Move(int row, int col, char symbol);              // parametric constructor (0-based row/col)

    int getRow() const;
    int getCol() const;
    char getSymbol() const;

    std::string describe() const;                     // e.g. "X -> row 2, col 3"

private:
    int row_;
    int col_;
    char symbol_;
};

std::ostream& operator<<(std::ostream& os, const Move& move);

#endif
