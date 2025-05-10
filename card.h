#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>
#include <iomanip>

enum Suit{
    SPADE=0,
    HEART,
    DIAMOND,
    CLUB
};

class card{
public:
    card(int, int);
    const int getNumber() const;
    const std::string getPrintableNum() const;
    const std::string getSuit() const;
    const Suit getEnumSuit() const;

    bool operator<(const card&) const;
    bool operator>(const card&) const;
    bool operator<=(const card&) const;
    bool operator>=(const card&) const;
    bool operator==(const card&) const;
    bool operator!=(const card&) const;

    friend std::ostream& operator<<(std::ostream&, const card&);


private:
    const int number;
    const Suit suit;
};

#endif
