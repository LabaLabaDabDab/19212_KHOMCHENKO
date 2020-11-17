#pragma once
#include<iostream>
#include "Deck.h"
#include "Player.h"
using namespace std;

Player::Player () { }
Player::Player(Deck deck)
{
	this->deck = deck; 
}
int Player::GetCardsSum()
{
	int result = 0;
	for (int i = 0; i < deck.Cards.size(); i++)
		result += deck.Cards[i]->value;
	return result;
}
int Player::GetTwoCardsSum()
{
	int result = 0;
	for (int i = 0; i < deck.Cards.size(); i++)
		if (deck.Cards[i]->value == 2)
			result += deck.Cards[i]->value;
	return result;
}