#ifndef MAIN_CPP_SIMPLEDDESK_H
#define MAIN_CPP_SIMPLEDDESK_H

#include<iostream>
#include<vector>
#include<ctime>
#include <cstdlib>

class simpled_deck {
public:
    std::vector <int> deck;
    void init_deck();
    void shuffler();
    void print_deck();
    int  getCard();
    bool is_deck_empty();
};

#endif //MAIN_CPP_SIMPLEDDESK_H
