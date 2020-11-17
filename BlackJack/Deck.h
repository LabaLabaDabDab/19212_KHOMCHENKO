#ifndef UNTITLED7_DECK_H
#define UNTITLED7_DECK_H

#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "Card.h"
using namespace std;

class Deck{
public:
    // Значение туза, может быть 1 или 11
    static int AceGlasses;
    // Вектор карт (массив)
    vector<Card*> Cards;
    // Создание массива карт (Упрощённый)
    static vector<Card*> CreateSimplifiedDeck(){
        vector<Card*> result;
        for (int i = 2; i <= 10; i++)
            for (int m = 0; m < 4; m++)
                result.push_back(new Card('D', i));
        return result;
    }
    // Создание массива карт (Одна колода)
    static vector<Card*> CreatePrimitiveDeck(){
        vector<Card*> result;
        vector<char> specialCards{ 'T', 'K', 'L', 'J', '\0' };
        for (int j = 0; j < specialCards.size(); j++)
            for (int m = 0; m < 4; m++)
                result.push_back(new Card(specialCards[j], specialCards[j] == 'T' ? AceGlasses : 10));
        for (int i = 2; i <= 10; i++)
            for (int m = 0; m < 4; m++)
                result.push_back(new Card('D', i));
        return result;
    }
    // Создание массива карт (Выдача из N кол-ва колод)
    static vector<Card*> CreateMultiDeck(int N){
        vector<Card*> result;
        for (int i = 0; i < N; i++)
            AddRange(result, CreatePrimitiveDeck());
        return result;
    }
    // Метод для тасовки колоды
    void ShuffleDeck(){
        srand(time(0));
        for (int i = 0; i < Cards.size(); i++)
            swap(Cards[i], Cards[rand() % Cards.size()]);
    }
    // Метод для добавления массив в массив (используется для совмещения нескольких колод в одну)
    static void AddRange(vector<Card*> &source, vector<Card*> cards){
        for (int i = 0; i < cards.size(); i++)
            source.push_back(cards[i]);
    }
    // Вывод на консоль
    void PrintDeck(){
        for (int i = 0; i < Cards.size(); i++)
            cout << "Карта: " << Cards[i]->type << " : " << Cards[i]->value << endl;
    }
};

// Устанавливаем начальное значение туза
int Deck::AceGlasses = 1;

#endif //UNTITLED7_DECK_H
