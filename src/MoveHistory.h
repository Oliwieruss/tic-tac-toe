#ifndef MOVEHISTORY_H
#define MOVEHISTORY_H

#include <vector>
#include "Move.h"

// Stores the moves of one game. Supports add, undo (remove last), search by turn and listing.
class MoveHistory {
public:
    MoveHistory() = default;

    void add(const Move& move);                       // ADD a move
    bool removeLast();                                // REMOVE the last move (undo); false if empty
    const Move* findByTurn(int turn) const;           // SEARCH: turn is 1-based, nullptr if not found
    const Move& last() const;                         // last move (check isEmpty() first)
    bool isEmpty() const;
    std::size_t size() const;
    void clear();
    void print() const;                               // lists all moves

private:
    std::vector<Move> moves_;
};

#endif
