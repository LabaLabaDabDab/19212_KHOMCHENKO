#pragma once
#include <iostream>
#include <windows.h>
#include "BlackJackLogic.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	system("cls");

	char choice;
	BlackJackLogic* blackJack = new BlackJackLogic();
	blackJack->Start();
	delete blackJack;


	cout << "Retry? (y/n)\n>> ";
	cin >> choice;
	if (choice == 'y')
		main();
	else exit(NULL);


	cin.get();
	cin.get();
}