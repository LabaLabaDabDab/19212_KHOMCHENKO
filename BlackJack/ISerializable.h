#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class ISerializable
{
    public:
	// Метод из интерфейса ISerializable для сериализации объекта в строковый вид
    // И дальнейшей записи в файл
	virtual string SerializeObject() = 0;
	// Метод из интерфейса ISerializable для десериализации объекта
	virtual void DeserializeObject(string serializeInfo) = 0;
};