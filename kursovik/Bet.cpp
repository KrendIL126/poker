#include "Bet.h"

char Bet::getChoice() {
	return choice;
}

float Bet::getSize() {
	return size;
}

void Bet::setChoice(char c) {
	choice = c;
}

void Bet::addSize(float s) {
	size += s;
}