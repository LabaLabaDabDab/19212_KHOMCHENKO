#pragma once
#include "Player.h"
class Strategy
{
    public:
	// ����� ����������� �����, ������� �������������� ��������� ���������
	virtual char GetStrategyChoice(Player player, Player opponent) { return 'x'; }
};