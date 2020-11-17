#pragma once
#include <iostream>
#include "Strategy.h"
#include "Player.h"

using namespace std;

class Easy3Strategy : public Strategy
{
    public:
	// ��������������� ������� ������ ��������� �� ������ Strategy.
	// �� ���� � ����� ������ ������� ����� ���������� �����,
	// �� �� �� ���� ����� ������� �����, ����������� � ����� ������.
	char GetStrategyChoice(Player player, Player opponent);
};