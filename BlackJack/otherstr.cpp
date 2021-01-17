#include "otherstr.h"

namespace {
	Strategy * newOther() {
		return new Other;
	}
	std::string ID = "other";
	std::string name = "Other strategy";
	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy(ID, (Strategy * (*)())newOther);
}

void Other::init(const std::string & path) {
	std::ifstream file;
	std::string fullpath;
	fullpath.resize(path.length());
	std::copy(path.begin(), path.end(), fullpath.begin());
	fullpath.push_back(char(92));
	fullpath.append(ID);
	fullpath.append(".txt");
	file.open(fullpath, std::ios_base::in);
	if (!file.is_open())
		throw StrSettingError();
	int count = 0, coef = 0, tmp = 0, i = 0, j = 0;
	file >> count;
	file >> coef;
	if (count < 0 || count > 21 || coef < 1 || coef > 10)
		throw StrSettingError();
	coefficient = coef;
	data.resize(count);
	for (i = 0; i < count; i++) {
		file >> tmp;
		if (tmp < 0 || tmp > 21)
			throw StrSettingError();
		data[i].push_back(tmp);
		for (j = 0; j < 21; j++) {
			file >> tmp;
			if (tmp < 0 || tmp > 1) {
				throw StrSettingError();
			}
			data[i].push_back(tmp);
			tmp = 2;
		}
	}
	file.close();
}

Decision Other::decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) {
	getScore(stack);
	unsigned char max = 0;
	for (auto it : front) {
		if (max < it.weight)
			max = it.weight;
	}
	int i = 0;
	for (i = 0; i < data.size(); i++) {
		if (static_cast<int>(max) < data[i].front())
			break;
	}
	std::vector<unsigned int> & behavior = data[i < data.size() ? i : data.size() - 1];
	unsigned char counter = 0; //how many strategies stoped the game
	for (auto it : decisions) {
		if (it == Decision::STOP)
			counter++;
	}
	if (counter > decisions.size() / coefficient)
		return Decision::STOP;

	return (behavior[score <= 21 ? score + 1 : 21] == 1 ? Decision::NEXT : Decision::STOP);
}

std::string Other::getName() {
	return name;
}

std::string Other::getID() {
	return ID;
}