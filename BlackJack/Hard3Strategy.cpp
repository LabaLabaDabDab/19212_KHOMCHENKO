#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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
	// ������ ���� ��������� � �������� �������,
	// �������� �������� � ����� ��� ���� ����� ����� ����� ���� ����������������� ������
	return to_string(score) + "&";
}
void Hard3Strategy::DeserializeObject(string serializeInfo)
{
	// ������� ��������� �� ������ �� �����,
	// � ������ � ���� �������������� � ������� ������ ������ � ��������� ����, 
	// �� �������� ����� ������������� ����������������� ���������
	char* temp = strtok(const_cast <char*> (serializeInfo.c_str()), "&");

	// ������ �� ��� ���� � �����
	score = stod(temp);
}