#ifndef STRATEGY_IMP_H
#define STRATEGY_IMP_H
#include <fstream>
#include <vector>
#include <string>
#include "strategy.h"

class StrategyImp : public Strategy {
public:
	std::string path;
	virtual ~StrategyImp() {}
	void getScore(const StackCard & stack) { score = stack.score(); }

protected:
    unsigned int score = 0u;
    unsigned char number = 0u;
};
#endif