#ifndef STRATEGY_H
#define STRATEGY_H

#include "blackjack.h"
#include "exception.h"

class Strategy {
public:
	Strategy() {}
	virtual ~Strategy() {}
	virtual void init(const std::string & path) = 0;
	virtual Decision decide(const StackCard &, const std::vector<Card> & front, const std::vector<Decision> & decisions) = 0;
	virtual std::string getName() = 0;
	virtual std::string getID() = 0;
};

#endif