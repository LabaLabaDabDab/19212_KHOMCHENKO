#include <iostream>
#include "game.h"
#include "SimpledDesk.h"
#include <string>

simpled_deck deck;

void start1() {
    deck.init_deck();
    deck.print_deck();
    deck.shuffler();
    deck.print_deck();
}

