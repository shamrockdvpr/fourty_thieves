#ifndef TREE_H
#define TREE_H
#include "linkedList.h"
#include <iostream>
#include <sstream>

template <class type>
class binaryTree
{
public:
    const binaryTree<type> &operator=(const binaryTree<type> &otherTree);
    bool isEmpty() const;
    void inorderTraversal() const;
    std::string preorderTraversal() const;
    void postorderTraversal() const;
    int treeHeight() const;
    int treeNodeCount(const type &searchItem) const;
    int treeLeavesCount(const type &searchItem) const;
    void destroyTree();
    virtual bool search(const type &searchItem) const = 0;
    virtual void insert(const type &insertItem) = 0;
    virtual void deleteNode(const type &deleteItem) = 0;
    binaryTree(const binaryTree<type> &otherTree);
    binaryTree();
    ~binaryTree();

protected:
    node<type> *root;

private:
    void copyTree(node<type> *&copiedTreeRoot, node<type> *otherTreeRoot);
    void destroy(node<type> *&p);
    void inorder(node<type> *p) const;
    void preorder(node<type> *p, std::ostringstream &) const;
    void postorder(node<type> *p) const;
    int height(node<type> *p) const;
    int max(int x, int y) const;
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
void binaryTree<type>::inorderTraversal() const
{
    inorder(root);
}

template <class type>
std::string binaryTree<type>::preorderTraversal() const
{
    std::ostringstream out;
    preorder(root, out);
    return out.str();
}

template <class type>
void binaryTree<type>::postorderTraversal() const
{
    postorder(root);
}

template <class type>
int binaryTree<type>::treeHeight() const
{
    return height(root);
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
        destroy(p->lLink);
        destroy(p->rLink);
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
binaryTree<type>::~binaryTree()
{
    destroy(root);
}

template <class type>
void binaryTree<type>::inorder(node<type> *p) const
{
    /*1. inorder left sub tree
    2. visit the current node
    3. inorder right sub tree */
    if (p != nullptr)
    {
        inorder(p->lLink);
        std::cout << *p->info << "\n\n";
        inorder(p->rLink);
    }
}

template <class type>
void binaryTree<type>::preorder(node<type> *p, std::ostringstream &out) const
{
    /*1. visit current node
    2. preorder left sub tree
    3. preorder right sub tree*/
    if (p != nullptr)
    {
        out << *p->info << "\n\n";
        preorder(p->lLink, out);
        preorder(p->rLink, out);
    }
}

template <class type>
void binaryTree<type>::postorder(node<type> *p) const
{
    /*1. preorder right sub tree
    2. preorder left sub tree
    3. visit current node*/
    if (p != nullptr)
    {
        postorder(p->lLink);
        postorder(p->rLink);
        std::cout << *p->info << "\n\n";
    }
}

template <class type>
int binaryTree<type>::height(node<type> *p) const
{
    if (p == nullptr)
        return 0;
    else
        return 1 + max(height(p->lLink), height(p->rLink));
}

template <class type>
int binaryTree<type>::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
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
        copiedTreeRoot->info = new type(*otherTreeRoot->info);
        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
}

// lab=> implement both of these
template <class type>
int binaryTree<type>::nodeCount(const type &searchItem, node<type> *p, int count) const
{
    if (p == nullptr)
        return count;
    else if (*p->info == searchItem)
        return count + 1;
    else if (*p->info > searchItem)
        return nodeCount(searchItem, p->lLink, count + 1);
    else
        return nodeCount(searchItem, p->rLink, count + 1);
}

template <class type>
int binaryTree<type>::leavesCount(const type &searchItem, node<type> *p, int count) const
{
    // int count = 0;
    if (p == nullptr)
        return count;
    if ((p->lLink == nullptr) && (p->rLink == nullptr))
        count += 1;
    if (*p->info == searchItem)
        return count;
    if (p->lLink != nullptr && *p->info > searchItem)
        count = leavesCount(searchItem, p->lLink, count);
    if (p->rLink != nullptr && searchItem > *p->info)
        count = leavesCount(searchItem, p->rLink, count);
    return count;
}

#endif