#pragma once
#include <iostream>
#include <vector>
#include <fstream>
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

BlackJackLogic::BlackJackLogic(char outputCardMode, int N, int aceGlasses)
{
	switch (outputCardMode)
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
}
void BlackJackLogic::GetCard(Player &target)
{
	target.deck.Cards.push_back(deck.Cards[deck.Cards.size() - 1]);
	deck.Cards.pop_back();
}
void BlackJackLogic::CompetitionDetailed(Player player1, Player player2, Strategy* player1Strategy, Strategy* player2Strategy)
{
	srand(time(NULL));
	char playerChoice, player2Choice, startGame;
	int randNumber;
    std::system("CLS");
	cout << "Select one of the items: \na. Start the game \nx. Exit \n>>";
	cin >> startGame;
	if (startGame != 'a')
		CompetitionDetailed(player1, player2, player1Strategy, player2Strategy);
	while (true)
	{
		std::system("CLS");
		std::system("CLS");
		playerChoice = player1Strategy->GetStrategyChoice(player1, player2);
		player2Choice = player2Strategy->GetStrategyChoice(player1, player2);
		if (playerChoice == 'b' && player2Choice == 'b')
		{
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
	main();
}
void BlackJackLogic::CompetitionNotDetailed(Player player, Player player2, Strategy* player1Strategy, Strategy* player2Strategy)
{
	srand(time(NULL));
	char playerChoice, player2Choice, startGame;
	std::system("CLS");
	while (true)
	{
		player2Choice = player2Strategy->GetStrategyChoice(player, player2);
		playerChoice = player1Strategy->GetStrategyChoice(player, player2);
		if (playerChoice == 'a')
			GetCard(player);
		if (player2Choice == 'a')
			GetCard(player2);
		if (playerChoice == 'b' && player2Choice == 'b')
		{
			cout << "End of game!\n";
			cout << "Two players took the pass, the winner was: " << (player.GetCardsSum() > player2.GetCardsSum() ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		if (player.GetCardsSum() > 21 || player2.GetCardsSum() > 21)
		{
			cout << "End of game!\n";
			cout << "One of the players scored more than 21, the winner was: " << (player.GetCardsSum() > 21 ? "player2" : "player1");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		else if (player.GetCardsSum() == 21 || player2.GetCardsSum() == 21)
		{
			cout << "End of game!\n";
			cout << "One of the players scored exactly 21 points, the winner was: " << (player.GetCardsSum() == 21 ? "player1" : "player2");
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
	}
	std::system("CLS");
	main();
}
void BlackJackLogic::Tournament(Player player, Player player2, Strategy* player1Strategy, Strategy* player2Strategy)
{
	srand(time(NULL));
	char playerChoice, player2Choice, startGame;
	std::system("CLS");
	auto DefineWinner
	{
		[](Player p1, Player p2)
	    {
			cout << "Победителем стал: " << (p1.GetTwoCardsSum() > p2.GetTwoCardsSum() ? "player1" : "player2");
        }
	};
	while (true)
	{
		player2Choice = player2Strategy->GetStrategyChoice(player, player2);;
		playerChoice = player1Strategy->GetStrategyChoice(player, player2);
		if (playerChoice == 'a')
			GetCard(player);
		if (player2Choice == 'a')
			GetCard(player2);
		if (playerChoice == 'b' && player2Choice == 'b')
		{
			cout << "End of game!\n";
			cout << "Reason: Both players took a pass.\n";
			DefineWinner(player, player2);
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
		if (player.GetCardsSum() >= 21 || player2.GetCardsSum() >= 21)
		{
			cout << "End of game!\n";
			cout << "Reason: One of the players has 21 points or more.\n";
			DefineWinner(player, player2);
			cout << "\n\n>> Press any key to return to main menu...";
			_getch();
			break;
		}
	}
	std::system("CLS");
	main();
}
void BlackJackLogic::Start(char gameMode, Strategy* strategy)
{
	Strategy* player2Strategy = nullptr;
	int randNumber = rand() % 13;
	if (randNumber <= 2)
		player2Strategy = new Easy1Strategy();
	else if (randNumber > 2 && randNumber <= 4)
		player2Strategy = new Easy2Strategy();
	else if (randNumber > 4 && randNumber <= 6)
		player2Strategy = new Easy3Strategy();
	else if (randNumber > 6 && randNumber <= 8)
		player2Strategy = new Hard1Strategy();
	else if (randNumber > 8 && randNumber <= 10)
		player2Strategy = new Hard2Strategy();
	else if (randNumber > 10)
		player2Strategy = new Hard3Strategy();

	if (gameMode == 'a')
		CompetitionDetailed(user, dealer, strategy, player2Strategy);
	else if (gameMode == 'b')
		CompetitionNotDetailed(user, dealer, strategy, player2Strategy);
	else if (gameMode == 'c')
		Tournament(user, dealer, strategy, player2Strategy);

}