#ifdef _WIN32
#include <Windows.h>
#endif

#include "card.h"
#include <iostream>
#include "linkedList.h"
#include "main.h"

/*
    Note on suits:
        Spades = 1
        HEART = 2
        DIAMOND = 3
        CLUB = 4
*/

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    linkedList<int> intList;


    intList.insert(5);
    intList.insert(8);
    intList.insert(2);
    intList.insert(7);
    intList.deleteItem(7);

    intList.insert(0);
    intList.insert(5);
    intList.insert(1000000);

    for (auto it = intList.begin(); it != intList.end(); ++it){
        std::cout << *it << std::endl;
    };
}