#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"

template <class type>
class binarySearchTree : public binaryTree<type>{
public:
    void insert(const type &insertItem) override;
    void deleteNode(const type &deleteItem) override;
    type getMax();

private:
    void insertFromNode(node<type>*& newNode, node<type>*& currentNode);
    void deleteNodeFromTree(node<type>*& deathRowNode);
};

template<class type>
void binarySearchTree<type>::insertFromNode(node<type>*& newNode, node<type>*& currentNode)
{
    // if the current node is empty, set the current node to the new node
    if (!currentNode){
        currentNode = newNode;
    }

    else{
        // We can't have duplicate items
        if (*(currentNode->data) == *(newNode->data)){
            throw std::invalid_argument("Duplicate items not allowed (Line 84)");
        }

        // if the new node is greater than the current node, work down the right subtree
        else if(*(currentNode->data) < *(newNode->data)){
            insertFromNode(newNode, currentNode->right);
        }

        // if the new node is less than the current node, work down the left subtree
        else if(*(currentNode->data) > *(newNode->data)){
            insertFromNode(newNode, currentNode->left);
        }
    }
}

template <class type>
void binarySearchTree<type>::insert(const type &insertItem)
{
    // create a new node, populate it with the item to be inserted
    node<type>* newNode = new node<type>;
    newNode->data = new type(insertItem);
    newNode->left = nullptr;
    newNode->right = nullptr;

    // try to insert node, starting at root, if it fails, throw an error and delete the memory to prevent leaks
    try
    {
        insertFromNode(newNode, this->root);
    }
    catch(const std::invalid_argument &e)
    {
        //std::cout << e.what();
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
        if (deleteItem == *(currentNode->data)){

            found = true;

            // if it is the root node
            if (currentNode == this->root){
                deleteNodeFromTree(this->root);
            }

            // if the item is less than the parent
            if (deleteItem < *(parentNode->data)){
                deleteNodeFromTree(parentNode->left);
            }

            // if the item is greater than the parent
            else if (deleteItem > *(parentNode->data)){
                deleteNodeFromTree(parentNode->right);
            }

            break;
        }

        // if its less than, move to the left, greater than, move to the right

        else if (deleteItem > *(currentNode->data)){
            parentNode = currentNode;
            currentNode = currentNode->right;
        }

        else if (deleteItem < *(currentNode->data)){
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
    }

    // if the item isn't found in the tree, throw an error
    if (!found){
        throw std::invalid_argument("is not found in the tree");
    }
}

template <class type>
type binarySearchTree<type>::getMax()
{
    node<type> *currentNode;
    currentNode = this->root;
    while(currentNode->right != nullptr){
        currentNode = currentNode->right;
    }
    return *(currentNode->data);
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
    if (deathRowNode->left == nullptr && deathRowNode->right == nullptr){
        temporaryNode = deathRowNode;
        deathRowNode = nullptr;
        delete temporaryNode;
    }

    // if the left side is empty, cut the deleting node out and replace with the right side subtree
    else if (!deathRowNode->left){
        temporaryNode = deathRowNode;
        deathRowNode = temporaryNode->right;
        delete temporaryNode;
    }

    // if the right side is empty, cut the deleting node out and replace with the left side subtree
    else if (!deathRowNode->right){
        temporaryNode = deathRowNode;
        deathRowNode = temporaryNode->left;
        delete temporaryNode;
    }

    else{

        // first we want to find a next largest successor node, then set the current node to house the data of the succesor
        // delete the data previously stored in the node, delete the successor

        // set the replacement node to the root of the right side subtree
        replacementNode = deathRowNode->right;
        replacementParent = nullptr;

        // while there are nodes below on the left side, move downwards
        while (replacementNode->left != nullptr)
        {
            replacementParent = replacementNode;
            replacementNode = replacementNode->left;
        }

        // extract the data from the node that needs to be deleted into a temporary storage
        type *tempdata = deathRowNode->data;

        // replace the data in the node with the successor data
        deathRowNode->data = replacementNode->data;

        // replace the successor node with the temporary data
        replacementNode->data = tempdata;

        // remove the left link of the parent of the replacement node
        replacementParent->left = nullptr;
        // delete the replacement and set it to nullptr
        delete replacementNode;
        replacementNode = nullptr;
    }
}

#endif