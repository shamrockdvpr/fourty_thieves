#ifndef MOVE_H
#define MOVE_H
#include "stack.h"
#include "card.h"

class move{
public:
    move(stack<card> &source, stack<card> &destination, card &movedCard, int currentScore) 
        : source(&source), destination(&destination), movedCard(&movedCard), score(currentScore){

        // assign variables and increment score
        if (destination.getType() == stack<card>::FOUNDATION){
            score += 5;
        }

        if (destination.isFull()){
            score += 60;
        }
    };

    bool operator<(const move&otherMove) const {return this->score < otherMove.score;};
    bool operator>(const move&otherMove) const {return this->score > otherMove.score;};
    bool operator==(const move&otherMove) const {return this->score == otherMove.score;};
    bool operator!=(const move&otherMove) const {return !(*this == otherMove);};

    const int getScore() const {return score;};

private:
    const stack<card>* source;
    const stack<card>* destination;
    const card* movedCard;
    int score;
};



#endif // MACRO
