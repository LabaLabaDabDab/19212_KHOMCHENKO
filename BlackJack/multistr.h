#ifndef MULTISTR_H
#define MULTISTR_H

#include <fstream>
#include <vector>
#include "factory.h"
#include "StrategyImp.h"

class Multi : public StrategyImp {
	std::vector<std::vector<unsigned int>> data;
	unsigned char coefficient = 2;
public:
	void init(const std::string & path);
	Decision decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) override final;
	std::string getName() override final;
	std::string getID() override final;

	Multi() { StrategyImp::score = 0u; }
	~Multi() override {}
};

#endif 