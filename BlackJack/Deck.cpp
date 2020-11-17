#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "Card.h"
#include "Deck.h"
using namespace std;

// �������� ����, ����� ���� 1 ��� 11
static int AceGlasses;
// ������ ���� (������)
vector<Card*> Cards;
// �������� ������� ���� (����������)
vector<Card*> Deck::CreateSimplifiedDeck()
{
	vector<Card*> result;
	for (int i = 2; i <= 10; i++)
		for (int m = 0; m < 4; m++)
			result.push_back(new Card('D', i));
	return result;
}
// �������� ������� ���� (���� ������)
vector<Card*> Deck::CreatePrimitiveDeck()
{
	vector<Card*> result;
	vector<char> specialCards{ 'T', 'K', 'L', 'J', '\0' };
	for (int j = 0; j < specialCards.size(); j++)
		for (int m = 0; m < 4; m++)
			result.push_back(new Card(specialCards[j], specialCards[j] == 'T' ? AceGlasses : 10));
	for (int i = 2; i <= 10; i++)
		for (int m = 0; m < 4; m++)
			result.push_back(new Card('D', i));
	return result;
}
// �������� ������� ���� (������ �� N ���-�� �����)
vector<Card*> Deck::CreateMultiDeck(int N)
{
	vector<Card*> result;
	for (int i = 0; i < N; i++)
		AddRange(result, CreatePrimitiveDeck());
	return result;
}
// ����� ��� ������� ������
void Deck::ShuffleDeck()
{
	srand(time(0));
	for (int i = 0; i < Cards.size(); i++)
		swap(Cards[i], Cards[rand() % Cards.size()]);
}
// ����� ��� ���������� ������ � ������ (������������ ��� ���������� ���������� ����� � ����)
void Deck::AddRange(vector<Card*> &source, vector<Card*> cards)
{
	for (int i = 0; i < cards.size(); i++)
		source.push_back(cards[i]);
}
// ������������� ��������� �������� ����
int Deck::AceGlasses = 1;