#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
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
	char result;
	if (player.GetCardsSum() <= firstScore)
		result = 'a';
	else if (player.GetCardsSum() > firstScore && player.GetCardsSum() <= secondScore)
		result = easy2->GetStrategyChoice(player, opponent);
	else if (player.GetCardsSum() > secondScore)
		result = easy1->GetStrategyChoice(player, opponent);
	return result;
}
string Hard2Strategy::SerializeObject()
{
	// Пакуем нашие параметры в сплошную строчку,
	// разделяя параметри знаки для того чтобы потом можно было десериализировать строку
	return to_string(firstScore) + "&" + to_string(secondScore) + "&";
}
void Hard2Strategy::DeserializeObject(string serializeInfo)
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