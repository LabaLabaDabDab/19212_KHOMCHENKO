#pragma once
#include<iostream>
#include "Deck.h"
using namespace std;
class Player
{
    public:
	// ������ ���� ������
	Deck deck;
	Player();
	Player(Deck deck);

	// ����� ��� ������������ ���� ����� ���� �� ������
	int GetCardsSum();
	int GetTwoCardsSum();
};