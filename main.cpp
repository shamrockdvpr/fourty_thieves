#include "card.h"
#include <iostream>

/*
    Note on suits:
        Spades = 1
        HEART = 2
        DIAMOND = 3
        CLUB = 4
*/

int main(){
    card aceOfSpaces(1, 1);
    card fiveOfHearts(5, 2);
    card tenOfDiamonds(10, 3);

    std::cout << aceOfSpaces.getNumber() << std::endl;
    std::cout << (fiveOfHearts > aceOfSpaces) << std::endl;
    std::cout << (fiveOfHearts < aceOfSpaces) << std::endl;
    std::cout << (fiveOfHearts >= aceOfSpaces) << std::endl;
    std::cout << (fiveOfHearts <= aceOfSpaces) << std::endl;
    std::cout << (fiveOfHearts == aceOfSpaces) << std::endl;
    std::cout << (fiveOfHearts != aceOfSpaces) << std::endl;
    std::cout << aceOfSpaces;
    std::cout << fiveOfHearts;
    std::cout << tenOfDiamonds;

}