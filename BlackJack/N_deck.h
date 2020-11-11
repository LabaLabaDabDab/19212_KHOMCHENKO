#ifndef BLACKJACK_N_DECK_H
#define BLACKJACK_N_DECK_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

class n_deck {
    std::vector <int> n_deck;
    void init_deck(int N);
    void shuffler();
    void print_deck();
    int  getCard();
    bool is_deck_empty();
};

#endif //BLACKJACK_N_DECK_H