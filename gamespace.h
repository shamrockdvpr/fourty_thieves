#ifndef GAMESPACE_H
#define GAMESPACE_H
#include "stack.h"
#include "card.h"
#include "move.h"
#include "doubleLinkedList.h"

class gamespace{
public:
    gamespace();
    bool isValid(stack<card>&, stack<card>&);
    void moveCards(int test1, int test2);
    void resetScore();
    void updateScore(int scoreInc);
    bool movesLeft();
    void undo();
    friend std::ostream &operator<<(std::ostream& out, const gamespace game);

private:
    int score;
    stack<card> foundations[8];
    stack<card> tableaus[10];
    stack<card> waste;
    stack<card> stock;
    doubleLinkedList<move> gameHistory;
    Iterator<move> currentMove;
};

gamespace::gamespace() 
    : 
    foundations{{13}, {13}, {13}, {13}, {13}, {13}, {13}, {13}},
    tableaus{{104}, {104}, {104}, {104}, {104}, {104}, {104}, {104}, {104}, {104}},
    waste(104),
    stock(110),
    gameHistory(),
    currentMove(gameHistory.begin())
{
    score = 0;

    // populates stock with 2 full decks
    for (int i = 0; i < 52; ++i){
        card *newCard = new card((i % 13 + 1), (i / 13));
        stock.push(*newCard);
        delete newCard;
    }
    for (int i = 0; i < 52; ++i){
        card *newCard = new card((i % 13 + 1), (i / 13));
        stock.push(*newCard);
        delete newCard;
    }

    // shuffle stock

    // deals 4 cards to each tableau
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 10; ++j){
            tableaus[j].push(stock.pop());
        }
    }
}

void gamespace::resetScore()
{
    score = 0;
}

void gamespace::updateScore(int scoreInc)
{
    score += scoreInc;
}

void gamespace::moveCards(int test1, int test2)
{
    // determine if move is valid
    // calculate change in score
    // create new move obj
    // add to move list
    // increm score

    // test of class functions
    foundations[test1].push(tableaus[test2].pop());
    updateScore(5);
}

std::ostream &operator<<(std::ostream &out, const gamespace game)
{
    // outputs top of box
    out << "+------------------------------------------------------------+\n";

    // outputs score
    out << "|" << std::setw(30) << "Score: " << game.score << std::setw(30) << "|";

    // outputs bottom of scoreboard
    out << "\n|------------------------------------------------------------|";
    
    // right justifies stock , allows for empty deck
    out << "\n|" << std::setw(53) << "Stock: ";
    try
    {
        out << game.stock.peek();
    }
    catch(std::out_of_range)
    {
        out << "[   ]";
    }

    // right justifies waste , allows for empty deck
    out << "  |\n|" << std::setw(53) << "Waste: ";
    try
    {
        out << game.waste.peek();
    }
    catch(std::out_of_range)
    {
        out << "[   ]";
    }
    // creates a blank line
    out << "  |\n|" << std::setw(65) << "|\n|  ";
    

    // outputs both lines of foundations
    for (int i = 0; i < 4; ++i){
        out << "F" << i << ": ";
        try
        {
            out << game.foundations[i].peek();
        }
        catch(std::out_of_range)
        {
            out << "[   ]";
        }
        out << "   ";
    }
    out << std::setw(15) << "|\n|  ";

    for (int i = 4; i < 8; ++i){
        out << "F" << i << ": ";
        try
        {
            out << game.foundations[i].peek();
        }
        catch(std::out_of_range)
        {
            out << "[   ]";
        }
        out << "   ";
    }
    out << std::setw(13) << "|\n|";

    // blank line
    out << std::setw(65) << "|\n|  ";

    // outputs tableaus
    for (int i = 0; i < 10; ++i){
        // divides output into two lines
        if (i == 5) out << "   |\n|  ";
        out << "T" << i << ": ";
        try
        {
            out << game.tableaus[i].peek();
        }
        catch(std::out_of_range)
        {
            out << "[   ]";
        }
        out << "  ";
    }
    out << "   |";
    // bottom of box
    out << "\n+------------------------------------------------------------+\n";
    return out;
}


#endif