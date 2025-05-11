#ifndef GAMESPACE_H
#define GAMESPACE_H
#include "stack.h"
#include "card.h"
#include "move.h"
#include "binarySearchTree.h"
#include <random>

class gamespace{
public:
    // constructor
    gamespace();

    // card movement
    bool isValid(stack<card>&, stack<card>&);
    void moveCards(std::string, std::string);
    void undo();

    // score manipulation
    void resetScore() {score = 0;};
    void updateScore(int scoreInc) {score += scoreInc;};
    int getScore() {return score;};

    // game state determiners
    void generateMovesTree();
    bool movesLeft();
    bool determineOutcome();
    void resetGamespace();

    void getHint();

    // output
    friend std::ostream &operator<<(std::ostream& out, const gamespace game);

private:
    // score and number of decks in game
    int score;
    const static int decksCount = 20;

    // list of all decks and game history
    stack<card> decks[decksCount];
    stack<move> gameHistory;

    // hints
    binarySearchTree<move> hints;

    // shuffles deck, private because no one other than the gamespace should be shuffling anything
    void shuffle(stack<card>&);
    // calculates score increases, private to prevent unwanted score manipulation
    int calculateScoreInc(stack<card>&, stack<card>&);
};

#endif