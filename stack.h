#ifndef STACK_H
#define STACK_H

#include "linkedList.h"

template <class type>
class stack : public linkedList<type>{
public:
    // constructor
    stack();
    stack(int max);

    // basic operations
    const bool isFull() const {return this->count >= maxSize;};
    bool isEmpty() const {return (stackTop == nullptr);};

    // main operations
    void push(const type&);
    type pop();
    type peek() const;

private:
    node<type>* stackTop;
    const int maxSize;
};

template <class type>
stack<type>::stack(int max) : maxSize(max){ 
    stackTop = nullptr;
    this->count = 0;
}

template <class type>
stack<type>::stack() : maxSize(10000){ 
    stackTop = nullptr;
    this->count = 0;
}

// the insert function already does all the operations in the way it should
template <class type>
void stack<type>::push(const type &newItem)
{
    if (isFull()){
        throw std::overflow_error("Stack Overflow");
    }
    node<type>* newNode = new node<type>;
    newNode->data = new type(newItem);
    newNode->right = stackTop;

    stackTop = newNode;
    this->count++;
}

template <class type>
type stack<type>::peek() const
{
    if (isEmpty()){
        throw std::out_of_range("Empty Stack");
    }
    return *(stackTop->data);
}

template <class type>
type stack<type>::pop()
{  
    node<type> *temp;

    if (isEmpty()){
        throw std::underflow_error("Stack Underflow");
    }

    temp = stackTop;
    stackTop = stackTop->right;

    // clean up: return data stored, decrease count, free memory
    type returnItem = *(temp->data);
    delete temp;
    this->count--;
    return returnItem;
}

#endif
