#ifdef _WIN32
#include <Windows.h>
#endif

#include "card.h"
#include <iostream>
#include <sstream>
#include <string>
#include "doubleLinkedList.h"
#include "stack.h"
#include "gamespace.h"

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

/* TODO:

- Implement game functions
    - Test move function
    - REGEX for user input to move function
    - test undo function
    - write validation code
    - write gameplay loop
    - Shuffling!!!

- hint system (if time)
    - tree
    - binary tree
    - hint function

- wrapping up
    - Final Tests
    - Playtesting
    - Project Summary
*/

    gamespace game;
    std::cout << "+" << std::setw(75) << std::setfill('-') << "+\n" << std::setfill(' ');
    std::cout << "Welcome to 40 thieves!\n";
    std::cout << game << std::endl;
    

    //gameplay loop
    // show board using <<
    // wait for input
    // parse input
    // case 1
    //      send to moveCards()
    // case 2
    //      send to undoMove()
    // check for game end state
    // output win or lose if needed
    // offer to play again
    // either reset board or exit program
    
    return 0;
}
