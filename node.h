#ifndef NODE_H
#define NODE_H

template <class type>
struct node{
    type* data;
    node<type>* right;
    node<type>* left;

    node() {left = nullptr; right = nullptr};

    ~node{delete data;}
};


#endif