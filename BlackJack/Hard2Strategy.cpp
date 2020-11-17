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
	// ������ ���� ��������� � �������� �������,
	// �������� �������� � ����� ��� ���� ����� ����� ����� ���� ����������������� ������
	return to_string(firstScore) + "&" + to_string(secondScore) + "&";
}
void Hard2Strategy::DeserializeObject(string serializeInfo)
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