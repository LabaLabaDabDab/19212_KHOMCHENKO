#pragma once
#include <iostream>
#include "Easy3Strategy.h"

using namespace std;

char Easy3Strategy::GetStrategyChoice(Player player, Player opponent)
{
	if (opponent.deck.Cards.size() > 1 && (opponent.deck.Cards[0]->value + opponent.deck.Cards[1]->value) >= 8)
		return 'b';
	else return 'a';
}