#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Hard2Strategy.h"
#include "Easy1Strategy.h"
#include "Easy2Strategy.h"
#include "FileStream.cpp"
#include "ISerializable.h"

using namespace std;

Hard2Strategy::Hard2Strategy()
{
	Load("hard2Strategy");
}
char Hard2Strategy::GetStrategyChoice(Player player, Player opponent)
{
	Strategy* easy1 = new Easy1Strategy();
	Strategy* easy2 = new Easy2Strategy();
	if (player.GetCardsSum() <= firstScore)
		return 'a';
	else if (player.GetCardsSum() > firstScore && player.GetCardsSum() <= secondScore)
		return easy2->GetStrategyChoice(player, opponent);
	else if (player.GetCardsSum() > secondScore)
		return easy1->GetStrategyChoice(player, opponent);
}
string Hard2Strategy::SerializeObject()
{
	// Пакуем наши параметры в сплошную строчку,
	// разделяя параметр и знаки для того чтобы потом можно было десериализировать строку
	return to_string(firstScore) + "&" + to_string(secondScore) + "&";
}
void Hard2Strategy::DeserializeObject(string serializeInfo)
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