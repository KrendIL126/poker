#pragma once

class Card {
private:
	char value;  // 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A
	char suit;  // spades,clubs, diamonds, hearts

public:
	Card() {
		value = 'x';
		suit = 'x';
	}
	Card(char value, char suit) {
		this->value = value;
		this->suit = suit;
	}

	void print();
	char getValue();
	void setValue(char value);
	char getSuit();
	void setSuit(char suit);
};