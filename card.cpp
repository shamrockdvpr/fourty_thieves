#include "card.h"

// initializes a card with a number and suit. NOTE: these are constant variables
card::card(int number, int suit) : number(number), suit(static_cast<Suit>(suit)){}

const int card::getNumber() const
{
    return this->number;
}

const std::string card::getSuit() const
{
    switch (this->suit)
    {
        case 1:return "\u2660";
        case 2:return "\u2665";
        case 3:return "\u2666";
        case 4:return "\u2663";
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
    out << "\n+---+\n";
    out << "|" << cardOut.getSuit() << "  |\n";
    out << "|   |\n";
    out << "|  " << cardOut.number << "|\n";
    out << "+---+\n";
}
