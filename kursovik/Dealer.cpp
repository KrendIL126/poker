#include <vector>
#include <iostream>
#include <conio.h>
#include "Dealer.h"

//void Dealer::giveCard(Player* p) {
//	Card c = deck.getCard(0);
//	p->setHand(c, 0)
//}

bool isEqualBets(Player** players, float genBet) {
	int p = 0, eq = 0;
	for (int i = 0; i < 8; i++)
		if (players[i]->getName() != "0") {
			p++;
			if (players[i]->getBet() == genBet or players[i]->getBet() == -1)
				eq++;
		}
	if (eq == p) return true;
	else return false;
}

void Dealer::goPreflop() {
	deck.reload();
	deck.shuffle();
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 8; i++) 
			if (table->getPlayer(i)->getName() != "0") {
				table->getPlayer(i)->setHand(deck.getCard(0), j);
				deck.addCounter();
			}
	}

	// blinds 
	float BB = 10, genBet = BB;  // big blind
	int btn = table->getBtnPos(), btn2 = 0;
	for (int i = 0; i < 8; i++) {
		if (table->getPlayer((btn + 1 + i) % 8)->getName() != "0") {
			table->getPlayer((btn + 1 + i) % 8)->call(BB / 2);
			for (int j = 0; j < 7; j++)
				if (table->getPlayer((btn + 1 + i + 1 + j) % 8)->getName() != "0") {
					table->getPlayer((btn + 1 + i + 1 + j) % 8)->call(BB);
					btn2 = (btn + i + j + 3) % 8;
					break;
				}
			break;
		}
	}
	
	// bets
	Player *p;
	char choice;
	float size;
	int ok = 1;
	while (isEqualBets(table->getAllPlayers(), genBet) == 0) {
		for (int i = 0; i < 8; i++) {
			p = table->getPlayer( (btn2 + i) % 8);
			if (p->getName() != "0")
				if (p->getBet() >= 0) {
					system("cls");
					std::cout << "PREFLOP\n" << std::endl;
					std::cout << p->getName() << "'s turn.\n(Press any button)" << std::endl;
					while (getchar() != '\n');
					getchar();
					system("cls");
					ok = 1;
					while (ok) {
						std::cout << p->getName() << std::endl;
						std::cout << "Board: ";
						table->printBoard();
						std::cout << "Your hand: ";
						p->getHand(0).print();
						p->getHand(1).print();
						std::printf("\n\nGeneral Bet: %g\n", genBet);
						std::printf("You have: %g\n", p->getCash());
						std::printf("Your Bet: %g\n", p->getBet());
						std::printf("\n\nAnd your choice is?\n1-check;\n2-fold;\n3-call;\n4-raise\n");
						std::cin >> choice;
						if (choice == '1' and (genBet == 0 or genBet == p->getBet())) {
							//p->check();
							ok = 0;
						}
						else if (choice == '2') {
							bank += p->fold();
							ok = 0;
						}
						else if (choice == '3') {
							if (genBet > (p->getCash() + p->getBet())) 
								bank += p->fold();
							else
								p->call(genBet);  // if bet >= genBet
							ok = 0;
						}
						else if (choice == '4') {
							std::printf("how much do you want to raise the bet?\n");
							std::cin >> size;
							if (size > p->getCash()) size = p->getCash() - (genBet - p->getBet());
							p->raise(size + (genBet - p->getBet()));
							genBet += size;
							ok = 0;
						}
						system("cls");
					}
					
				}
		}
	}

	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				bank += table->getPlayer(i)->takeBet();
		

	std::cout << "CLOSED\nPREFLOP BANK:  " << bank << std::endl;
	while (getchar() != '\n');
	getchar();
	system("cls");
}

void Dealer::goFlop() {
	table->setBoard(deck.getCard(0), 0);
	deck.addCounter();
	table->setBoard(deck.getCard(0), 1);
	deck.addCounter();
	table->setBoard(deck.getCard(0), 2);
	deck.addCounter();

	// bets
	float genBet = 0;  // big blind
	Player* p;
	char choice;
	float size;
	int ok = 1, k = 0, btn = table->getBtnPos() + 1;

	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				k++;
	if (k == 1) ok = 0;

	while (isEqualBets(table->getAllPlayers(), genBet) == 0 or ok == 1) {
		for (int i = 0; i < 8; i++) {
			p = table->getPlayer((btn + i) % 8);
			if (p->getName() != "0")
				if (p->getBet() >= 0) {
					system("cls");
					std::cout << "FLOP\n" << std::endl;
					std::cout << p->getName() << "'s turn.\n(Press any button)" << std::endl;
					while (getchar() != '\n');
					getchar();
					system("cls");
					ok = 1;
					while (ok) {
						std::cout << p->getName() << std::endl;
						std::cout << "Board: ";
						table->printBoard();
						std::cout << "Your hand: ";
						p->getHand(0).print();
						p->getHand(1).print();
						std::printf("\n\nGeneral Bet: %g\n", genBet);
						std::printf("You have: %g\n", p->getCash());
						std::printf("Your Bet: %g\n", p->getBet());
						std::printf("\n\nAnd your choice is?\n1-check;\n2-fold;\n3-call;\n4-raise\n");
						std::cin >> choice;
						if (choice == '1' and (genBet == 0 or genBet == p->getBet())) {
							//p->check();
							ok = 0;
						}
						else if (choice == '2') {
							bank += p->fold();
							ok = 0;
						}
						else if (choice == '3') {
							if (genBet > (p->getCash() + p->getBet()))
								bank += p->fold();
							else
								p->call(genBet);  // if bet >= genBet
							ok = 0;
						}
						else if (choice == '4') {
							std::printf("how much do you want to raise the bet?\n");
							std::cin >> size;
							if (size > p->getCash()) size = p->getCash() - (genBet - p->getBet());
							p->raise(size + (genBet - p->getBet()));
							genBet += size;
							ok = 0;
						}
						system("cls");
					}

				}
		}
	}

	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				bank += table->getPlayer(i)->takeBet();


	std::cout << "CLOSED\nFLOP BANK:  " << bank << std::endl;
	while (getchar() != '\n');
	getchar();
	system("cls");
}

void Dealer::goTurn() {
	table->setBoard(deck.getCard(0), 3);
	deck.addCounter();

	// bets
	float genBet = 0;
	Player* p;
	char choice;
	float size;
	int ok = 1, k = 0, btn = table->getBtnPos() + 1;

	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				k++;
	if (k == 1) ok = 0;
	
	while (isEqualBets(table->getAllPlayers(), genBet) == 0 or ok == 1) {
		for (int i = 0; i < 8; i++) {
			p = table->getPlayer((btn + i) % 8);
			if (p->getName() != "0")
				if (p->getBet() >= 0) {
					system("cls");
					std::cout << "TURN\n" << std::endl;
					std::cout << p->getName() << "'s turn.\n(Press any button)" << std::endl;
					while (getchar() != '\n');
					getchar();
					system("cls");
					ok = 1;
					while (ok) {
						std::cout << p->getName() << std::endl;
						std::cout << "Board: ";
						table->printBoard();
						std::cout << "Your hand: ";
						p->getHand(0).print();
						p->getHand(1).print();
						std::printf("\n\nGeneral Bet: %g\n", genBet);
						std::printf("You have: %g\n", p->getCash());
						std::printf("Your Bet: %g\n", p->getBet());
						std::printf("\n\nAnd your choice is?\n1-check;\n2-fold;\n3-call;\n4-raise\n");
						std::cin >> choice;
						if (choice == '1' and (genBet == 0 or genBet == p->getBet())) {
							//p->check();
							ok = 0;
						}
						else if (choice == '2') {
							bank += p->fold();
							ok = 0;
						}
						else if (choice == '3') {
							if (genBet > (p->getCash() + p->getBet()))
								bank += p->fold();
							else
								p->call(genBet);  // if bet >= genBet
							ok = 0;
						}
						else if (choice == '4') {
							std::printf("how much do you want to raise the bet?\n");
							std::cin >> size;
							if (size > p->getCash()) size = p->getCash() - (genBet - p->getBet());
							p->raise(size + (genBet - p->getBet()));
							genBet += size;
							ok = 0;
						}
						system("cls");
					}

				}
		}
	}

	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				bank += table->getPlayer(i)->takeBet();


	std::cout << "CLOSED\nTURN BANK:  " << bank << std::endl;
	while (getchar() != '\n');
	getchar();
	system("cls");
}

void Dealer::goRiver() {
	table->setBoard(deck.getCard(0), 4);
	deck.addCounter();

	// bets
	float genBet = 0;
	Player* p;
	char choice;
	float size;
	int ok = 1, k = 0, btn = table->getBtnPos() + 1;

	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				k++;
	if (k == 1) ok = 0;

	while (isEqualBets(table->getAllPlayers(), genBet) == 0 or ok == 1) {
		for (int i = 0; i < 8; i++) {
			p = table->getPlayer((btn + i) % 8);
			if (p->getName() != "0")
				if (p->getBet() >= 0) {
					system("cls");
					std::cout << "RIVER\n" << std::endl;
					std::cout << p->getName() << "'s turn.\n(Press any button)" << std::endl;
					while (getchar() != '\n');
					getchar();
					system("cls");
					ok = 1;
					while (ok) {
						std::cout << p->getName() << std::endl;
						std::cout << "Board: ";
						table->printBoard();
						std::cout << "Your hand: ";
						p->getHand(0).print();
						p->getHand(1).print();
						std::printf("\n\nGeneral Bet: %g\n", genBet);
						std::printf("You have: %g\n", p->getCash());
						std::printf("Your Bet: %g\n", p->getBet());
						std::printf("\n\nAnd your choice is?\n1-check;\n2-fold;\n3-call;\n4-raise\n");
						std::cin >> choice;
						if (choice == '1' and (genBet == 0 or genBet == p->getBet())) {
							//p->check();
							ok = 0;
						}
						else if (choice == '2') {
							bank += p->fold();
							ok = 0;
						}
						else if (choice == '3') {
							if (genBet > (p->getCash() + p->getBet()))
								bank += p->fold();
							else
								p->call(genBet);  // if bet >= genBet
							ok = 0;
						}
						else if (choice == '4') {
							std::printf("how much do you want to raise the bet?\n");
							std::cin >> size;
							if (size > p->getCash()) size = p->getCash() - (genBet - p->getBet());
							p->raise(size + (genBet - p->getBet()));
							genBet += size;
							ok = 0;
						}
						system("cls");
					}

				}
		}
	}

	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				bank += table->getPlayer(i)->takeBet();


	std::cout << "CLOSED\nRIVER BANK:  " << bank << std::endl;
	while (getchar() != '\n');
	getchar();
	system("cls");
}

void Dealer::showdown() {
	std::vector<Player> players;
	for (int i = 0; i < 8; i++)
		if (table->getPlayer(i)->getName() != "0")
			if (table->getPlayer(i)->getBet() >= 0)
				players.push_back(*table->getPlayer(i));
	int p1, p2;
	Player temp;
	for (int i = 0; i < players.size() - 1; i++) {
		p1 = players[i].checkCombo(table->getBoard());
		p2 = players[i + 1].checkCombo(table->getBoard());
		if (p1 < p2) {
			temp = players[i + 1];
			players[i + 1] = players[i];
			players[i] = temp;
		}
	}
	std::cout << "WINNER: " << players[0].getName() << " and gets " << bank << std::endl;
	for (int i = 0; i < 8; i++) {
		if (table->getPlayer(i)->getName() == players[0].getName()) {
			table->getPlayer(i)->setCash(table->getPlayer(i)->getCash() + bank);
			break;
		}
	}
	bank = 0;
	while (getchar() != '\n');
	getchar();
	system("cls");
}

Deck* Dealer::getDeck() {
	return &deck;
}

Table* Dealer::getTable() {
	return table;
}

void Dealer::setTable(Table* t) {
	table = t;
}

float Dealer::getBank() {
	return bank;
}

void Dealer::addBank(float cash) {
	bank += cash;
}