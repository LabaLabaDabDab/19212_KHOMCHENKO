#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class ISerializable
{
    public:
	// ����� �� ���������� ISerializable ��� ������������ ������� � ��������� ���
    // � ���������� ������ � ����
	virtual string SerializeObject() = 0;
	// ����� �� ���������� ISerializable ��� �������������� �������
	virtual void DeserializeObject(string serializeInfo) = 0;
};