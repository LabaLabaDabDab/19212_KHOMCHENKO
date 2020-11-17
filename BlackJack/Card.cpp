#pragma once
#include <iostream>
#include "Card.h"

using namespace std;

Card::Card(int value)
{
	this->value = value;
}
Card::Card(char type, int value) : Card(value)
{
	this->type = type;
}