#ifndef DIFFICULT_H
#define DIFFICULT_H
#include <fstream>
#include <vector>
#include "factory.h"
#include "StrategyImp.h"

class Difficult : public StrategyImp {
	std::vector<std::vector<unsigned int>> data;
public:
	void init(const std::string & path);
	Decision decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) override final;
	std::string getName() override final;
	std::string getID() override final;
	Difficult() { StrategyImp::score = 0u; }
	~Difficult() override {}
};

#endif 