#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>
#include <iomanip>

enum Suit{
    SPADE=1,
    HEART,
    DIAMOND,
    CLUB
};

class card{
public:
    card(int, int);
    const int getNumber() const;
    const std::string getSuit() const;

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
