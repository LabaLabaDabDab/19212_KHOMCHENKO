#include "deck.h"

int Ace = 1;
int J = 10;
int Q = 10;
int K = 10;

void deck::init_deck() {
    deck = { Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
             Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
             Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
             Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K };
}

void deck::shuffler() {
    srand(time(NULL));
    int length = deck.size();
    for (int i = 0; i < length; i++)
        std::swap(deck[i], deck[rand() % length]);
    std::cout << "******Deck Shuffled!******" << std::endl;
}

void deck::print_deck() {
    std::cout << "deck:" << std::endl;
    int t = 0;
    for (auto i : deck) {
        std::cout << i << " ,";
        t++;
        if (t % 13 == 0) std::cout << std::endl;
    }
}

int deck::getCard() {
    int card = deck.front();
    deck.erase(deck.begin());
    return card;
}

bool deck::is_deck_empty() {
    return deck.empty();
}