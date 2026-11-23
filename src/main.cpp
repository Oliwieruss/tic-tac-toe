#include <iostream>
#include "Board.h"

// Temporary test driver - will be replaced by Game class later.
int main() {
    Board board;
    board.placeMark(0, 0, 'X');
    board.placeMark(1, 1, 'X');
    board.placeMark(2, 2, 'X');

    std::cout << "Winner: " << board.checkWinner() << "\n";
    std::cout << "Full? " << std::boolalpha << board.isFull() << "\n";
    return 0;
}
