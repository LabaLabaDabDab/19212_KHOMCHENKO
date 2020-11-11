#include "N_deck.h"

void n_deck::init_deck(int N) {
    int Ace = 1;
    int J = 10;
    int Q = 10;
    int K = 10;
    n_deck = { Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
             Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
             Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
             Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K };
    std::vector <int> new_deck = n_deck;
    for (int i = 0; i < N; ++i) {
        n_deck.insert(n_deck.end(), new_deck.begin(), new_deck.end());
    }
}

void n_deck::shuffler() {
    srand(time(NULL));
    int length = n_deck.size();
    for (int i = 0; i < length; i++)
        std::swap(n_deck[i], n_deck[rand() % length]);
    std::cout << "Deck Shuffled!" << std::endl;
}

void n_deck::print_deck() {
    std::cout << "deck:" << std::endl;
    int t = 0;
    for (auto i : n_deck) {
        std::cout << i << " ,";
        t++;
        if (t % 13 == 0) std::cout << std::endl;
    }
}

int n_deck::getCard() {
    int card = n_deck.front();
    n_deck.erase(n_deck.begin());
    return card;
}

bool n_deck::is_deck_empty() {
    return n_deck.empty();
}