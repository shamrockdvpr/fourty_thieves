/*
/* Program name: linkedList.h
* Author: Charlie Shaneck
* Date last updated: 5/10/2025
* Purpose: Defines a linked list class for use as a base class
*/ 

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>

// Defines a node structure for use in linked lists
template <class type>
struct node{
    type *data;
    // use as linked list -> link, named as such to make it easier to handle binary trees
    node<type> *right;
    node<type> *left;
    ~node() {delete data;};
    bool operator==(const node<type> &otherNode) const {return (*(data) == *(otherNode.data));}
    bool operator!=(const node<type> &otherNode) const {return (*(data) != *(otherNode.data));}
};

// Defines an iterator class for traversal
template <class type>
class Iterator{
public:
    //constructor
    Iterator(node<type> *currentNode);

    bool hasNext() const;

    // operator overloads
    type& operator*();
    Iterator<type> &operator++();
    Iterator<type> &operator--();
    bool operator==(const Iterator<type> &otherIt) const;
    bool operator!=(const Iterator<type> &otherIt) const;

protected:
    node<type> *current;
};

// linked list base class
template <class type>
class linkedList{
protected:
    node<type> *first;
    node<type> *last;
    int count;

private:
    void copyList(const linkedList<type> &otherList);

public:
    // constructors and destructors

    linkedList();
    linkedList(const linkedList<type> &otherList);
    ~linkedList();

    // minor operations

    virtual void initializeList();
    virtual bool isEmpty() const;
    int length() const;
    type front() const;
    type back() const;

    // major operations

    virtual bool search(const type &searchItem) const;
    virtual void insert(const type &newItem);
    virtual void deleteItem(const type &deleteItem);

    // iterator operations
    Iterator<type> begin();
    Iterator<type> end();
};

// Operations Defined:

/************ Minor Operations *****************/

// returns true if the list is empty
template <class type>
bool linkedList<type>::isEmpty() const
{
    return (first == nullptr);
}

// returns length of list
template <class type>
int linkedList<type>::length() const
{
    return count;
}

// returns the data stored at the first node
template <class type>
type linkedList<type>::front() const
{
    if (front != nullptr) return *(first->data);
}

// returns the data stored at the last node
template <class type>
type linkedList<type>::back() const
{
    if (last != nullptr) return *(last->data);
}


/*************************** Complex Operations ***************************/

// copys the conents of a different list into the current list
template <class type>
void linkedList<type>::copyList(const linkedList<type> &otherList)
{
    // creates a new node and a pointer to the current node
    node<type> *newNode;
    node<type> *current;

    // if the current list isn't empty, clear all data
    if (first != nullptr) initializeList();

    // if the other list is empty, set the new list to be empty
    if (otherList.first == nullptr){
        first = nullptr;
        last = nullptr;
        count = 0;
    }

    else{
        // start current at the beginning of the other list
        current = otherList.first;
        count = otherList.count;

        // create a first node and init the list
        first = new node<type>();
        first->data = current->data;
        last = first;

        // begin iteration
        current = current->right;
        while (current != nullptr)
        {
            // create new nodes
            newNode = new node<type>();
            newNode->data = current->data;
            newNode->right = nullptr;

            // insert into list and advance current
            last->right = newNode;
            last = newNode;
            current = current->right;
        }
        
    }
}

// deletes contents of list in a memory safe manner
template <class type>
void linkedList<type>::initializeList()
{
    // create a temporary pointer
    node<type>* temp;

    // advance first foward over the list until the end, delete the data previously stored at first
    while (first != nullptr){
        temp = first;
        first = first->right;
        delete temp;
    }

    // clean up
    last = nullptr;
    count = 0;
}


/************ Main Operations ************/

// finds if an item is in the list, returns an bool if obj is present in list
template <class type>
bool linkedList<type>::search(const type &searchItem) const{

    // if the list is empty, the object will not exist
    if (isEmpty()) return false;

    // iterate over the list
    node<type>* current;
    current = first;

    // while not at the end of the list
    while (current != nullptr){
        if (searchItem == *(current->data)) {
            return true;
        }
        else {
            current = current->right;
        }
    }

    return false;
}

// inserts into last position
template <class type>
void linkedList<type>::insert(const type &newItem)
{
    // creates new node
    node<type> *newNode = new node<type>();
    newNode->data = new type(newItem);

    // insert first if list is empty
    if (isEmpty()){
        first = newNode;
        last = newNode;
        ++count;
    }

    // otherwise insert last
    else{
        last->right = newNode;
        last = newNode;
        ++count;
    }
}

// deletes item from list
template <class type>
void linkedList<type>::deleteItem(const type &deleteItem)
{
    // create two nodes, one will point to the object being deleted, one will point to the one before it
    node<type> *curr = first;
    node<type> *tempTail = first;
    bool found = false;

    // if list is empty
    if (isEmpty()){
        throw(std::out_of_range("Cannot delete from empty list"));
    }

	if (deleteItem == *(first->data)){ //first item deletion
        found = true;
		first = first->right;
		delete curr;
        last = nullptr;
		--count;
	}

	else {
        // while not at item end
		while (curr != nullptr){
			
			if (*(curr->data) == *(last->data)){ //last item deletion
                found = true;
				last = tempTail;
				last->right = nullptr;
				delete curr;
				--count; 
				break;
			}

			if (deleteItem == *(curr->data)) { //mid list delete
                found = true;
				tempTail->right = curr->right;
				delete curr;
				--count;
				break;
			}

			tempTail = curr;
			curr = curr->right;
		}

        if (!found) throw(std::out_of_range("Item not in list"));
	}
}


/***********Constructors/Destructors************/

// destructor
template <class type>
linkedList<type>::~linkedList()
{
    initializeList();
}

// default constructor
template <class type>
linkedList<type>::linkedList(){
    first = nullptr;
    last = nullptr;
    count = 0;
}

// copy constructor
template <class type>
linkedList<type>::linkedList(const linkedList<type> &otherList)
{
    first = nullptr;
    copyList(otherList);
}


/***********Iterator Operators Specific to Linked list Access************/

// returns an Iterator to the first node
template <class type>
Iterator<type> linkedList<type>::begin()
{
    return Iterator<type>(first);
}

// returns an Iterator to the last node
template <class type>
Iterator<type> linkedList<type>::end()
{
    return Iterator<type>(last);
}


/****** Iterator Methods ******/

// default constructor
template <class type>
Iterator<type>::Iterator(node<type> *currentNode) : current(currentNode)
{}

// returns true if the next item isnt the nullptr
template <class type>
bool Iterator<type>::hasNext() const
{
    return (current->right != nullptr) ? true : false;
}

// returns data stored at the iterator position
template <class type>
type& Iterator<type>::operator*()
{
    return *(current->data);
}

// advances the iterator one forward
template <class type>
Iterator<type>& Iterator<type>::operator++()
{
    current = current->right;
    return *this;
}

// moves the iterator back one
template <class type>
Iterator<type> &Iterator<type>::operator--()
{
    current = current->left;
    return *this;
}

// returns true if the data stored at the iterator equals a different iterator
template <class type>
bool Iterator<type>::operator==(const Iterator<type> &otherIt) const
{
    return *(current->data) == *(otherIt.current->data);
}

// returns true if the data stored at the iterator does not equals a different iterator
template <class type>
bool Iterator<type>::operator!=(const Iterator<type> &otherIt) const
{
    return !(*(current->data) == *(otherIt.current->data));
}

#endif
