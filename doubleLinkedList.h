/*
/* Program name: doubleLinkedList.h
* Author: Charlie Shaneck
* Date last updated: 5/10/2025
* Purpose: Define a double linked list class
*/ 

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "linkedList.h"

// creates a double linked list that extends off linked list
template <class type>
class doubleLinkedList : public linkedList<type>{
public:
    doubleLinkedList() : linkedList<type>() {};

    void insert(const type &newItem) override;
    void deleteItem(const type &deleteItem) override;
};

// inserts an item into the double directional list
template <class type>
void doubleLinkedList<type>::insert(const type &newItem)
{
    // creates a new node
    node<type>* newNode = new node<type>;
    newNode->data = new type(newItem);
    newNode->right = nullptr;
    newNode->left = nullptr;

    // first item insert
    if (this->isEmpty()){
        this->first = newNode;
        this->last = newNode;

        ++this->count;
    }

    // last item insert
    else{
        this->last->right = newNode;
        newNode->left = this->last;
        this->last = newNode;
        ++this->count;
    }
}

template <class type>
void doubleLinkedList<type>::deleteItem(const type &deleteItem)
{
    node<type>* curr = this->first;
    node<type>* tempTail = this->first;
    bool found = false;

    if (this->isEmpty()){
        throw(std::out_of_range("Cannot delete from empty list"));
    }

	if (deleteItem == *(this->first->data)){ //first item deletion
        found = true;

        // single item in list
        if (this->first->right == nullptr){
            this->first = this->first->right;
            delete curr;
            this->last = nullptr;
            --this->count;
        }

        else{
            // go over to the next item, set the left pointer to the nullptr
            this->first->right->left = nullptr;
            // shift the first item to be the previous second item
            this->first = this->first->right;
            // delete the node that needs to be deleted and decrease the count
            delete curr;
            --this->count;
        }
	}

	else {
		while (curr != nullptr){
			
			if (*(curr->data) == *(this->last->data)){ //last item deletion
                found = true;

				this->last = tempTail;
				this->last->right = nullptr;

				delete curr;
				--this->count; 
				break;
			}

			if (deleteItem == *(curr->data)) { //mid list delete
                found = true;

                // set the nodes to point around the current node scheduled for removal
				tempTail->right = curr->right;
                curr->right->left = tempTail;

				delete curr;
				--this->count;
				break;
			}

			tempTail = curr;
			curr = curr->right;
		}

        if (!found) throw(std::out_of_range("Item not in list"));
	}
}

#endif