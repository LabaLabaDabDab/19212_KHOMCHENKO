#ifndef MAIN_CPP_DECK_H
#define MAIN_CPP_DECK_H

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>

class deck {
    std::vector <int> deck;
    void init_deck();
    void shuffler();
    void print_deck();
    int  getCard();
    bool is_deck_empty();
};

#endif //MAIN_CPP_DECK_H
