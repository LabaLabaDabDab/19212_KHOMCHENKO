#include "SimpledDesk.h"

void simpled_deck::init_deck() {
    deck = {1,2,3,4,5,6,7,8,9,10};
}

void simpled_deck::shuffler() {
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
        std::swap(deck[i], deck[rand() % 10]);
    std::cout << std::endl;
    std::cout << "Deck Shuffled!" << std::endl;
}

void simpled_deck::print_deck() {
    std::cout << "deck:" << std::endl;
    for (auto i : deck) {
        std::cout << i << ", ";
    }
}

int simpled_deck::getCard() {
    int card = deck.front();
    return card;
}

bool simpled_deck::is_deck_empty() {
    return deck.empty();
}