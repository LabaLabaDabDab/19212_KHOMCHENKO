#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "Card.h"
using namespace std;

class Deck
{
    public:
	// �������� ����, ����� ���� 1 ��� 11
	static int AceGlasses;
	// ������ ���� (������)
	vector<Card*> Cards;
	// �������� ������� ���� (����������)
	static vector<Card*> CreateSimplifiedDeck();
	// �������� ������� ���� (���� ������)
	static vector<Card*> CreatePrimitiveDeck();
	// �������� ������� ���� (������ �� N ���-�� �����)
	static vector<Card*> CreateMultiDeck(int N);
	// ����� ��� ������� ������
	void ShuffleDeck();
	// ����� ��� ���������� ������ � ������ (������������ ��� ���������� ���������� ����� � ����)
	static void AddRange(vector<Card*> &source, vector<Card*> cards);
};