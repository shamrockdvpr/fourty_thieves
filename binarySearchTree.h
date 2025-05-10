#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"

template <class type>
class binarySearchTree : public binaryTree<type>{
public:
    bool search(const type &searchItem) const override;
    void insert(const type &insertItem) override;
    void deleteNode(const type &deleteItem) override;

private:
    bool searchFromNode(const type &searchItem, node<type>* currentNode) const;
    void insertFromNode(node<type>*& newNode, node<type>*& currentNode);
    void deleteNodeFromTree(node<type>*& deathRowNode);
};

template <class type>
bool binarySearchTree<type>::searchFromNode(const type &searchItem, node<type>* currentNode) const
{
    // ensure that we aren't looking at an empty node
    if (currentNode != nullptr){

        // if the search item equals the current node
        if (searchItem == *(currentNode->info)){

            // output the node
            std::cout << *(currentNode->info) << '\n';

            // exit the function
            return true;
        }

        // if the search item is less than the current node, search the left side
        if (searchItem < *(currentNode->info)){
            return searchFromNode(searchItem, currentNode->lLink);
        }

        // if the search item is greater than the current node, search the right side
        else if (searchItem > *(currentNode->info)){
            return searchFromNode(searchItem, currentNode->rLink);
        }
    }

    // if we didn't find it, we can assume the function failed and return false
    return false;
}

template <class type>
bool binarySearchTree<type>::search(const type &searchItem) const
{
    // starts off the recusrive search from the root node
    return searchFromNode(searchItem, this->root);
}

template<class type>
void binarySearchTree<type>::insertFromNode(node<type>*& newNode, node<type>*& currentNode)
{
    // if the current node is empty, set the current node to the new node
    if (!currentNode){
        currentNode = newNode;
    }

    else{
        // We can't have duplicate items
        if (*(currentNode->info) == *(newNode->info)){
            throw std::invalid_argument("Duplicate items not allowed (Line 84)");
        }

        // if the new node is greater than the current node, work down the right subtree
        else if(*(currentNode->info) < *(newNode->info)){
            insertFromNode(newNode, currentNode->rLink);
        }

        // if the new node is less than the current node, work down the left subtree
        else if(*(currentNode->info) > *(newNode->info)){
            insertFromNode(newNode, currentNode->lLink);
        }
    }
}

template <class type>
void binarySearchTree<type>::insert(const type &insertItem)
{
    // create a new node, populate it with the item to be inserted
    node<type>* newNode = new node<type>;
    newNode->info = new type(insertItem);
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;

    // try to insert node, starting at root, if it fails, throw an error and delete the memory to prevent leaks
    try
    {
        insertFromNode(newNode, this->root);
    }
    catch(const std::invalid_argument &e)
    {
        std::cout << e.what();
        delete newNode;
    }
    
}

template <class type>
void binarySearchTree<type>::deleteNode(const type &deleteItem)
{
    // create two node pointers, one will point to the current node and one will point to the parent of the current
    node<type>* currentNode = this->root;
    node<type>* parentNode = currentNode;
    bool found = false;

    if(this->isEmpty()){
        throw std::invalid_argument("Cannot delete from empty tree (Line 125)");
    }

    // while the current node isn't empty, iterate over the tree
    while (currentNode != nullptr){

        // if the current item and the item to be deleted match, then decided how to delete the item
        if (deleteItem == *(currentNode->info)){

            found = true;

            // if it is the root node
            if (currentNode == this->root){
                deleteNodeFromTree(this->root);
            }

            // if the item is less than the parent
            if (deleteItem < *(parentNode->info)){
                deleteNodeFromTree(parentNode->lLink);
            }

            // if the item is greater than the parent
            else if (deleteItem > *(parentNode->info)){
                deleteNodeFromTree(parentNode->rLink);
            }

            break;
        }

        // if its less than, move to the left, greater than, move to the right

        else if (deleteItem > *(currentNode->info)){
            parentNode = currentNode;
            currentNode = currentNode->rLink;
        }

        else if (deleteItem < *(currentNode->info)){
            parentNode = currentNode;
            currentNode = currentNode->lLink;
        }
    }

    // if the item isn't found in the tree, throw an error
    if (!found){
        throw std::invalid_argument("is not found in the tree");
    }
}

template <class type>
void binarySearchTree<type>::deleteNodeFromTree(node<type>*& deathRowNode)
{
    // create three nodes
    node<type>* replacementNode;
    node<type>* replacementParent;
    node<type>* temporaryNode;

    // if the node to be deleted is empty, throw an error
    if (!deathRowNode){
        throw std::invalid_argument("Cannot delete a node that doesn't exist (line 154)");
    }

    // if the node is a leaf, free the node pointer, and delete the node
    if (deathRowNode->lLink == nullptr && deathRowNode->rLink == nullptr){
        temporaryNode = deathRowNode;
        deathRowNode = nullptr;
        delete temporaryNode;
    }

    // if the left side is empty, cut the deleting node out and replace with the right side subtree
    else if (!deathRowNode->lLink){
        temporaryNode = deathRowNode;
        deathRowNode = temporaryNode->rLink;
        delete temporaryNode;
    }

    // if the right side is empty, cut the deleting node out and replace with the left side subtree
    else if (!deathRowNode->rLink){
        temporaryNode = deathRowNode;
        deathRowNode = temporaryNode->lLink;
        delete temporaryNode;
    }

    else{

        // first we want to find a next largest successor node, then set the current node to house the data of the succesor
        // delete the data previously stored in the node, delete the successor

        // set the replacement node to the root of the right side subtree
        replacementNode = deathRowNode->rLink;
        replacementParent = nullptr;

        // while there are nodes below on the left side, move downwards
        while (replacementNode->lLink != nullptr)
        {
            replacementParent = replacementNode;
            replacementNode = replacementNode->lLink;
        }

        // extract the data from the node that needs to be deleted into a temporary storage
        type *tempInfo = deathRowNode->info;

        // replace the data in the node with the successor data
        deathRowNode->info = replacementNode->info;

        // replace the successor node with the temporary data
        replacementNode->info = tempInfo;

        // remove the left link of the parent of the replacement node
        replacementParent->lLink = nullptr;
        // delete the replacement and set it to nullptr
        delete replacementNode;
        replacementNode = nullptr;
    }
}

#endif