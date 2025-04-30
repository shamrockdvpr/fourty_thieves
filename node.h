#ifndef NODE_H
#define NODE_H

template <class type>
struct node{
    type* data;
    // use as linked list -> link
    // named as such to make it easier to handle binary trees
    node<type>* right;
    node<type>* left;

    //node() {left = nullptr; right = nullptr;};

    ~node() {delete data;}
};


#endif