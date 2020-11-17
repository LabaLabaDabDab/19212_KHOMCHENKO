#pragma once
#include <iostream>
#include "Strategy.h"
#include "Player.h"

using namespace std;

class Easy2Strategy : public Strategy
{
    public:
	// Переопределённая функция выбора стратегии из класса Strategy.
	// То есть в любом случае функция будет возвращать выбор,
	// но то от чего будет зависит выбор, реализуется в самом методе.
	char GetStrategyChoice(Player player, Player opponent);
};