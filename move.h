/*
/* Program name: move.h
* Author: Charlie Shaneck
* Date last updated: 5/10/2025
* Purpose: Defines a move in the game
*/ 

#ifndef MOVE_H
#define MOVE_H
#include "stack.h"
#include "card.h"

class move{
public:
    move(stack<card> &source, stack<card> &destination, int currentScore) 
        : 
        source(&source), 
        destination(&destination), 
        score(currentScore)
    {};

    ~move() {source = nullptr; destination = nullptr;};

    bool operator<(const move&otherMove) const {return this->score < otherMove.score;};
    bool operator>(const move&otherMove) const {return this->score > otherMove.score;};
    bool operator==(const move&otherMove) const {return this->score == otherMove.score;};
    bool operator!=(const move&otherMove) const {return !(*this == otherMove);};

    const int getScore() const {return score;};
    stack<card>* getSource() {return source;};
    stack<card>* getDestination() {return destination;};

private:
    stack<card>* source;
    stack<card>* destination;
    int score;
};




#endif // MACRO
