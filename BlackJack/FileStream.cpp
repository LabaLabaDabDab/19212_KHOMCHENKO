#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "ISerializable.h"
using namespace std;
// Наследуемся от класса сериализации
class FileStream : public ISerializable
{
    public:
	// Метод для создания конфигурационного файла по его имени
	// Он не используется но пусть будет на всякий пожарный
	void Write(string fileName)
	{
		const string filePath = "configs/" + fileName + ".cfg";
		ofstream ofFileStream(filePath);
		ofFileStream << SerializeObject();
		ofFileStream.close();
	}
	// Метод для подгрузки конфигурационного файла по его имени
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