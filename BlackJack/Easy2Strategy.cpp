#pragma once
#include <iostream>
#include "Easy2Strategy.h"

using namespace std;

char Easy2Strategy::GetStrategyChoice(Player player, Player opponent)
{
	if (opponent.deck.Cards.size() > 0 && opponent.deck.Cards[opponent.deck.Cards.size() - 1]->value >= 9)
		return 'b';
	else return 'a';
}