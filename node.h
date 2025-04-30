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

// template<class type>
// class Iterator{
//     public:
//         Iterator(node<type>* currentNode);
//         type &operator*();
//         Iterator operator++();
//         bool operator==(const Iterator &otherIt) const;
//         bool operator!=(const Iterator &otherIt) const;
//     private:
//         node<type>* current;
// };


#endif