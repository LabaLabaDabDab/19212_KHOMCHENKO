#include <iostream>
#include "game.h"

int main(){
    std::cout << "Hi, what type of game would you prefer?" << std::endl;
    std::cout << "1. Simplified: card issuance is a random number from 1 to 10" << std::endl;
    std::cout << "2. One deck: a card is issued from the final shuffled deck" << std::endl;
    std::cout << "3. With N number of decks" << std::endl;
    int set;
    std::cin >> set;
    switch (set) {
        case 1:
            start1();
            break;
        case 2:
            break;
        case 3:
            int N;
            std::cout << "Enter the number of decks" << std::endl;
            std::cin >> N;

            break;
    };

    return 0;
}