#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
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
	// Пакуем нашие параметры в сплошную строчку,
	// разделяя параметри знаки для того чтобы потом можно было десериализировать строку
	return to_string(firstScore) + "&" + to_string(secondScore) + "&";
}
void Hard1Strategy::DeserializeObject(string serializeInfo)
{
	// Создаем указатель на массив из чаров,
	// и пихаем в него преобразованую в чаровый массив строку и указываем знак, 
	// по которому будут распределятся сериализированные параметры

	istringstream iss(serializeInfo);
	std::string token;
	getline(iss, token, '&');
	firstScore = stod(token);
	getline(iss, token, '&');
	secondScore = stod(token);
}