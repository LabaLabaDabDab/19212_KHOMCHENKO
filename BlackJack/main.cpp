#pragma once
#include <iostream>
#include "BlackJackLogic.h"

using namespace std;
int main(){
    setlocale(LC_ALL, "Russian");
    int N = 1;
    char cardOutputMode = 'x', gameMode = 'x';
    char aceValueChoice;
    cout << "Выберите значение туза: \na. 1\nb. 11\n>> ";
    cin >> aceValueChoice;
    Deck::AceGlasses = aceValueChoice == 'a' ? 1 : 11;
    system("CLS");
    while (cardOutputMode != 'a' && cardOutputMode != 'b' && cardOutputMode != 'c'){
        cout << "Выберите тип игры: " << endl;
        cout << "a. Упрощённый.";
        cout << "\nb. Одна колода.";
        cout << "\nc. Выдача из N конечных колод.\n>> ";
        cin >> cardOutputMode;
        system("CLS");
        if (cardOutputMode == 'c')
        {
            cout << "Введите кол-во колод: " << endl;
            cin >> N;
        }
    }
    while (gameMode != 'a' && gameMode != 'b' && gameMode != 'c'){
        system("CLS");
        cout << "Выберите режим игры: ";
        cout << "\na. Соревнование с детализацией.";
        cout << "\nb. Соревнование без детализации.";
        cout << "\nc. Турнир.\n>> ";
        cin >> gameMode;
    }
    BlackJackLogic* blackJack = new BlackJackLogic(cardOutputMode, N);
    blackJack->Start(gameMode);
    cin.get();
    cin.get();
}