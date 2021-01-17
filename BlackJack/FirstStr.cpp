#include "firststr.h"
namespace {
	Strategy * newFirstStr() {
		return new FirstStr;
	}
	std::string ID = "first";
	std::string name = "Seventeen Points Strategy";

	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy(ID, (Strategy * (*)())newFirstStr);
};

Decision FirstStr::decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) {
	getScore(stack);
	unsigned int aaa = StrategyImp::score;
	return ((aaa < 17u) ?  Decision::NEXT : Decision::STOP);
}

std::string FirstStr::getName() {
	return name;
}

std::string FirstStr::getID() {
	return ID;
}