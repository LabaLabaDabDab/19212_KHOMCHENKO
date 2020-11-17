#ifndef UNTITLED7_PLAYER_H
#define UNTITLED7_PLAYER_H

#pragma once
#include<iostream>
#include "Deck.h"
using namespace std;
class Player{
public:
    // Колода карт игрока
    Deck deck;
    Player() { }
    Player(Deck deck) { this->deck = deck; }

    // Метод для суммирования всех очков карт из колоды
    int GetCardsSum(){
        int result = 0;
        for (int i = 0; i < deck.Cards.size(); i++)
            result += deck.Cards[i]->value;
        return result;
    }
};

#endif //UNTITLED7_PLAYER_H
