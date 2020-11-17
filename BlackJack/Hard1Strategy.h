#pragma once
#include <iostream>
#include "Strategy.h"
#include "Player.h"
#include "ISerializable.h"
#include "FileStream.cpp"

using namespace std;

// Наследуем базовый класс стратегии а также класс подгрузки параметров из конфигурационного файла
class Hard1Strategy : public Strategy, public FileStream
{
	int firstScore, secondScore;
    public:
	// Коструктор без параметров
    // Hужен чтобы при создании экзмпляра объекта -
    // загружался конфигурацмонный файл с параметрами стратегии
	Hard1Strategy();
	// Переопределённая функция выбора стратегии из класса Strategy.
	// То есть в любом случае функция будет возвращать выбор,
	// но то от чего будет зависит выбор, реализуется в самом методе.
	char GetStrategyChoice(Player player, Player opponent);
	// Метод из интерфейса ISerializable для сериализации объекта в строковый вид
	// И дальнейшей записи в файл
	string SerializeObject();
	// Метод из интерфейса ISerializable для десериализации объекта
	void DeserializeObject(string serializeInfo);
};