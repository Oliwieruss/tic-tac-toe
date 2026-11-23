#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>

class Board {
public:
    static const int SIZE = 3;

    Board();                                  // default constructor: empty board

    // Modifiers
    bool placeMark(int row, int col, char symbol);   // false if cell is taken / out of range
    void reset();

    // Accessors (const: they do not change the board)
    char getCell(int row, int col) const;
    bool isFull() const;
    bool isCellFree(int row, int col) const;
    char checkWinner() const;                 // 'X', 'O' or ' ' (no winner yet)
    void print() const;                       // draws the board in the console

private:
    std::array<std::array<char, SIZE>, SIZE> cells_;
    bool inRange(int row, int col) const;
};

#endif
