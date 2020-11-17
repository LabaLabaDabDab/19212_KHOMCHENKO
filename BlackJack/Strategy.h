#pragma once
#include "Player.h"
class Strategy
{
    public:
	// Чисто виртуальный метод, который переопределяет поведение стратегии
	virtual char GetStrategyChoice(Player player, Player opponent) { return 'x'; }
};