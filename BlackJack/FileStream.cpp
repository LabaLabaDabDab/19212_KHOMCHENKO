#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "ISerializable.h"
using namespace std;
// ����������� �� ������ ������������
class FileStream : public ISerializable
{
    public:
	// ����� ��� �������� ����������������� ����� �� ��� �����
	// �� �� ������������ �� ����� ����� �� ������ ��������
	void Write(string fileName)
	{
		const string filePath = "configs/" + fileName + ".cfg";
		ofstream ofFileStream(filePath);
		ofFileStream << SerializeObject();
		ofFileStream.close();
	}
	// ����� ��� ��������� ����������������� ����� �� ��� �����
	void Load(string fileName)
	{
		const string filePath = "configs/" + fileName + ".cfg";
		ifstream ifFileStream(filePath);
		string serializeInfo;
		ifFileStream >> serializeInfo;
		DeserializeObject(serializeInfo);
		ifFileStream.close();
	}
};