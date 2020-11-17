#ifndef UNTITLED7_CARD_H
#define UNTITLED7_CARD_H

#pragma once
#include<iostream>

using namespace std;
class Card{
public:
    int value; // Значение карты (карты с картинками по 10, и т.д)
    char type; // Тип карты, используется для обозначения карт с картинкой
    Card(int value){
        this->value = value;
    }
    Card(char type, int value) : Card(value){
        this->type = type;
    }
};

#endif //UNTITLED7_CARD_H
