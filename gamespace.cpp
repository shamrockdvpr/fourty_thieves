#include "gamespace.h"

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

bool gamespace::isValid(stack<card> &, stack<card> &)
{
    return true;
}

void gamespace::moveCards(std::string startString, std::string destString)
{
    // determine if move is valid
    // calculate change in score
    // create new move obj
    // add to move list
    // increm score

    // make both strings lower case for easier processing
    std::transform(startString.begin(), startString.end(), startString.begin(), 
                    [](unsigned char c){return std::tolower(c); });
    std::transform(destString.begin(), destString.end(), destString.begin(), 
                    [](unsigned char c){return std::tolower(c); });

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
            startDeck = &foundations[*secondChar - '0'];
            break;
        }

        // first char is t
        case 116:{
            char* secondChar = &startString[1];
            startDeck = &tableaus[*secondChar - '0'];
            break;
        }
        // first char is s
        case 115:{
            startDeck = &stock;
            break;
        }
        // first char is w
        case 119:{
            startDeck = &waste;
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
            destDeck = &foundations[*secondChar - '0'];
            break;}

        // first char is t
        case 116:{
            char* secondChar = &destString[1];
            destDeck = &tableaus[*secondChar - '0'];
            break;}
        
        // first char is w
        case 119:{
            destDeck = &waste;
            break;}  

        default: {throw std::out_of_range("Deck not available");};
    }

    if (isValid(*startDeck, *destDeck)){
        destDeck->push(startDeck->pop());
        move* newMove = new move(*startDeck, *destDeck, score);
        gameHistory.insert(*newMove);
        updateScore(scoreInc);
        delete newMove;
    }

    else throw std::invalid_argument("Move Invalid");
}

void gamespace::undo()
{
    currentMove = gameHistory.end();
    move undoMove = *currentMove;
    gameHistory.deleteItem(currentMove);

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