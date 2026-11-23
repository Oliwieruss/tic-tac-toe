#include "Move.h"

Move::Move() : row_(0), col_(0), symbol_(' ') {}

Move::Move(int row, int col, char symbol)
    : row_(row), col_(col), symbol_(symbol) {}

int Move::getRow() const { return row_; }
int Move::getCol() const { return col_; }
char Move::getSymbol() const { return symbol_; }

std::string Move::describe() const {
    return std::string(1, symbol_) + " -> row " + std::to_string(row_ + 1) +
           ", col " + std::to_string(col_ + 1);
}
