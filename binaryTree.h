/*
/* Program name: binaryTree.h
* Author: Charlie Shaneck
* Date last updated: 5/10/2025
* Purpose: Define a binary tree base class for extension to the binary search tree
*/ 

#ifndef TREE_H
#define TREE_H
#include "linkedList.h"
#include <iostream>
#include <sstream>

template <class type>
class binaryTree
{
public:
    bool isEmpty() const;

    int treeNodeCount(const type &searchItem) const;
    int treeLeavesCount(const type &searchItem) const;
    void destroyTree();
    type getRoot() const;
    
    virtual void insert(const type &insertItem) = 0;
    virtual void deleteNode(const type &deleteItem) = 0;

    const binaryTree<type> &operator=(const binaryTree<type> &otherTree);
    binaryTree(const binaryTree<type> &otherTree);
    binaryTree();
    ~binaryTree();

protected:
    node<type> *root;

private:
    void copyTree(node<type> *&copiedTreeRoot, node<type> *otherTreeRoot);
    void destroy(node<type> *&p);
    int nodeCount(const type &searchItem, node<type> *p, int count = 0) const;
    int leavesCount(const type &searchItem, node<type> *p, int count = 0) const;
};

template <class type>
bool binaryTree<type>::isEmpty() const
{
    return (root == nullptr);
}

template <class type>
binaryTree<type>::binaryTree()
{
    root = nullptr;
}

template <class type>
int binaryTree<type>::treeNodeCount(const type &searchItem) const
{
    return nodeCount(searchItem, root);
}

template <class type>
int binaryTree<type>::treeLeavesCount(const type &searchItem) const
{
    return leavesCount(searchItem, root);
}

template <class type>
void binaryTree<type>::destroy(node<type> *&p)
{
    if (p != nullptr)
    {
        destroy(p->left);
        destroy(p->right);
        delete p;
        p = nullptr;
    }
}

template <class type>
void binaryTree<type>::destroyTree()
{
    destroy(root);
}

template <class type>
type binaryTree<type>::getRoot() const
{
    return *(root->data);
}

template <class type>
binaryTree<type>::~binaryTree()
{
    destroy(root);
}

template <class type>
binaryTree<type>::binaryTree(const binaryTree<type> &otherTree)
{
    if (otherTree.root == nullptr)
        root = nullptr;
    else
        copyTree(root, otherTree.root);
}

template <class type>
const binaryTree<type> &binaryTree<type>::operator=(const binaryTree<type> &otherTree)
{
    if (this != &otherTree)
    {
        if (root != nullptr)
        destroy(root);
        if (otherTree.root == nullptr)
        root = nullptr;
        else
        copyTree(root, otherTree.root);
    }
    return *this;
}

template <class type>
void binaryTree<type>::copyTree(node<type> *&copiedTreeRoot, node<type> *otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
        copiedTreeRoot = nullptr;
    else
    {
        copiedTreeRoot = new node<type>;
        copiedTreeRoot->data = new type(*otherTreeRoot->data);
        copyTree(copiedTreeRoot->left, otherTreeRoot->left);
        copyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

// lab=> implement both of these
template <class type>
int binaryTree<type>::nodeCount(const type &searchItem, node<type> *p, int count) const
{
    if (p == nullptr)
        return count;
    else if (*p->data == searchItem)
        return count + 1;
    else if (*p->data > searchItem)
        return nodeCount(searchItem, p->left, count + 1);
    else
        return nodeCount(searchItem, p->right, count + 1);
}

template <class type>
int binaryTree<type>::leavesCount(const type &searchItem, node<type> *p, int count) const
{
    // int count = 0;
    if (p == nullptr)
        return count;
    if ((p->left == nullptr) && (p->right == nullptr))
        count += 1;
    if (*p->data == searchItem)
        return count;
    if (p->left != nullptr && *p->data > searchItem)
        count = leavesCount(searchItem, p->left, count);
    if (p->right != nullptr && searchItem > *p->data)
        count = leavesCount(searchItem, p->right, count);
    return count;
}

#endif