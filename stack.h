#ifndef STACK_H
#define STACK_H

#include "linkedList.h"

template <class type>
class stack : public linkedList<type>{
private:
    // this contains the type of deck that this stack is, used for move checking and scoring
    stackType deckType;

public:
    enum stackType{
        FOUNDATION,
        TABLEAU,
        STOCK,
        WASTE,
    };

    // get the deck's type
    const stackType getType() const;

    const bool isFull() const;
};

template <class type>
const stack<type>::stackType stack<type>::getType() const
{
    return deckType;
}

template <class type>
const bool stack<type>::isFull() const
{
    // return true if the stack is a sequence from ace to king
}

#endif
