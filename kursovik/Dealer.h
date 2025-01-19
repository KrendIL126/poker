#pragma once

#include "Deck.h"
#include "Table.h"

class Dealer {
private:
	Deck deck;
	Table* table;
	float bank;  // is it important? u can store it in Table

public:
	Dealer(Table *t) {
		deck = Deck();
		table = t;
		bank = 0;
	}

	void giveCard(Player *p);
	void goPreflop();
	void goFlop();
	void goTurn();
	void goRiver();
	void showdown();
	Deck* getDeck();
	Table* getTable();
	void setTable(Table* t);
	float getBank();
	void addBank(float cash);

};