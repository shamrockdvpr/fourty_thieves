#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <regex>
#include "doubleLinkedList.h"
#include "binarySearchTree.h"
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
    std::regex quitStr{R"(^q|quit$)"};
    std::regex undoStr{R"(^u|undo$)"};
    std::regex helpStr{R"(^\?|help$)"};
    std::regex hintStr{R"(^h|hint$)"};
    std::regex credStr{R"(^c|credits$)"};

    std::cout << "+" << std::setw(75) << std::setfill('-') << "+\n" << std::setfill(' ');
    std::cout << "Welcome to 40 thieves!\n";
    std::cout << "\nAt any time during the game type any of the following:\n: q or quit to quit the game\n: u or undo to undo move\n: h or hint to have the computer generate the optimal move\n: ? or help to bring up a list of commands\n: c or credits to bring up a credits page\n";
    std::cout << "\nMoves can be entered using the following syntax: deck -> deck\nThe important part is that you enter two decks and make sure to get the names of the decks off the board!\n";
    std::cout << "\nDecks should be in letter-digit form, the letter refers to the deck type:\n- S for the stock, W for the waste or discard pile, T for the tableau, and F for the foundations\nIf you are referencing a tableau or foundation, be sure to include the number of the deck you want\nthe board contains a label next to every deck for convenience";
    std::cout << "For example, all of the following are valid entries: \n - f1 to t5\n - s->t1\n - w move to T1\n - s move supercalifragalistically to t5\n";
    std::cout << "Fortunately we'll let you know if a move is invalid! Remember to type ? or help at any time to get help and have fun!\n";
    std::cout << "\nType 'Start' when you are ready to go: ";
    std::string dummyVar;
    std::getline(std::cin, dummyVar);
    
    std::cout << game << std::endl;

    while (true){
        std::string line;
        std::cout << "Enter move: ";
        std::getline(std::cin, line);

        std::transform(line.begin(), line.end(), line.begin(), 
                    [](unsigned char c){return std::tolower(c); });

        std::smatch commands;

        if (std::regex_match(line, quitStr)) break;

        else if(std::regex_match(line, undoStr)) {
            
            try{
                game.undo();
                std::cout << "Undid move\n";
            } catch(const std::invalid_argument& e) {
                std::cout << e.what() << '\n';
            }
            std::cout << game << std::endl;
        }

        else if (std::regex_match(line, commands, moveStrings)){
            std::string startString = commands[1];
            std::string destString = commands[2];

            try{game.moveCards(startString, destString);}
            catch(const std::invalid_argument& e){std::cout << e.what() << '\n';}
            std::cout << "Prev move: " << startString << " -> " << destString << std::endl;
            std::cout << game << std::endl;
        }
    }

    //gameplay loop to write
    // check for game end state
    // output win or lose if needed
    // offer to play again
    // either reset board or exit program
    
    return 0;
}
