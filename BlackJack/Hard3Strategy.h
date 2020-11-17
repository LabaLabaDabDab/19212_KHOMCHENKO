#pragma once
#include <iostream>
#include "Strategy.h"
#include "Player.h"
#include "ISerializable.h"
#include "FileStream.cpp"

using namespace std;

// ��������� ������� ����� ��������� � ����� ����� ��������� ���������� �� ����������������� �����
class Hard3Strategy : public Strategy, public FileStream
{
	int score;
public:
	// ���������� ��� ����������
	// H���� ����� ��� �������� ��������� ������� -
	// ���������� ���������������� ���� � ����������� ���������
	Hard3Strategy();
	// ��������������� ������� ������ ��������� �� ������ Strategy.
	// �� ���� � ����� ������ ������� ����� ���������� �����,
	// �� �� �� ���� ����� ������� �����, ����������� � ����� ������.
	char GetStrategyChoice(Player player, Player opponent);
	// ����� �� ���������� ISerializable ��� ������������ ������� � ��������� ���
	// � ���������� ������ � ����
	string SerializeObject();
	// ����� �� ���������� ISerializable ��� �������������� �������
	void DeserializeObject(string serializeInfo);
};