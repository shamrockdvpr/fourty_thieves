#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "linkedList.h"
template <class type>
class binaryTree : linkedList<type>
{
private:
    
public:
    binaryTree();
    ~binaryTree();
};

template <class type>
binaryTree<type>::binaryTree()
{
}

template <class type>
binaryTree<type>::~binaryTree()
{
}


#endif