#pragma once
#include<iostream>

using namespace std;
// ������ ����� �� ������
class Card
{
public:
	// �������� ����� (����� � ���������� �� 10, � �.�)
	int value;
	// ��� �����, ������������ ��� ����������� ���� � ���������
	char type;

	Card(int value);
	Card(char type, int value);
};