#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "Card.h"
#include "Deck.h"
using namespace std;

// Значение туза, может быть 1 или 11
static int AceGlasses;
// Вектор карт (массив)
vector<Card*> Cards;
// Создание массива карт (Упрощённый)
vector<Card*> Deck::CreateSimplifiedDeck()
{
	vector<Card*> result;
	for (int i = 2; i <= 10; i++)
		for (int m = 0; m < 4; m++)
			result.push_back(new Card('D', i));
	return result;
}
// Создание массива карт (Одна колода)
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
// Создание массива карт (Выдача из N кол-ва колод)
vector<Card*> Deck::CreateMultiDeck(int N)
{
	vector<Card*> result;
	for (int i = 0; i < N; i++)
		AddRange(result, CreatePrimitiveDeck());
	return result;
}
// Метод для тасовки колоды
void Deck::ShuffleDeck()
{
	srand(time(0));
	for (int i = 0; i < Cards.size(); i++)
		swap(Cards[i], Cards[rand() % Cards.size()]);
}
// Метод для добавления массив в массив (используется для совмещения нескольких колод в одну)
void Deck::AddRange(vector<Card*> &source, vector<Card*> cards)
{
	for (int i = 0; i < cards.size(); i++)
		source.push_back(cards[i]);
}
// Устанавливаем начальное значение туза
int Deck::AceGlasses = 1;