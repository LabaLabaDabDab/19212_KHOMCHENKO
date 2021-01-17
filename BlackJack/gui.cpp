#include "gui.h"
#include <string>
#include "game.h"
#include "blackjack.h"
#include "strategy.h"

void Gui::TurnResults(unsigned int i) const {
	std::cout << " \t" << i + 1u << ": \n"
		<< "\tSummary score: " << static_cast<unsigned int>(game->stackcard[i].score()) << ";\n"
		<< "\tScore on turn: " << static_cast<unsigned int>(game->stackcard[i].top().weight) << ";\n"
		<< i + 1u << "'st " << "Strategy decision: ";
	std::cout << (game->decisions[i] == Decision::NEXT ? "continue the game." : "stop the game.") << std::endl;
}

void Gui::Results() const {
	std::cout << " " << game->configs.countStr << " strategies competed in the game: " << std::endl;
	unsigned int i = 0u;
	for (; i < game->configs.countStr; i++) {
		std::cout << i + 1 << ".) - '" << game->strategies[i]->getName() << "'\n "
			 << " ID is:" << game->strategies[i]->getID() << "' is ID of this strategy." << std::endl;
	}
	std::cout << "\tTable with results:" << std::endl;
	std::cout << "   Number:    | Num of moves:|     Score:   " << std::endl;
	for (i = 0u; i < game->configs.countStr; i++) {
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << i + 1 << "|";
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << static_cast<unsigned int>(game->stackcard[i].size()) << "|";
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << static_cast<unsigned int>(game->stackcard[i].score()) << std::endl;
	}
}

void Gui::StrategiesList() const {
	std::cout << "       TOURNAMENT" << std::endl;
	std::cout << "   Number:    | Name: " << std::endl;
	for (unsigned int i = 0; i < game->configs.countStr; i++) {
		std::cout.width(13);
		std::cout.setf(std::ios::left);
		std::cout << "    " << i + 1 << "|";
		std::cout << game->strategies[i]->getName() << std::endl;
	}
}

void Gui::TableResults(const std::vector<unsigned char>& table) const {
	unsigned char i = 0u, j = 0u;
	std::cout << " Table with results of a tourney: " << std::endl;
	std::cout << "NUMBER";
	for (j = 0u; j < game->configs.countStr; j++) {
		std::cout << "|  " << j + 1u << "  ";
	}
	std::cout << std::endl;
	for (i = 0u; i < game->configs.countStr; i++) {
		std::cout << "   " << i + 1u << "  ";
		for (j = 0u; j < game->configs.countStr;j++) {
			if (i == j) 
				std::cout << "|  " << static_cast<char>('~') << "  ";
			else
				std::cout << "|  " << static_cast<int>(table[i * game->configs.countStr + j]) + 1 << "  ";
		}
		std::cout << std::endl;
	}
}

void Gui::TourneyResults(const std::vector<unsigned char> & results) const {
	std::cout << std::endl;
	unsigned char i;
	std::vector<unsigned char> winners;
	winners.push_back(0u);
	for (i = 1u; i < game->configs.countStr; i++) {
		if (results[i] > results[winners.back()]) {
			winners.clear();
			winners.push_back(i);
		}
		else if (results[i] == results[winners.back()]) {
			winners.push_back(i);
		}
	}
	if (winners.size() > 1u) {
		std::cout << "Drawn game! At least two strategies scored equal score!" << std::endl;
		std::cout << "\t Strategies with the highest score:" << std::endl;
		std::cout << "NUMBER|" << "SCORE  |" << "\tNAME:" << std::endl;
		for (auto it : winners)
			std::cout << "   " << it + 1u << "  |   " << static_cast<int>(results[it]) << "  |"
				<< game->strategies[it]->getName() << std::endl;
		
	}
	else {
		std::cout << game->strategies[winners.back()]->getName() << " won the tourney. It's strategy number " <<
			winners.back() + 1 << ". " << std::endl;
	}
}