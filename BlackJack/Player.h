#pragma once
#include<iostream>
#include "Deck.h"
using namespace std;
class Player
{
    public:
	// Колода карт игрока
	Deck deck;
	Player();
	Player(Deck deck);

	// Метод для суммирования всех очков карт из колоды
	int GetCardsSum();
	int GetTwoCardsSum();
};