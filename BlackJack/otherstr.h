#ifndef OTHERSTR_H
#define OTHERSTR_H

#include <fstream>
#include <vector>
#include "factory.h"
#include "StrategyImp.h"

class Other : public StrategyImp {
	std::vector<std::vector<unsigned int>> data;
	unsigned int coefficient = 1;
public:
	void init(const std::string & path);
	Decision decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) override final;
	std::string getName() override final;
	std::string getID() override final;
	Other() { StrategyImp::score = 0u; }
	~Other() override {}
};

#endif 