#ifdef _WIN32
#include <Windows.h>
#endif

#include "card.h"
#include <iostream>
#include "doubleLinkedList.h"
#include "main.h"


int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    linkedList<int> intList;
    doubleLinkedList<int> dblList;

    /* TODO:
        - Debug linked and double linked list
        - debug delete from linked and double linked
            Priority: URGENT
            need to get this fixed BEFORE starting stack and trees
        - Fix documentation
        - implement stack
        - implement tree
        - implement binary tree
        - UI Demo for testing
        - begin on game functionality
        - Begin UI development
        - Final Tests
        - Project Summary
    */

    intList.insert(5);
    intList.insert(8);
    intList.insert(6);
    intList.insert(5);
    intList.insert(8);
    intList.insert(8);
    intList.insert(266);
    intList.insert(77);
    intList.insert(55);
    intList.insert(2);
    intList.insert(9);
    intList.insert(787);
    intList.insert(55);
    intList.insert(83);
    intList.insert(29);
    intList.insert(77);

    dblList.insert(5);
    dblList.insert(8);
    dblList.insert(6);
    dblList.insert(5);
    dblList.insert(8);
    dblList.insert(8);
    dblList.insert(266);
    dblList.insert(77);
    dblList.insert(55);
    dblList.insert(2);
    dblList.insert(9);
    dblList.insert(787);
    dblList.insert(55);
    dblList.insert(83);
    dblList.insert(29);
    dblList.insert(77);

    std::cout << "Single Linked:" << std::endl;
    auto it = intList.begin();
    std::cout << *it << std::endl;
    do
    {
        ++it;
        std::cout << *it << std::endl;
    } while (it != intList.end());

    std::cout << "Forwards:" << std::endl;
    it = dblList.begin();
    std::cout << *it << std::endl;
    do
    {
        ++it;
        std::cout << *it << std::endl;
    } while (it != dblList.end());

    std::cout << "Backwards:" << std::endl;
    it = dblList.end();
    std::cout << *it << std::endl;
    do
    {
        --it;
        std::cout << *it << std::endl;
    } while (it != dblList.begin());
    
}