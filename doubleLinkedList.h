#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "linkedList.h"

template <class type>
class doubleLinkedList : public linkedList<type>{
public:
    doubleLinkedList() : linkedList<type>() {};
    void insert(const type &newItem) override;
    void deleteItem(const type &deleteItem) override;
};

template <class type>
void doubleLinkedList<type>::insert(const type &newItem)
{
    node<type>* newNode = new node<type>;
    newNode->data = new type(newItem);
    newNode->right = nullptr;
    newNode->left = nullptr;

    if (this->isEmpty()){
        this->first = newNode;
        this->last = newNode;
        this->first->left = this->last;

        ++this->count;
    }

    else{
        this->last->right = newNode;
        newNode->left = this->last;
        this->last = newNode;
        ++this->count;
    }
}

#endif
