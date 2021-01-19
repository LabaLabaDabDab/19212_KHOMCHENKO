#include "blackjack.h"

std::vector<Card> Deck::start_deck(0);

const Card & Card::operator=(const Card & other) {
	if (this != &other) {
		number = other.number;
		weight = other.weight;
		suit = other.suit;
	}
	return *this;
}

void Deck::shufle() {
	topCard = N * size - 1u;
	unsigned int i;
	srand(int(time(0)));
	if (mode == CardGivMode::SIMPLE) {
		for (i = 0u; i <= topCard; i++) {
			deck[i].number = static_cast<unsigned char>(1 + rand() % (size / 4));
			deck[i].weight = deck[i].number;
		}
		return;
	}
	else {
		unsigned int tmp;
		if (start_deck.size() == 0)
			Deck::InitialDeck();

		for (i = 0u; i <= topCard; i++)
			deck[i] = start_deck[i % size];

		for (i = 0u; i <= topCard; i++) {
			tmp = rand() % (N * size);
			if (tmp != i)
				std::swap(deck[i], deck[tmp]);
		}
		return;
	}
}


const Card & Deck::getCard() {
	if (topCard == 0u) {
		Card & ret = deck[0u];
		shufle();
		return ret;
	}
	return deck[topCard--];
}

void Deck::InitialDeck() {
	if (start_deck.size() == 0) {
		start_deck.resize(size);
		unsigned char i = 0u, j = 0u, cnt = 0u;
		for (; i < 4; i++) {
			for (j = 0u; j < size / 4; j++) {
				start_deck[cnt].number = j + (15 - size / 4);
				start_deck[cnt].suit = Suits(i);
				if (j == size / 4 - 1)
					start_deck[cnt].weight = 11;

				else if ((j >= size / 4 - 5) && (j <= size / 4 - 2))
					start_deck[cnt].weight = 10;

				else
					start_deck[cnt].weight = j + (15 - size / 4);
				cnt++;
			}
		}
	}
}