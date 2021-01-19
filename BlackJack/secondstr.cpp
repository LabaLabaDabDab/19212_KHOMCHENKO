#include "secondstr.h"

namespace {
	Strategy * newSecondStr() {
		return new SecondStr;
	}
	std::string ID = "second";
	std::string name = "Bad and loosed strategy";
	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy(ID, (Strategy * (*)())newSecondStr);
};

Decision SecondStr::decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) {
	getScore(stack);
	return ((StrategyImp::score < 16u && StrategyImp::score > 2u) ? Decision::NEXT : Decision::STOP);
}
std::string SecondStr::getName() {
	return name;
}

std::string SecondStr::getID() {
	return ID;
}