#ifndef BLACKJACK_H

#define BLACKJACK_H
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

#include "enums.h"

struct Card {
	unsigned char number;
	unsigned char weight;
	Suits suit = Suits::HEART;
	const Card & operator=(const Card & other);
};

class Deck {
	const static unsigned char size = 52u;
	static std::vector<Card> start_deck;

	CardGivMode mode;
	unsigned char N;
	unsigned int topCard;
	std::vector<Card> deck;
public:
	Deck(unsigned char n = 1u, CardGivMode md = CardGivMode::SIMPLE) : N(n), mode(md)
			{ deck.resize(size * N); shufle(); }
	const Card & getCard();
	void shufle();

	static void InitialDeck();
};

class StackCard {
	std::vector<Card> stack_card;
	unsigned int weight_stack = 0u;
public:
	StackCard() : weight_stack(0u) {}
	~StackCard() {}
	const Card & top() const { return stack_card.back(); }
	const Card & low() const { return stack_card.front(); }
	void push(const Card & other) { stack_card.push_back(other) ; weight_stack += (unsigned int)other.weight; }
	void pop() { weight_stack -= (unsigned int)stack_card.back().weight; stack_card.pop_back(); }
	void clear() { stack_card.clear(); weight_stack = 0u; }
	unsigned int size() const { return (unsigned int)stack_card.size(); }
	unsigned int score() const { return weight_stack; }

	StackCard(const Card & other) = delete;
	StackCard & operator=(const StackCard &) = delete;
};
#endif