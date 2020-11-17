#pragma once
#include <iostream>
#include "Strategy.h"
#include "Player.h"
#include "ISerializable.h"
#include "FileStream.cpp"

using namespace std;

// ��������� ������� ����� ��������� � ����� ����� ��������� ���������� �� ����������������� �����
class Hard1Strategy : public Strategy, public FileStream
{
	int firstScore, secondScore;
    public:
	// ���������� ��� ����������
    // H���� ����� ��� �������� ��������� ������� -
    // ���������� ���������������� ���� � ����������� ���������
	Hard1Strategy();
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