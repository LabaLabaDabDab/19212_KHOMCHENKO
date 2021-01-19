#ifndef DOMINATE_H
#define DOMINATE_H
#include "factory.h"
#include "StrategyImp.h"
#include <iostream>

class Dominate : public StrategyImp {
	unsigned int contrl;
public:
	void init(const std::string & path);
	Decision decide(const StackCard & stack, const std::vector<Card> & front, const std::vector<Decision> & decisions) override final;
	std::string getName() override final;
	std::string getID() override final;

	Dominate() { StrategyImp::score = 0u; }
	~Dominate() override {}
};

#endif // !DOMINATE_H