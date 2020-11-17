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
class BlackJackLogic
{
private:
	//  Колода карт, которая будет в дальнейшем заполена картами в зависимости от выбранного режима.
	Deck deck;
	// Игроки
	Player user, dealer;
	//  Коструктор, который наполняет колоду картами и тасует
	// Принимает 3 аргумента
	// 1. Режим выдачи карт
	// 2. Кол-во сменшаных колод
	// 3. значение туза (в блэкджеке при начале игры игроки решают, сколько очков будет туз)
    public:
	BlackJackLogic(char outputCardMode, int N, int aceGlasses = 1);
	// Метод для получения карты, который принимает в аргументах игрока, которому будет выдана карта
	void GetCard(Player &target);
	// Симуляция a.
	void CompetitionDetailed(Player player1, Player player2, Strategy* player1Strategy, Strategy* player2Strategy);
	// Симуляция b.
	void CompetitionNotDetailed(Player player1, Player player2, Strategy* player1Strategy, Strategy* player2Strategy);
	// Симуляция c.
	void Tournament(Player player1, Player player2, Strategy* player1Strategy, Strategy* player2Strategy);
	// Метод для начала игры
	void Start(char gameMode, Strategy* strategy);
};