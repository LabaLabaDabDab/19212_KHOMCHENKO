#pragma once
#include<iostream>

using namespace std;
//  Класс карты из колоды
class Card
{
public:
	// Значение карты (карты с картинками по 10, и т.д)
	int value;
	// Тип карты, используется для обозначения карт с картинкой
	char type;

	Card(int value);
	Card(char type, int value);
};