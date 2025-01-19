#pragma once

#include "Card.h"
#include "Player.h"

class Table {
private:
	Card board[5];
	float bank;
	Player* seats[8];
	int btnPos;
	//genBet

public:
	Table() {
		bank = 0;
		btnPos = 0;
	}

	void printBoard();
	void printTable();
	Card* getBoard();
	Card getBoard(int index);
	void setBoard(Card card, int index);
	float getBank();
	void addBank(float cash);
	Player** getAllPlayers();
	Player* getPlayer(int index);
	void addPlayer(Player* player, int index);
	void removePlayer(int i);
	int getBtnPos();
	void moveBtn();
};