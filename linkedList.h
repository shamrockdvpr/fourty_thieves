#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

template <class type>
class linkedList{
protected:
    node<type>* first;
    node<type>* last;
    int count;
private:
    void copyList(const linkedList<type> &otherList);
public:
    linkedList();
    linkedList(const linkedList<type> &otherList);
    ~linkedList();

    void initializeList();
    bool isEmpty() const;
    int length() const;
    type front() const;
    type back() const;

    virtual bool search(const type &searchItem) const;
    virtual void insert(const type &newItem);
    virtual void deleteItem(const type &deleteItem);

    class Iterator{
    public:
        Iterator(node<type>* currentNode);
        type &operator*();
        Iterator operator++();
        bool operator==(const Iterator &otherIt) const;
        bool operator!=(const Iterator &otherIt) const;
    private:
        node<type>* current;
    };

    Iterator begin();
    Iterator end();
};

// Operations Defined:

// *** Simple Operations *** //

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

// ** Complex Operations ** //

// copys the conents of a different list into the current list
template <class type>
void linkedList<type>::copyList(const linkedList<type> &otherList)
{
    node<type> *newNode;
    node<type> *current;
    if (first != nullptr) initializeList();
    if (otherList.first == nullptr){
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else{
        current = otherList.first;
        count = otherList.count;

        first = new node<type>();
        first->data = current->data;

        last = first;

        current = current->right;
        while (current != nullptr)
        {
            newNode = new node<type>();
            newNode->data = current->data;
            newNode->right = nullptr;
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
    node<type>* temp;
    while (first != nullptr){
        temp = first;
        first = first->right;
        delete temp;
    }
    last = nullptr;
    count = 0;
}

// ** Main Operations ** //

// finds if an item is in the list, returns an bool if obj is present in list
template <class type>
bool linkedList<type>::search(const type &searchItem) const{

    if (isEmpty()) return false;

    node<type>* current;
    current = first;

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
    node<type>* newNode = new node<type>;
    newNode->data = new type(newItem);
    newNode->right = nullptr;

    if (isEmpty()){
        first = newNode;
        last = newNode;
        ++count;
    }

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
    node<type>* curr = first;
    node<type>* tempTail = first;
    bool found = false;

    if (isEmpty()){
        throw(std::out_of_range("Cannot delete from empty list"));
    }

	if (deleteItem == *(first->data)){ //first item deletion
        found = true;
		first = first->right;
		delete curr;
		--count;
	}

	else {
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

// ** Constructors/Destructors ** //

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

// returns an Iterator to the first node
template <class type>
typename linkedList<type>::Iterator linkedList<type>::begin()
{
    Iterator it(first);
    return it;
}

// returns an Iterator to the last node
template <class type>
typename linkedList<type>::Iterator linkedList<type>::end()
{
    Iterator it(last);
    return it;
}

template <class type>
linkedList<type>::Iterator::Iterator(node<type> *currentNode) : current(currentNode)
{}

template <class type>
type &linkedList<type>::Iterator::operator*()
{
    return *(current->data);
}

template <class type>
typename linkedList<type>::Iterator linkedList<type>::Iterator::operator++(){
    current = current->right;
    return *this;
}

template <class type>
bool linkedList<type>::Iterator::operator==(const Iterator &otherIt) const
{
    return *(current->data) == *(otherIt.current->data);
}

template <class type>
bool linkedList<type>::Iterator::operator!=(const Iterator &otherIt) const
{
    return !(*(current->data) == *(otherIt.current->data));
}

#endif
