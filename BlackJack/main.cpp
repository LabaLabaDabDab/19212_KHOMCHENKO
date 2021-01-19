#include <cstring>
#include "blackjack.h"
#include "factory.h"
#include "game.h"
#include "string"
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
			if (std::strncmp(par[i].c_str(), "--configs=", tmp.length()) != 0) {
				std::cout << "Undefined argument for programm!" << par[i] << std::endl;
				continue;
			}
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

	std::cout << "This is a programm for simulating 'BlackJack' game." << std::endl;
	if (argc < 2) {
		std::cout << "Bad input" << std::endl;
		return 1;
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
		if (nullptr == function) {
			std::cerr << "Unikown strategy ID " << ID[i] << std::endl;
			continue;
		}
		strategies.emplace_back(function());
	}
	configs.countStr = strategies.size();
	if (configs.countStr < 2) {
		std::cerr << " Too few strategies identified, impossible to continue the game" << std::endl;
		return 0;
	}

	Game game(configs, std::move(strategies));
	game.Play();

	return 0;
}