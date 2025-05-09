#ifndef GAMESPACE_H
#define GAMESPACE_H
#include <algorithm>
#include "stack.h"
#include "card.h"
#include "move.h"
#include "doubleLinkedList.h"

class gamespace{
public:
    gamespace();
    bool isValid(stack<card>&, stack<card>&);
    void moveCards(std::string, std::string);
    void undo();

    void resetScore() {score = 0;};
    void updateScore(int scoreInc) {score += scoreInc;};

    bool gameFinished();

    friend std::ostream &operator<<(std::ostream& out, const gamespace game);

private:
    int score;
    stack<card> foundations[8];
    stack<card> tableaus[10];
    stack<card> waste;
    stack<card> stock;
    doubleLinkedList<move> gameHistory;
    Iterator<move> currentMove;

    void shuffle(stack<card>*);
};

#endif