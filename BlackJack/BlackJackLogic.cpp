#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Player.h"
#include "BlackJackLogic.h"
#include "Strategy.h"

#include "Easy1Strategy.h"
#include "Easy2Strategy.h"
#include "Easy3Strategy.h"

#include "Hard1Strategy.h"
#include "Hard2Strategy.h"
#include "Hard3Strategy.h"

using namespace std;
int main();
template <typename P>
void DeleteContainer::operator () (P container)
{
	delete container;
}
BlackJackLogic::~BlackJackLogic()
{
	delete player1_strategy;
	delete player2_strategy;
	std::for_each(deck.Cards.begin(), deck.Cards.end(), DeleteContainer());
	deck.Cards.clear();
}
void BlackJackLogic::GetCard(Player &target)
{
	target.deck.Cards.push_back(deck.Cards[deck.Cards.size() - 1]);
	deck.Cards.pop_back();
}
void BlackJackLogic::CompetitionDetailed()
{
	srand(time(NULL));
	char playerChoice, player2Choice, startGame;
	int randNumber;
    std::system("CLS");
	cout << "Select one of the items: \na. Start the game \nx. Exit \n>>";
	cin >> startGame;
	if (startGame != 'a')
		CompetitionDetailed();
	while (true)
	{
		std::system("CLS");
		std::system("CLS");
		playerChoice = player1_strategy->GetStrategyChoice(player1, player2);
		player2Choice = player2_strategy->GetStrategyChoice(player1, player2);
		if (playerChoice == 'b' && player2Choice == 'b')
		{
			std::system("CLS");
			cout << "End of game!\n";
			cout << "Two players took the pass, the winner was: " << (player1.GetCardsSum() > player2.GetCardsSum() ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		if (playerChoice == 'a')
			GetCard(player1);
		if (player2Choice == 'a')
			GetCard(player2);
		cout << "                          Player1           |    Player2\n";
		cout << "\nAct:                    " << (playerChoice == 'a' ? "took the card" : "pass") << "            " << (player2Choice == 'a' ? "took the card" : "pass");
		cout << "\n\nPoints for the current turn:      " << (player1.deck.Cards.size() > 0 ? player1.deck.Cards[player1.deck.Cards.size() - 1]->value : 0) << "                     " << (player2.deck.Cards.size() > 0 ? player2.deck.Cards[player2.deck.Cards.size() - 1]->value : 0);
		cout << "\n\nPoints for the current game:     " << player1.GetCardsSum() << "                     " << player2.GetCardsSum() << endl << "\n\na. Continue\nx. Exit\n>> ";
		char currentChoice;
		cin >> currentChoice;
		if (currentChoice != 'a')
		{
			std::system("CLS");
			cout << "Inncorrect input, game stopped!";
			return;
		}
		if (player1.GetCardsSum() > 21 || player2.GetCardsSum() > 21)
		{
			std::system("CLS");
			cout << "End of game!\n";
			cout << "One of the players scored more than 21, the winner was: " << (player1.GetCardsSum() > 21 ? "player2" : "player1");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		else if (player1.GetCardsSum() == 21 || player2.GetCardsSum() == 21)
		{
			std::system("CLS");
			cout << "End of game!\n";
			cout << "One of the players scored exactly 21 points, the winner was: " << (player1.GetCardsSum() == 21 ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
	}

	std::system("CLS");
}
void BlackJackLogic::CompetitionNotDetailed()
{
	srand(time(NULL));
	char playerChoice, player2Choice, startGame;
	std::system("CLS");
	while (true)
	{
		player2Choice = player1_strategy->GetStrategyChoice(player1, player2);
		playerChoice = player2_strategy->GetStrategyChoice(player1, player2);
		if (playerChoice == 'a')
			GetCard(player1);
		if (player2Choice == 'a')
			GetCard(player2);
		if (playerChoice == 'b' && player2Choice == 'b')
		{
			cout << "End of game!\n";
			cout << "Two players took the pass, the winner was: " << (player1.GetCardsSum() > player2.GetCardsSum() ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		if (player1.GetCardsSum() > 21 || player2.GetCardsSum() > 21)
		{
			cout << "End of game!\n";
			cout << "One of the players scored more than 21, the winner was: " << (player1.GetCardsSum() > 21 ? "player2" : "player1");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		else if (player1.GetCardsSum() == 21 || player2.GetCardsSum() == 21)
		{
			cout << "End of game!\n";
			cout << "One of the players scored exactly 21 points, the winner was: " << (player1.GetCardsSum() == 21 ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
	}
	std::system("CLS");
}
void BlackJackLogic::Tournament()
{
	srand(time(NULL));
	char playerChoice, player2Choice, startGame;
	std::system("CLS");
	while (true)
	{
		player2Choice = player1_strategy->GetStrategyChoice(player1, player2);;
		playerChoice = player1_strategy->GetStrategyChoice(player1, player2);
		if (playerChoice == 'a')
			GetCard(player1);
		if (player2Choice == 'a')
			GetCard(player2);
		if (playerChoice == 'b' && player2Choice == 'b')
		{
			cout << "End of game!\n";
			cout << "Reason: Both players took a pass.\n";
			cout << "Winner is: " << (player1.GetTwoCardsSum() > player2.GetTwoCardsSum() ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		if (player1.GetCardsSum() >= 21 || player2.GetCardsSum() >= 21)
		{
			cout << "End of game!\n";
			cout << "Reason: One of the players has 21 points or more.\n";
			cout << "Winner is: " << (player1.GetTwoCardsSum() > player2.GetTwoCardsSum() ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
	}
	std::system("CLS");
}
void BlackJackLogic::Start()
{
	int N = 1;
	char cardOutputMode = 'x', gameMode = 'x', strategyDifficulty = 'x', strategyChoice = 'x';
	char aceValueChoice;
	cout << "Choose the value of the ace: \na. 1\nb. 11\n>> ";
	cin >> aceValueChoice;
	Deck::AceGlasses = aceValueChoice == 'a' ? 1 : 11;
	system("CLS");
	while (cardOutputMode != 'a' && cardOutputMode != 'b' && cardOutputMode != 'c')
	{
		cout << "Choose the type of game: " << endl;
		cout << "a. Simplified.";
		cout << "\nb. One deck.";
		cout << "\nc. Output from N final decks.\n>> ";
		cin >> cardOutputMode;
		system("CLS");
		if (cardOutputMode == 'c')
		{
			cout << "Enter the number of decks: " << endl;
			cin >> N;
		}
	}
	while (gameMode != 'a' && gameMode != 'b' && gameMode != 'c')
	{
		system("CLS");
		cout << "Select game mode: ";
		cout << "\na. Competition with detail.";
		cout << "\nb. Competition without detail.";
		cout << "\nc. Tournament.\n>> ";
		cin >> gameMode;
	}
	while (strategyDifficulty != 'a' && strategyDifficulty != 'b')
	{
		system("CLS");
		cout << "Select the difficulty of the strategy: ";
		cout << "\na. Trivial.";
		cout << "\nb. Not trivial.\n>> ";
		cin >> strategyDifficulty;
	}
	if (strategyDifficulty == 'a')
	{
		while (strategyChoice != 'a' && strategyChoice != 'b' && strategyChoice != 'c')
		{
			system("CLS");
			cout << "Choose a strategy:";
			cout << "\na. Easy 1.";
			cout << "\nb. Easy 2.";
			cout << "\nc. Easy 3.\n>> ";
			cin >> strategyChoice;
		}
		switch (strategyChoice)
		{
		case 'a':
			player1_strategy = new Easy1Strategy();
			break;
		case 'b':
			player1_strategy = new Easy2Strategy();
			break;
		case 'c':
			player1_strategy = new Easy3Strategy();
			break;
		default:
			break;
		}
	}
	else if (strategyDifficulty == 'b')
	{
		while (strategyChoice != 'a' && strategyChoice != 'b' && strategyChoice != 'c')
		{
			system("CLS");
			cout << "Choose a strategy: ";
			cout << "\na. Hard 1.";
			cout << "\nb. Hard 2.";
			cout << "\nc. Hard meta-strategy.\n>> ";
			cin >> strategyChoice;
		}
		switch (strategyChoice)
		{
		case 'a':
			player1_strategy = new Hard1Strategy();
			break;
		case 'b':
			player1_strategy = new Hard3Strategy();
			break;
		case 'c':
			player1_strategy = new Hard2Strategy();
			break;
		default:
			break;
		}
	}
	switch (cardOutputMode)
	{
	case 'a':
		deck.Cards = Deck::CreateSimplifiedDeck();
		break;
	case 'b':
		deck.Cards = Deck::CreatePrimitiveDeck();
		break;
	case 'c':
		deck.Cards = Deck::CreateMultiDeck(N);
		break;
	}
	deck.ShuffleDeck();

	int randNumber = rand() % 13;
	if (randNumber <= 2)
		player2_strategy = new Easy1Strategy();
	else if (randNumber > 2 && randNumber <= 4)
		player2_strategy = new Easy2Strategy();
	else if (randNumber > 4 && randNumber <= 6)
		player2_strategy = new Easy3Strategy();
	else if (randNumber > 6 && randNumber <= 8)
		player2_strategy = new Hard1Strategy();
	else if (randNumber > 8 && randNumber <= 10)
		player2_strategy = new Hard2Strategy();
	else if (randNumber > 10)
		player2_strategy = new Hard3Strategy();

	if (gameMode == 'a')
		CompetitionDetailed();
	else if (gameMode == 'b')
		CompetitionNotDetailed();
	else if (gameMode == 'c')
		Tournament();

}