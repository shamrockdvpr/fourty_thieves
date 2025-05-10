#ifdef _WIN32
#include <Windows.h>
#endif

#include "card.h"
#include "move.h"
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "doubleLinkedList.h"
#include "stack.h"
#include "gamespace.h"

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

/* TODO:

- Implement game functions
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

    std::regex moveStrings{R"(^([s]|[w]|[f][0-7]|[t][0-9]).*?([s]|[w]|[f][0-7]|[t][0-9])$)"};
    std::regex quitStr{R"(^q)"};

    std::cout << "+" << std::setw(75) << std::setfill('-') << "+\n" << std::setfill(' ');
    std::cout << "Welcome to 40 thieves!\n";
    std::cout << game << std::endl;

    while (true){
        std::string line;
        std::cout << "Enter move, type q to exit: ";
        std::getline(std::cin, line);

        std::transform(line.begin(), line.end(), line.begin(), 
                    [](unsigned char c){return std::tolower(c); });

        if (std::regex_match(line, quitStr)) break;

        std::smatch commands;
        if (std::regex_match(line, commands, moveStrings)){
            std::string startString = commands[1];
            std::string destString = commands[2];

            try{game.moveCards(startString, destString);}
            catch(const std::invalid_argument& e){std::cout << e.what() << '\n';}
            std::cout << "Prev move: " << startString << " -> " << destString << std::endl;
            std::cout << game << std::endl;
        }
    }

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
