/*
/* Program name: card.cpp
* Author: Charlie Shaneck
* Date last updated: 5/10/2025
* Purpose: Define functionality of a card object in the game
*/ 

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

const Suit card::getEnumSuit() const
{
    return suit;
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
    out << "[" << cardOut.getSuit() << std::setw(2) << cardOut.getPrintableNum() << "]";
    return out;
}
