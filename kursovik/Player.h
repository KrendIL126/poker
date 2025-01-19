#pragma once

#include <string>
#include "Card.h"

class Player {
private:
	std::string name;
	Card hand[2];
	float cash;
	float bet;

public:
	Player() {
		name = "0";
		this->hand[0] = Card();
		this->hand[1] = Card();
		this->cash = 0;
		this->bet = 0;
	}

	Player(std::string name, float cash) {
		this->name = name;
		this->hand[0] = Card();
		this->hand[1] = Card();
		this->cash = cash;
		this->bet = 0;
	}

	float fold();
	void check();
	void call(float genBet);
	void raise(float size);
	int checkCombo(Card* board);
	std::string getName();
	void setName(std::string name);
	Card getHand(int i);
	void setHand(Card card, int index);
	float getCash();
	void setCash(float cash);
	float getBet();
	float takeBet();
};