#include "card.h"

// initializes a card with a number and suit. NOTE: these are constant variables
card::card(int number, int suit) : number(number), suit(static_cast<Suit>(suit)){}

const std::string card::getPrintableNum() const
{
    switch (number)
    {
        case 13: return "K";  
        case 12: return "Q";
        case 11: return "J";
        case 1: return "A";
        default: return std::to_string(number);
    }
}

const int card::getNumber() const{
    return number;
}

const std::string card::getSuit() const
{
    switch (this->suit)
    {
        case 0:return "\u2660";
        case 1:return "\u2665";
        case 2:return "\u2666";
        case 3:return "\u2663";
        default:return "ERR";
    }
}

bool card::operator<(const card &otherCard) const
{
    return this->number < otherCard.number;
}

bool card::operator>(const card &otherCard) const
{
    return this->number > otherCard.number;
}

bool card::operator<=(const card &otherCard) const
{
    return this->number <= otherCard.number;
}

bool card::operator>=(const card &otherCard) const
{
    return this->number >= otherCard.number;
}

bool card::operator==(const card &otherCard) const
{
    return this->number == otherCard.number;
}

bool card::operator!=(const card &otherCard) const
{
    return !(*this == otherCard);
}

std::ostream &operator<<(std::ostream &out, const card &cardOut)
{
    // out << "\n+----+\n";
    // out << "|" << cardOut.getSuit() << "   |\n";
    // out << "|    |\n";

    // switch (cardOut.number)
    // {
    //     case 13:{
    //         out << "|  " << std::setw(2) << "K" << "|\n";
    //         break;
    //     }    
    //     case 12:{
    //         out << "|  " << std::setw(2) << "Q" << "|\n";
    //         break;
    //     }
    //     case 11:{
    //         out << "|  " << std::setw(2) << "J" << "|\n";
    //         break;
    //     }
    //     case 1:{
    //         out << "|  " << std::setw(2) << "A" << "|\n";
    //         break;
    //     }
    //     default:{
    //         out << "|  " << std::setw(2) << cardOut.number << "|\n";
    //         break;
    //     }
    // }

    
    // out << "+----+\n";
    out << "[" << cardOut.getSuit() << std::setw(2) << cardOut.getPrintableNum() << "]";
    return out;
}
