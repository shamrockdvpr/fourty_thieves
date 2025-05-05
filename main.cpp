#ifdef _WIN32
#include <Windows.h>
#endif

#include "card.h"
#include <iostream>
#include "doubleLinkedList.h"
#include "stack.h"
#include "gamespace.h"

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

/* TODO:

- Implement game functions
    - input parsing
    - moves
    - move
    - undo function
    - Shuffling!!!

- hint system
    - tree
    - binary tree
    - hint function

- wrapping up
    - Final Tests
    - Playtesting
    - Project Summary

*/

    gamespace game;
    std::cout << game << std::endl;
    game.moveCards(2, 7);
    game.moveCards(2, 7);
    game.moveCards(2, 7);
    game.moveCards(2, 7);
    game.moveCards(5, 6);
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
