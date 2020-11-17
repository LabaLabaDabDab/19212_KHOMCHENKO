#pragma once
#include <iostream>
#include "BlackJackLogic.h"
#include "Strategy.h"
#include "ISerializable.h"

#include "Easy1Strategy.h"
#include "Easy2Strategy.h"
#include "Easy3Strategy.h"

#include "Hard1Strategy.h"
#include "Hard2Strategy.h"
#include "Hard3Strategy.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int N = 1;
	Strategy* playerStrategy = nullptr;
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
			playerStrategy = new Easy1Strategy();
			break;
		case 'b':
			playerStrategy = new Easy2Strategy();
			break;
		case 'c':
			playerStrategy = new Easy3Strategy();
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
			playerStrategy = new Hard1Strategy();
			break;
		case 'b':
			playerStrategy = new Hard3Strategy();
			break;
		case 'c':
			playerStrategy = new Hard2Strategy();
			break;
		default:
			break;
		}
	}
	BlackJackLogic* blackJack = new BlackJackLogic(cardOutputMode, N);
	blackJack->Start(gameMode, playerStrategy);
	cin.get();
	cin.get();
}