#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include "blackjack.h"
#include "gui.h"
#include "enums.h"
#include "StrategyImp.h"

struct GConfigs {
	CardGivMode cMod;
	GameMode gMod;
	std::string configDir;
	unsigned char deckSize;
	size_t countStr;
	GConfigs(GConfigs & other);
	GConfigs();
	GConfigs & operator=(const GConfigs & other);
};

class Game {
	_Game _isGame;
	std::vector<std::unique_ptr<Strategy>> strategies;
	std::vector<StackCard> stackcard;
	std::vector<Decision> decisions;
	std::vector<Card> low_card;
	GConfigs configs;
	Deck deck;
	std::unique_ptr<Gui> gui;
private:
	void Tournament();
	void Turn();
	void ResultsCalculating();
	size_t Pair(size_t first, size_t second);
	Game() = delete;
public:
	Game(GConfigs, std::vector<std::unique_ptr<Strategy>>);
	~Game() {}
	void Play();
	void startGame() { _isGame = _Game::YES; }
	void stopGame() { _isGame = _Game::NO; }
	friend class Gui;
};
#endif