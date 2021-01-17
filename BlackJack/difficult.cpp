#include "difficult.h"

namespace {
	Strategy * newDifficult() {
		return new Difficult;
	}
	std::string ID = "difficult";
	std::string name = "Difficult strategy";
	bool ok = Factory <std::string, Strategy * (*)()>::getInstance()
		->regStrategy(ID, (Strategy * (*)())newDifficult);
}

void Difficult::init(const std::string & path) {
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
	int count = 0, tmp = 0, i = 0, j = 0;
	file >> count;
	if (count < 0 || count > 21)
		throw StrSettingError();
	data.resize(count);
	for (i = 0; i < count; i++) {
		file >> tmp;
		if (tmp < 0 || tmp > 21)
			throw StrSettingError();
		data[i].push_back(tmp);
		for (j = 0; j < 21; j++) {
			file >> tmp;
			if (tmp < 0 || tmp > 1)
				throw StrSettingError();
			data[i].push_back(tmp);
			tmp = 2;
		}
	}
	file.close();
}

Decision Difficult::decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) {
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
	return (behavior[score <= 21 ? score + 1 : 21] == 1 ? Decision::NEXT : Decision::STOP);
}

std::string Difficult::getName() {
	return name;
}

std::string Difficult::getID() {
	return ID;
}