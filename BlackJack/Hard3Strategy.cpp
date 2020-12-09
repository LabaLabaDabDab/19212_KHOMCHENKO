#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include "Hard3Strategy.h"
#include "FileStream.cpp"
#include "ISerializable.h"

using namespace std;

Hard3Strategy::Hard3Strategy()
{
	Load("hard3Strategy");
}
char Hard3Strategy::GetStrategyChoice(Player player, Player opponent)
{
	if (player.GetCardsSum() <= score)
		return 'a';
	else if (player.GetCardsSum() > score)
		return 'b';
}
string Hard3Strategy::SerializeObject()
{
	// Пакуем нашие параметры в сплошную строчку,
	// разделяя параметри знаки для того чтобы потом можно было десериализировать строку
	return to_string(score) + "&";
}
void Hard3Strategy::DeserializeObject(string serializeInfo)
{
	// Создаем указатель на массив из чаров,
	// и пихаем в него преобразованую в чаровый массив строку и указываем знак, 
	// по которому будут распределятся сериализированные параметры
	istringstream iss(serializeInfo);
	std::string token;
	getline(iss, token, '&');
	score = stod(token);
}