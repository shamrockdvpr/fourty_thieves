/*
/* Program name: main.cpp
* Author: Charlie Shaneck
* Date last updated: 5/10/2025
* Purpose: Play the game of 40 Thieves solitaire
*/ 

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <algorithm>
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
    FINAL TODO:
    - check code comments and clean up where needed
    - project summary
    - final testing
    - submit!
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
    std::cout << "\nFor example, all of the following are valid entries: \n - f1 to t5\n - s->t1\n - w move to T1\n - s move supercalifragalistically to t5\n";
    std::cout << "\nFortunately we'll let you know if a move is invalid! Remember to type ? or help at any time to get help and have fun!\n";
    std::cout << "\nType 'Start' when you are ready to go: ";
    std::string dummyVar;
    std::getline(std::cin, dummyVar);
    
    std::cout << game << std::endl;

    while (true){

        // generate a list of moves for hints
        game.generateMovesTree();

        // if the game does not have has moves left, determine if it is a win condition or not
        if (!game.movesLeft()){
            // if it is a win condtion, offer to let the user play again or quit
            if (game.determineOutcome()){
                std::cout << "\nCongrats, you won! \nYour score was: " << game.getScore();
            }
            // if it is a loose condito
            else{
                std::cout << "\nBetter luck next time :(";
            }

            std::string playAgainStr;
            std::cout << "\nWould you like to play again? y/n: ";
            std::cin >> playAgainStr;

            std::transform(playAgainStr.begin(), playAgainStr.end(), playAgainStr.begin(), 
                    [](unsigned char c){return std::tolower(c); });

            if (playAgainStr == "y" || playAgainStr == "yes"){
                game.resetGamespace();
                std::cout << game << std::endl;
            }
            else if (playAgainStr == "n" || playAgainStr == "no"){
                std::cout << "Thanks for playing!";
                break;
            }
        }


        std::string line;
        std::cout << "Enter move or command: ";
        std::getline(std::cin, line);

        std::transform(line.begin(), line.end(), line.begin(), 
                    [](unsigned char c){return std::tolower(c); });

        std::smatch commands;

        // quit
        if (std::regex_match(line, quitStr)) break;

        else if (std::regex_match(line, credStr)) {
            std::cout << "\n\nThis game was developed by Charlie Shaneck\nVersion: 1.0.0\nLast Updated: 5/10/2025\nWritten using C++ for CSCI 202 Data Structures at Ivy Tech\n";
        }

        else if(std::regex_match(line, helpStr)){
            std::cout << "\nWelcome to the help menu!";
            std::cout << "\nFeeling stuck? h or hint will have the comupter play the most optimal move for you";
            std::cout << "\nWant to see who made this? c or credits will bring up a credits menu";
            std::cout << "\nStill unsure? Typing ? or help will bring this menu back up";
            std::cout << "\nWant to leave? q or quit will quit the program";
            std::cout << "\nFinally to move, enter the deck to draw a card from and the deck to place the card in\nUse the names printed next to the deck to identify them, and as long as both decks are written the move should run.\nIf a move is invalid the game will let you know";
            std::cout << "\nHopefully this helped, have fun and good luck!\n";
        }

        else if (std::regex_match(line, hintStr)){
            game.getHint();
            std::cout << "Played hint!\n";
            std::cout << game << std::endl;
        }

        // undo
        else if(std::regex_match(line, undoStr)) {
            
            try{
                game.undo();
                std::cout << "Undid move\n";
            } catch(const std::invalid_argument& e) {
                std::cout << e.what() << '\n';
            }
            std::cout << game << std::endl;
        }

        // move
        else if (std::regex_match(line, commands, moveStrings)){
            std::string startString = commands[1];
            std::string destString = commands[2];

            try{game.moveCards(startString, destString);}
            catch(const std::invalid_argument& e){std::cout << e.what() << '\n';}
            std::cout << "Prev move: " << startString << " -> " << destString << std::endl;
            std::cout << game << std::endl;
        }

        else{
            std::cout << "\nSorry, that input is not supported\n";
        }
    }
    return 0;
}
