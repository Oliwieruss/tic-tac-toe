#include "Board.h"
#include "Exceptions.h"

Board::Board() {
    reset();
}

void Board::reset() {
    for (auto& row : cells_)
        row.fill(' ');
}

bool Board::inRange(int row, int col) const {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

bool Board::isCellFree(int row, int col) const {
    return inRange(row, col) && cells_[row][col] == ' ';
}

void Board::placeMark(int row, int col, char symbol) {
    if (!inRange(row, col))
        throw InvalidMoveException("Row and column must be between 1 and " + std::to_string(SIZE) + ".");
    if (cells_[row][col] != ' ')
        throw CellOccupiedException("That cell is already taken.");
    cells_[row][col] = symbol;
}

bool Board::clearCell(int row, int col) {
    if (!inRange(row, col) || cells_[row][col] == ' ')
        return false;
    cells_[row][col] = ' ';
    return true;
}

char Board::getCell(int row, int col) const {
    return inRange(row, col) ? cells_[row][col] : ' ';
}

bool Board::isFull() const {
    for (const auto& row : cells_)
        for (char c : row)
            if (c == ' ') return false;
    return true;
}

char Board::checkWinner() const {
    // rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if (cells_[i][0] != ' ' && cells_[i][0] == cells_[i][1] && cells_[i][1] == cells_[i][2])
            return cells_[i][0];
        if (cells_[0][i] != ' ' && cells_[0][i] == cells_[1][i] && cells_[1][i] == cells_[2][i])
            return cells_[0][i];
    }
    // diagonals
    if (cells_[1][1] != ' ') {
        if (cells_[0][0] == cells_[1][1] && cells_[1][1] == cells_[2][2]) return cells_[1][1];
        if (cells_[0][2] == cells_[1][1] && cells_[1][1] == cells_[2][0]) return cells_[1][1];
    }
    return ' ';
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << "\n    1   2   3\n";
    for (int r = 0; r < Board::SIZE; ++r) {
        os << "  " << (r + 1) << " ";
        for (int c = 0; c < Board::SIZE; ++c) {
            os << board.getCell(r, c);
            if (c < Board::SIZE - 1) os << " | ";
        }
        os << "\n";
        if (r < Board::SIZE - 1) os << "    --+---+--\n";
    }
    os << "\n";
    return os;
}
