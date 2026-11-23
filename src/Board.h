#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>

class Board {
public:
    static const int SIZE = 3;

    Board();                                  // default constructor: empty board

    // Modifiers
    void placeMark(int row, int col, char symbol);   // throws InvalidMoveException / CellOccupiedException
    bool clearCell(int row, int col);                // empties a cell (used by undo)
    void reset();

    // Accessors (const: they do not change the board)
    char getCell(int row, int col) const;
    bool isFull() const;
    bool isCellFree(int row, int col) const;
    char checkWinner() const;                 // 'X', 'O' or ' ' (no winner yet)

private:
    std::array<std::array<char, SIZE>, SIZE> cells_;
    bool inRange(int row, int col) const;
};

// Draws the board: std::cout << board;
std::ostream& operator<<(std::ostream& os, const Board& board);

#endif
