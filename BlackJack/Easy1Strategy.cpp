#pragma once
#include <iostream>
#include "Easy1Strategy.h"

using namespace std;

char Easy1Strategy::GetStrategyChoice(Player player, Player opponent)
{
	if (player.GetCardsSum() >= 17)
		return 'b';
	else return 'a';
}