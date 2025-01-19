#include <iostream>
#include "Table.h"

void Table::printBoard() {
	for (Card c : board)
		std::cout << c.getValue() << c.getSuit() << ' ';
	std::cout << std::endl;
}

void Table::printTable() {
	for (Card c : board)
		std::cout << c.getValue() << c.getSuit() << ' ';
	std::cout << std::endl;

	for (int i = 0; i < 8; i++)
		if (seats[i]->getName() != "0") {
			std::cout << i + 1 << ") " << seats[i]->getName() << " - ";
			seats[i]->getHand(0).print();
			seats[i]->getHand(1).print();
			std::cout << std::endl;
		}
}

Card* Table::getBoard() {
	return board;
}

Card Table::getBoard(int index) {
	return board[index];
}

void Table::setBoard(Card card, int index) {
	board[index] = card;
}

float Table::getBank() {
	return bank;
}

void Table::addBank(float cash) {
	bank += cash;
}

Player** Table::getAllPlayers() {
	return seats;
}

Player* Table::getPlayer(int index) {
	return seats[index];
}

void Table::addPlayer(Player* player, int index) {
	seats[index] = player;
}

void Table::removePlayer(int index) {
	seats[index] = 0;
}

int Table::getBtnPos() {
	return btnPos;
}

void Table::moveBtn() {
	btnPos = (btnPos + 1) % 8;
}