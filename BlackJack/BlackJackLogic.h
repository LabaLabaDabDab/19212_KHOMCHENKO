#ifndef UNTITLED7_BLACKJACKLOGIC_H
#define UNTITLED7_BLACKJACKLOGIC_H

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include "Player.h"

using namespace std;
int main();
class BlackJackLogic{
private:
    Deck deck;
    Player user, dealer;
public:
    BlackJackLogic(char outputCardMode, int N, int aceGlasses = 1){
        switch (outputCardMode){
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
    // Метод для получения карты, который принимает в аргументах игрока, которому будет выдана карта
    void GetCard(Player &target){
        target.deck.Cards.push_back(deck.Cards[deck.Cards.size() - 1]);
        deck.Cards.pop_back();
    }
    // Симуляция a.
    void CompetitionDetailed(Player player, Player dealer){
        srand(time(0));
        char playerChoice, dealerChoice;
        while (true){
            system("CLS");
            cout << "Выберите один из пунктов:\na. Взять карту\nb. Пасс\nc. Выход\n>> ";
            cin >> playerChoice;
            dealerChoice = (rand() % 10) <= 5 ? 'a' : 'b';
            system("CLS");
            if (playerChoice == 'c')
                break;
            if (playerChoice == 'b' && dealerChoice == 'b'){
                cout << "Конец игры!\n";
                cout << "Два игрока взяли пасс, победителем стал: " << (player.GetCardsSum() > dealer.GetCardsSum() ? "игрок1" : "игрок2");
                cout << "\n\n>> Нажмите любую клавишу для возврата в гл.меню...";
                _getch();
                break;
            }
            if (playerChoice == 'a')
                GetCard(player);
            if (dealerChoice == 'a')
                GetCard(dealer);
            cout << "                          Игрок1           |    Игрок2\n";
            cout << "\nДействие:                 " << (playerChoice == 'a' ? "взял карту" : "пасс") << "            " <<(dealerChoice == 'a' ? "взял карту" : "пасс");
            cout << "\n\nОчки за текущий ход:      " << (player.deck.Cards.size() > 0? player.deck.Cards[player.deck.Cards.size() - 1]->value : 0) << "                     " << (dealer.deck.Cards.size() > 0 ? dealer.deck.Cards[dealer.deck.Cards.size() - 1]->value : 0);
            cout << "\n\nОчки за текущую игру:     " << player.GetCardsSum() << "                     " << dealer.GetCardsSum() << endl<<"\n\n>> Нажмите любую клавишу чтобы продолжить...";
            _getch();
            system("CLS");
            if (player.GetCardsSum() > 21 || dealer.GetCardsSum() > 21){
                cout << "Конец игры!\n";
                cout << "Один из игроков набрал больше 21, победителем стал: " << (player.GetCardsSum() > 21 ? "игрок2" : "игрок1");
                cout << "\n\n>> Нажмите любую клавишу для возврата в гл.меню...";
                _getch();
                break;
            }
            if (player.GetCardsSum() == 21 || dealer.GetCardsSum() == 21){
                cout << "Конец игры!\n";
                cout << "Один из игроков набрал ровно 21 очко, победителем стал: " << (player.GetCardsSum() == 21 ? "игрок1" : "игрок2");
                cout << "\n\n>> Нажмите любую клавишу для возврата в гл.меню...";
                _getch();
                break;
            }
        }
        system("CLS");
        main();
    }
    // Симуляция b.
    void CompetitionNotDetailed(Player player, Player dealer){
        srand(time(0));
        char playerChoice, dealerChoice;
        system("CLS");
        cout << "Выберите один из пунктов:\na. Взять карту\nb. Пасс\nc. Выход\n>> ";
        cin >> playerChoice;
        dealerChoice = (rand() % 10) <= 5 ? 'a' : 'b';
        system("CLS");
        if (playerChoice == 'c'){
            system("CLS");
            main();
        }
        if (playerChoice == 'b' && dealerChoice == 'b'){
            cout << "Конец игры!\n";
            cout << "Два игрока взяли пасс, победителем стал: " << (player.GetCardsSum() > dealer.GetCardsSum() ? "игрок1" : "игрок2");
            cout << "\n\n>> Нажмите любую клавишу для возврата в гл.меню...";
            _getch();
            system("CLS");
            main();
        }
        if (playerChoice == 'a')
            GetCard(player);
        if (dealerChoice == 'a')
            GetCard(dealer);
        cout << "                          Игрок1           |    Игрок2\n";
        cout << "\nДействие:                 " << (playerChoice == 'a' ? "взял карту" : "пасс") << "            " << (dealerChoice == 'a' ? "взял карту" : "пасс");
        cout << "\n\nОчки за текущий ход:      " << (player.deck.Cards.size() > 0 ? player.deck.Cards[player.deck.Cards.size() - 1]->value : 0) << "                     " << (dealer.deck.Cards.size() > 0 ? dealer.deck.Cards[dealer.deck.Cards.size() - 1]->value : 0);
        cout << "\n\nОчки за текущую игру:     " << player.GetCardsSum() << "                     " << dealer.GetCardsSum() << endl << "\n\n>> Нажмите любую клавишу чтобы продолжить...";
        _getch();
        system("CLS");
        cout << "Конец игры!\n";
        cout << "Победителем стал: " << (player.GetCardsSum() > dealer.GetCardsSum() ? "игрок1" : "игрок2");
        cout << "\n\n>> Нажмите любую клавишу для возврата в гл.меню...";
        _getch();
        system("CLS");
        main();
    }
    // Симуляция c.
    void Tournament(Player player, Player dealer){
        system("CLS");
        cout << "В разработке.";
    }
    // Метод для начала игры
    void Start(char gameMode){
        if (gameMode == 'a')
            CompetitionDetailed(user, dealer);
        else if (gameMode == 'b')
            CompetitionNotDetailed(user, dealer);
        else if (gameMode == 'c')
            Tournament(user, dealer);
    }
};

#endif //UNTITLED7_BLACKJACKLOGIC_H
