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
	// ������ ���� ��������� � �������� �������,
	// �������� �������� � ����� ��� ���� ����� ����� ����� ���� ����������������� ������
	return to_string(firstScore) + "&" + to_string(secondScore) + "&";
}
void Hard1Strategy::DeserializeObject(string serializeInfo)
{
	// ������� ��������� �� ������ �� �����,
	// � ������ � ���� �������������� � ������� ������ ������ � ��������� ����, 
	// �� �������� ����� ������������� ����������������� ���������
	char* temp = strtok(const_cast <char*> (serializeInfo.c_str()), "&");
	// ������ �� ��� ���� � �����
	firstScore = stod(temp);
	// ����� �������
	temp = strtok(NULL, " ,.-");
	// ����� ������
	secondScore = stod(temp);
}