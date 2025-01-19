#include "Card.h"
#include <iostream>

void Card::print() {
	std::cout << value << suit;
}

char Card::getValue() {
	return this->value;
}

void Card::setValue(char value) {
	this->value = value;
}

char Card::getSuit() {
	return this->suit;
}

void Card::setSuit(char suit) {
	this->suit = suit;
}