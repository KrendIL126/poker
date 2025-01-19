#pragma once

#include "Card.h"

class Deck {
private:
	Card cards[52];
	int counter;

public:
	Deck() {
		reload();
	}

	void reload();
	void shuffle();
	void print();
	Card getCard(int index);
	int getCounter();
	void addCounter();
};