#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Player.h"
#include "Strategy.h"

using namespace std;
int main();
struct DeleteContainer
{
	template <typename P>
	void operator () (P container);
};
class BlackJackLogic
{
private:
	//  Колода карт, которая будет в дальнейшем заполена картами в зависимости от выбраного режима.
	Deck deck;
	// Игроки
	Player player1, player2;
	// Стратегии игроков
	Strategy* player1_strategy;
	Strategy* player2_strategy;
	//  Коструктор, который наполняет колоду картами и тасует
	// Принимает 3 аргумента
	// 1. Режим выдачи карт
	// 2. Кол-во сменшаных колод
	// 3. «начение туза (в блэкджеке при начале игры игроки решают, сколько очков будет туз)
    public:
	// Метод для получения карты, который принимает в аргументах игрока, которому будет выдана карта
	void GetCard(Player &target);
	// Симуляция a.
	void CompetitionDetailed();
	// Симуляция b.
	void CompetitionNotDetailed();
	// Симуляция c.
	void Tournament();
	// Метод для начала игры
	void Start();

	~BlackJackLogic();
};