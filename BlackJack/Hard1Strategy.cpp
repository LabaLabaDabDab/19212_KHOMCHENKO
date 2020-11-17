#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Hard1Strategy.h"
#include "FileStream.cpp"
#include "ISerializable.h"

using namespace std;

Hard1Strategy::Hard1Strategy()
{
	Load("hard1Strategy");
}
char Hard1Strategy::GetStrategyChoice(Player player, Player opponent)
{
	if (player.GetCardsSum() <= firstScore)
		return 'a';
	else if (player.GetCardsSum() > firstScore && player.GetCardsSum() <= secondScore)
		return 'b';
	else if (player.GetCardsSum() > secondScore)
		return 'a';
}
string Hard1Strategy::SerializeObject()
{
	// Пакуем наши параметры в сплошную строчку,
	// разделяя параметр и знаки для того чтобы потом можно было десериализировать строку
	return to_string(firstScore) + "&" + to_string(secondScore) + "&";
}
void Hard1Strategy::DeserializeObject(string serializeInfo)
{
	// Создаем указатель на массив из чаров,
	// и пихаем в него преобразованую в чаровый массив строку и указываем знак, 
	// по которому будут распределятся сериализированные параметры
	char* temp = strtok(const_cast <char*> (serializeInfo.c_str()), "&");
	// Парсим всё это дело в число
	firstScore = stod(temp);
	// Опять сплитим
	temp = strtok(NULL, " ,.-");
	// Опять парсим
	secondScore = stod(temp);
}