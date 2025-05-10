#include "gamespace.h"

gamespace::gamespace() 
    : 
    decks{{104}, // stock Index pos - 0
          {104}, // waste Index pos 1
          {13}, {13}, {13}, {13}, {13}, {13}, {13}, {13}, // foundations - Index pos 2 - 9
          {104}, {104}, {104}, {104}, {104}, {104}, {104}, {104}, {104}, {104} //tableaus Index Pos 10 - 19
    },
    gameHistory()
{
    score = 0;

    // populates stock with 2 full decks
    for (int i = 0; i < 52; ++i){
        card *newCard = new card((i % 13 + 1), (i / 13));
        decks[0].push(*newCard);
        delete newCard;
    }
    for (int i = 0; i < 52; ++i){
        card *newCard = new card((i % 13 + 1), (i / 13));
        decks[0].push(*newCard);
        delete newCard;
    }

    // shuffle stock

    // deals 4 cards to each tableau
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 10; ++j){
            decks[j + 10].push(decks[0].pop());
        }
    }
}

bool gamespace::isValid(stack<card> &startDeck, stack<card> &destDeck)
{
    // it is impossible to deal cards from an empty deck or to deal cards to a full deck
    if (startDeck.isEmpty()) return false;
    if (destDeck.isFull()) return false;

    // uses the difference in memory address from the current deck and start of decks array to determine what type of deck it is
    int startDeckType = &startDeck - decks;
    int destDeckType = &destDeck - decks;

    //using the type of deck that the destination is, decide which set of rules to follow

    // if the destination is the stock pile it is invalid
    if (destDeckType == 0) return false;

    // if the destination is the waste pile and the start is the stock, the move is valid
    if (destDeckType == 1 && startDeckType == 0) return true;

    // destination is a foundation
    if (10 > destDeckType && destDeckType > 2){

        // if the foundation isnt empty
        if (!destDeck.isEmpty()){
            // if the suits dont match
            if (destDeck.peek().getEnumSuit() != startDeck.peek().getEnumSuit()) return false;

            // if the foundation isnt empty and the new card is in ascending order move is valid
            else if ((startDeck.peek().getNumber() - destDeck.peek().getNumber() == 1))
                return true;
        }

        // if the foundation is empty and the card being inserted is  an ace the the move is  valid
        if (destDeck.isEmpty() && startDeck.peek().getNumber() == 1) return true;

        // if we dont pass all the tests, the move is invalid
        return false;
    }


    // if the destination is a tableau
    if (destDeckType > 10){
        // if the tableau is empty, any card is valid
        if (destDeck.isEmpty()) return true;

        // if the suits match and the numbers are descending the move is valid
        else if (destDeck.peek().getEnumSuit() == startDeck.peek().getEnumSuit() && (destDeck.peek().getNumber() - startDeck.peek().getNumber() == 1))
            return true;

        // if no condtion was met the move is invalid
        return false;
    }
    // if we passed all the tests, then the move is assumed to be true
    return false;
}

void gamespace::moveCards(std::string startString, std::string destString)
{
    // determine if move is valid
    // calculate change in score
    // create new move obj
    // add to move list
    // increm score

    // // make both strings lower case for easier processing
    // std::transform(startString.begin(), startString.end(), startString.begin(), 
    //                 [](unsigned char c){return std::tolower(c); });
    // std::transform(destString.begin(), destString.end(), destString.begin(), 
    //                 [](unsigned char c){return std::tolower(c); });

    stack<card> *startDeck;
    stack<card> *destDeck;
    // TODO:: UPDATE SCORING FUNCTIONALITY
    int scoreInc = 0;


    char* firstChar = &startString[0];
    
    // parse for start deck
    switch (*firstChar)
    {
        // first char is f
        case 102:{
            char* secondChar = &startString[1];
            startDeck = &decks[*secondChar - '0' + 2];
            break;
        }

        // first char is t
        case 116:{
            char* secondChar = &startString[1];
            startDeck = &decks[*secondChar - '0' + 10];
            break;
        }
        // first char is s
        case 115:{
            startDeck = &decks[0];
            break;
        }
        // first char is w
        case 119:{
            startDeck = &decks[1];
            break;    
        }
        default: {throw std::out_of_range("Deck not available");};
    }

    firstChar = &destString[0];

    // parse for second deck
    // we can never more a card to the second deck
    switch (*firstChar)
    {
        // first char is f
        case 102:{
            char* secondChar = &destString[1];
            destDeck = &decks[*secondChar - '0' + 2];
            break;}

        // first char is t
        case 116:{
            char* secondChar = &destString[1];
            destDeck = &decks[*secondChar - '0' + 10];
            break;}
        
        // first char is w
        case 119:{
            destDeck = &decks[1];
            break;}  
        
        // first char is s, this will be an invalid move but to better control errors we will pass it anyway
        case 115:{
            destDeck = &decks[0];
            break;
        }
        default: {throw std::out_of_range("Deck not available");};
    }

    if (isValid(*startDeck, *destDeck)){
        destDeck->push(startDeck->pop());
        move* newMove = new move(*startDeck, *destDeck, score);
        gameHistory.push(*newMove);
        updateScore(scoreInc);
        delete newMove;
    }

    else {

        throw std::invalid_argument("\nMove from " + startString + " to " + destString + " is invalid\n");
    }
}

void gamespace::undo()
{
    move undoMove = gameHistory.pop();
    // push the top card from the destination to the start, the reverse of how it was done in the move function
    (undoMove.getSource())->push((undoMove.getDestination())->pop());
    score = undoMove.getScore();
}

std::ostream &operator<<(std::ostream &out, const gamespace game)
{
    // outputs top of box
    out << "+------------------------------------------------------------+\n";

    // outputs score
    out << "|" << std::setw(26) << "Score: " << std::setw(5) << game.score << std::setw(30) << "|";

    // outputs bottom of scoreboard
    out << "\n|------------------------------------------------------------|";
    
    // right justifies stock , allows for empty deck
    out << "\n|" << std::setw(53) << "Stock: ";
    if (!game.decks[0].isEmpty()){
        out << game.decks[0].peek();
    } else{
        out << "[   ]";
    }

    // right justifies waste , allows for empty deck
    out << "  |\n|" << std::setw(53) << "Waste: ";

    if (!game.decks[1].isEmpty()){
        out << game.decks[1].peek();
    } else{
        out << "[   ]";
    }

    // creates a blank line
    out << "  |\n|" << std::setw(65) << "|\n|  ";
    

    // outputs both lines of foundations
    for (int i = 0; i < 4; ++i){
        out << "F" << i << ": ";

        if (!game.decks[i + 2].isEmpty()){
            out << game.decks[i + 2].peek();
        } else{
            out << "[   ]";
        }

        out << "   ";
    }
    out << std::setw(15) << "|\n|  ";

    for (int i = 4; i < 8; ++i){
        out << "F" << i << ": ";

        if (!game.decks[i + 2].isEmpty()){
            out << game.decks[i + 2].peek();
        } else{
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

        if (!game.decks[i + 10].isEmpty()){
            out << game.decks[i + 10].peek();
        } else{
            out << "[   ]";
        }

        out << "  ";
    }
    out << "   |";
    // bottom of box
    out << "\n+------------------------------------------------------------+\n";
    return out;
}