#pragma once
#include "factory.h"
#include "StrategyImp.h"

class FirstStr : public StrategyImp {
public:
	void init(const std::string & path) {}
	Decision decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) override;
	std::string getName() override;
	std::string getID() override;
	FirstStr() { score = 0u; }
	~FirstStr() {}
};