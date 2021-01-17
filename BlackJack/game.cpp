#include "game.h"
#include "gui.h"

GConfigs::GConfigs(GConfigs & other) : cMod(other.cMod), gMod(other.gMod),
configDir(other.configDir), deckSize(other.deckSize), countStr(other.countStr) {}

GConfigs::GConfigs() : cMod(CardGivMode::SIMPLE), gMod(GameMode::DETAILED),
deckSize(1u), countStr(2u) {}

GConfigs & GConfigs::operator=(const GConfigs & other) {
	if (this != &other) {
		cMod = other.cMod;
		gMod = other.gMod;
		deckSize = other.deckSize;
		countStr = other.countStr;
	}
	return *this;
}

Game::Game(GConfigs mode, std::vector<std::unique_ptr<Strategy>> str) : strategies(std::move(str)),
		configs(mode), deck(mode.deckSize, mode.cMod), gui(new Gui(this)) {
	stackcard.resize(mode.countStr);
	decisions.resize(mode.countStr);
	low_card.resize(mode.countStr);
}

void Game::Play() {
	startGame();
	unsigned int i = 0u;
	switch (configs.gMod) {
	case (GameMode::DETAILED): case (GameMode::FAST) :
		unsigned char c;
		for (i = 0u; i < configs.countStr; i++) {
			stackcard[i].push(deck.getCard());
			low_card[i] = stackcard[i].low();
		}
		try {
			for (i = 0u; i < configs.countStr; i++) {
				strategies[i]->init(configs.configDir);
				decisions[i] = strategies[i]->decide(stackcard[i], low_card, decisions);

				if (configs.gMod == GameMode::DETAILED)
					gui->TurnResults(i);
			}
		}
		catch (StrSettingError a) {
			a.what();
			stopGame();
			return;
		}
		while (_isGame == _Game::YES) {
			Turn();
			if (configs.gMod == GameMode::DETAILED){
				c = std::getchar();
			}
		}
		ResultsCalculating();
		break;

	case (GameMode::TOURNAMENT):
		Tournament();
		break;

	}
}

void Game::Turn() {
	unsigned int i = 0u;
	for(i = 0u; i < configs.countStr; i++){
		if (decisions[i] == Decision::NEXT) {
			stackcard[i].push(deck.getCard());
			decisions[i] = strategies[i]->decide(stackcard[i], low_card, decisions);
			if (configs.gMod == GameMode::DETAILED)
				gui->TurnResults(i);
		}
	} 
	for (i = 0u; i < configs.countStr; i++) {
		if (decisions[i] == Decision::NEXT) {
			if (configs.gMod == GameMode::DETAILED)
				std::cout << "Press any key to continue..." << std::endl;

			return;
		}
	}

	stopGame();
}

void Game::Tournament() {
	if (configs.countStr < 3) {
		std::cout << "Received to few (" << configs.countStr << ") strategies to play in this (tournament) mode. " <<
			"Game stoped." << std::endl;
		return;
	}
	size_t tmp = 0u, i = 0u, j = 0u;
	try {
		for (i = 0u; i < configs.countStr; i++)
			strategies[i]->init(configs.configDir);
	}
	catch (StrSettingError a) {
		a.what();
		stopGame();
		return;
	}
	gui->StrategiesList();
	std::vector<unsigned char> matrix(configs.countStr * configs.countStr);
	std::vector<unsigned char> results(configs.countStr);
	for (i = 0u; i < configs.countStr - 1u; i++) {
		for (j = i + 1u; j < configs.countStr; j++) {
			tmp = Pair(i, j);
			matrix[i*configs.countStr + j] = matrix[j*configs.countStr + i] = static_cast<unsigned char>(tmp);
			results[tmp]++;
		}
	}

	gui->TableResults(matrix);
	gui->TourneyResults(results);
	stopGame();
}

size_t Game::Pair(size_t i, size_t j) {
	decisions[i] = decisions[j] = Decision::NEXT;
	stackcard[i].push(deck.getCard());
	stackcard[j].push(deck.getCard());
	low_card[i] = stackcard[i].low();
	low_card[j] = stackcard[j].low();
	decisions[j] = strategies[j]->decide(stackcard[j], low_card, decisions);
	decisions[j] = strategies[j]->decide(stackcard[j], low_card, decisions);
	while (decisions[i] != Decision::STOP || decisions[j] != Decision::STOP) {
		if (decisions[i] == Decision::NEXT) {
			stackcard[i].push(deck.getCard());
			decisions[i] = strategies[i]->decide(stackcard[i], low_card, decisions);
		}
		if (decisions[j] == Decision::NEXT) {
			stackcard[j].push(deck.getCard());
			decisions[j] = strategies[j]->decide(stackcard[j], low_card, decisions);
		}
	} 
	
	size_t ret = 0u;
	if (stackcard[i].score() <= 21u) {
		if (stackcard[i].score() > stackcard[j].score() || stackcard[j].score() > 21u)
			ret = i;
		else if (stackcard[i].score() == stackcard[j].score()) {
			ret = configs.countStr;
		}
	}
	else {
		ret = ((stackcard[j].score() <= 21u) ? j : configs.countStr);
	}
	
	stackcard[i].clear();
	stackcard[j].clear();
	deck.shufle();
	return ret;
}

void Game::ResultsCalculating() {
	unsigned int i, championNumber = 0u, flag = 0u;
	for (i = 0u; i < configs.countStr; i++) {
		if (stackcard[i].score() <= 21u) {
			if (stackcard[i].score() > stackcard[championNumber].score() || stackcard[championNumber].score() > 21u) {
				championNumber = i;
				flag = 0;
			}
			else if (stackcard[i].score() == stackcard[championNumber].score() && championNumber != i) {
				flag = 1;
			}
		}
	}
	if (stackcard[championNumber].score() > 21u) {
		std::cout << "All strategies lost the game." << std::endl;
		gui->Results();
		return;
	}
	if (flag == 0)
		std::cout << "Strategy number " << championNumber + 1u << " won the game." << std::endl;
	else
		std::cout << "Drawn game! At least two strategies scored equal score!" << std::endl;

	gui->Results();
}