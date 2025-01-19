#include "Deck.h"
#include <iostream>
#include <algorithm>

void Deck::reload() {
	int i = 0;
	for (char s : "schd")
		for (char v : "23456789TJQKA")
			if (v != '\0' and s != '\0') {
				cards[i].setValue(v);
				cards[i].setSuit(s);
				i++;
			}
	counter = 0;
}

void Deck::shuffle() {
	std::random_shuffle(std::begin(cards), std::end(cards));
}

void Deck::print() {
	for (Card c : cards) {
		c.print();
		std::cout << std::endl;
	}
}

Card Deck::getCard(int index) {
	return cards[(counter + index) % 52];
}

int Deck::getCounter() {
	return counter;
}

void Deck::addCounter() {
	counter++;
}