#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "Card.h"
using namespace std;

class Deck
{
    public:
	// Значение туза, может быть 1 или 11
	static int AceGlasses;
	// Вектор карт (массив)
	vector<Card*> Cards;
	// Создание массива карт (Упрощённый)
	static vector<Card*> CreateSimplifiedDeck();
	// Создание массива карт (Одна колода)
	static vector<Card*> CreatePrimitiveDeck();
	// Создание массива карт (Выдача из N кол-ва колод)
	static vector<Card*> CreateMultiDeck(int N);
	// Метод для тасовки колоды
	void ShuffleDeck();
	// Метод для добавления массив в массив (используется для совмещения нескольких колод в одну)
	static void AddRange(vector<Card*> &source, vector<Card*> cards);
};