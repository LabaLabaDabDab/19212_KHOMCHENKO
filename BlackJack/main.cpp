#include <cstring>
#include "blackjack.h"
#include "factory.h"
#include "game.h"
#include "string"
#include "exception.h"
#include "gtest/gtest.h"

void ParametrsProcessing(GConfigs & mode, std::vector<std::string> & ID, std::vector<std::string> & par) {
	unsigned int i;
	for (i = 0u; i < par.size(); i++) {
		if (par[i] == "--mode=detailed") {
			mode.gMod = GameMode::DETAILED;
		}
		else if (par[i] == "--mode=fast") {
			mode.gMod = GameMode::FAST;
		}
		else if (par[i] == "--mode=tournament") {
			mode.gMod = GameMode::TOURNAMENT;
		}
		else if (par[i] == "--card=simple") {
			mode.cMod = CardGivMode::SIMPLE;
		}
		else if (par[i] == "--card=default") {
			mode.cMod = CardGivMode::DEFAULT;
		}
		else if (par[i].front() == '-') {
			std::string tmp = "--configs=";
			mode.configDir.resize(par[i].length() - tmp.length());
			std::copy(par[i].begin() + tmp.length(), par[i].end(), mode.configDir.begin());
		}
		else {
			ID.push_back(par[i]);
		}
	}
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    return 0;
    /*

	if (argc < 2) {
        throw BadInput();
	}
	std::vector<std::string> parametrs(0);
	std::vector<std::string> ID(0);
	GConfigs configs;
	for (int i = 1; i < argc; i++)
		parametrs.push_back(std::string(argv[i]));
	
	ParametrsProcessing(configs, ID, parametrs);
	std::vector<std::unique_ptr<Strategy>> strategies(0);
	Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();

	for (int i = 0; i < ID.size(); ++i) {
		Strategy * (*function)() = f->createStrategyByID(ID[i]);
		strategies.emplace_back(function());
	}
	configs.countStr = strategies.size();
	if (configs.countStr < 2) {
		throw BadStr();
	}

	Game game(configs, std::move(strategies));
	game.Play();

	return 0;
    */
}