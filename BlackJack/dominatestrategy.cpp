#include "dominatestrategy.h"

namespace {
	Strategy * newDominate() {
		return new Dominate;
	}
	std::string ID = "dominate";
	std::string name = "Dominate strategy";
	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy(ID, (Strategy * (*)())newDominate);
};

void Dominate::init(const std::string & path) {
	std::ifstream file;
	std::string fullpath;
	fullpath.resize(path.length());
	std::copy(path.begin(), path.end(), fullpath.begin());
	fullpath.push_back(char(92));
	fullpath.append(ID);
	fullpath.append(".txt");
	file.open(fullpath, std::ios_base::in);
	if (file.is_open())
		file >> contrl;
	else
		contrl = 18;
	file.close();
}

Decision Dominate::decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) {
	getScore(stack);

	return ((score < contrl) ? Decision::NEXT : Decision::STOP);
}
std::string Dominate::getName() {
	return name;
}

std::string Dominate::getID() {
	return ID;
}