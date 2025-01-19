#include <vector>
#include <algorithm>
#include <iostream>
#include "Player.h"

float Player::fold() {
	hand[0] = Card();
	hand[1] = Card();
	float b = bet;
	bet = -1;
	return b;
}

void Player::check() {
	bet = 0;
}


void Player::call(float genBet) {
	float diff = genBet - bet;
	if (cash > diff) {
		bet += diff;
		cash -= diff;
	}
	else {
		bet += cash;
		cash = 0;
	}
}
void Player::raise(float size) {
	if (cash > size) {
		bet += size;
		cash -= size;
	}
	else {
		bet += cash;
		cash = 0;
	}
}

// card power
int cp(char c) {
	char values[] = {'x', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
	auto ptr = std::find(std::begin(values), std::end(values), c);
	return ptr - values;
}

bool comp(Card& c1, Card& c2) {
	if (c1.getValue() != c2.getValue())
		return cp(c1.getValue()) > cp(c2.getValue());
	else
		return c1.getSuit() > c2.getSuit();
}

bool flushComp(Card& c1, Card& c2) {
	return c1.getSuit() < c2.getSuit();
}

int Player::checkCombo(Card* board) {
	std::vector<Card> combo = { hand[0], hand[1] };
	for (int i = 0; i < 5; i++)
		combo.push_back(board[i]);
	std::sort(combo.begin(), combo.end(), comp);


	int pair = 0, triple = 0, quad = 0, strIndex = -1;
	int maxPair = 0, maxTriple = 0, maxQuad = 0;
	int flush[] = { 0, 0, 0, 0 };  // [ S, C, H, D ]

	for (int i = 0; i < 7; i++) {
		// pairs and triple
		if (combo[i].getValue() == combo[(i + 1) % 7].getValue()) {
			if (combo[(i + 1) % 7].getValue() == combo[(i + 2) % 7].getValue()) {
				if (combo[(i + 2) % 7].getValue() == combo[(i + 3) % 7].getValue()) {
					quad++;
					maxQuad = cp(combo[i].getValue());
				}
				else if (combo[(i + 7 - 1) % 7].getValue() != combo[i].getValue()) {
					triple++;
					maxTriple = cp(combo[i].getValue()) > maxTriple ? cp(combo[i].getValue()) : maxTriple;
				}
			}
			else if (combo[(i + 7 - 1) % 7].getValue() != combo[i].getValue()) {
				pair++;
				maxPair = cp(combo[i].getValue()) > maxPair ? cp(combo[i].getValue()) : maxPair;
			}
		}

		// straight
		if (strIndex == -1)
			if (cp(combo[i].getValue()) - cp(combo[(i + 1) % 7].getValue()) == 1)
				if (cp(combo[(i + 1) % 7].getValue()) - cp(combo[(i + 2) % 7].getValue()) == 1)
					if (cp(combo[(i + 2) % 7].getValue()) - cp(combo[(i + 3) % 7].getValue()) == 1)
						if (cp(combo[(i + 3) % 7].getValue()) - cp(combo[(i + 4) % 7].getValue()) == 1)
							strIndex = i;

		// flush
		if (combo[i].getSuit() == 's') flush[0]++;
		else if (combo[i].getSuit() == 'c') flush[1]++;
		else if (combo[i].getSuit() == 'h') flush[2]++;
		else flush[3]++;
	}



	
	int maxFlush = *std::max_element(std::begin(flush), std::end(flush));

	if (maxFlush >= 5 and strIndex >= 0) {
		if (combo[strIndex].getSuit() == combo[strIndex + 1].getSuit())
			if (combo[strIndex].getSuit() == combo[strIndex + 2].getSuit())
				if (combo[strIndex].getSuit() == combo[strIndex + 3].getSuit())
					if (combo[strIndex].getSuit() == combo[strIndex + 4].getSuit()) {
						int straight = 0;
						straight += cp(combo[strIndex].getValue());
						straight += cp(combo[strIndex + 1].getValue());
						straight += cp(combo[strIndex + 2].getValue());
						straight += cp(combo[strIndex + 3].getValue());
						straight += cp(combo[strIndex + 4].getValue());
						//std::cout << "STRAIGHT FLUSH!!!!" << std::endl;
						return 510 + straight;  // 510+
					}
	}
	else if (quad > 0) {
		//std::cout << "FOUR OF A KIND!!!!" << std::endl;
		return 490 + maxQuad;  // 490-503
	}
	else if ((triple == 1 and pair == 1) or triple == 2) {
		//std::cout << "FULL HAUSE!!!!" << std::endl;
		return 280 + 15 * maxTriple + maxPair;  // 280-487

	}
	else if (maxFlush >= 5) {
		//std::cout << "FLUSH!!!!" << std::endl;
		std::sort(combo.begin(), combo.end(), flushComp);
		int sumFlush = 0;
		for (int i = 0; i < 5; i++)
			if (cp(combo[i].getSuit()) == cp(combo[i + 1].getSuit()))
				if (cp(combo[i].getSuit()) == cp(combo[i + 2].getSuit())) {
					sumFlush += cp(combo[i].getValue());
					sumFlush += cp(combo[i + 1].getValue());
					sumFlush += cp(combo[i + 2].getValue());
					sumFlush += cp(combo[i + 3].getValue());
					sumFlush += cp(combo[i + 4].getValue());
					break;
				}
		return 220 + sumFlush;  // 220-275
	}
	else if (strIndex >= 0) {
		int straight = 0;
		straight += cp(combo[strIndex].getValue());
		straight += cp(combo[strIndex + 1].getValue());
		straight += cp(combo[strIndex + 2].getValue());
		straight += cp(combo[strIndex + 3].getValue());
		straight += cp(combo[strIndex + 4].getValue());
		//std::cout << "STRAIGHT!!!! " << straight << std::endl;
		return 160 + straight;  // 160-215
	}
	else if (triple > 0) {
		//std::cout << "THREE OF A KIND!!!!" << std::endl;
		int highCard = 0;
		if (cp(combo[0].getValue()) == maxTriple)
			highCard = cp(combo[3].getValue());
		else
			highCard = cp(combo[0].getValue());
		return 130 + maxTriple + highCard;  // 130-155
	}
	else if (pair >= 2) {
		//std::cout << "TWO PAIR!!!!" << std::endl;
		int highCard = 0, secPair = 0, k = 0;
		for (int i = 0; i < 6; i++) {
			if (combo[i].getValue() == combo[i + 1].getValue()) {
				if (k == 1) secPair = cp(combo[i].getValue());
				else k++;
			}
			else if (cp(combo[i].getValue()) > highCard)
				highCard = cp(combo[i].getValue());
		}
		return 90 + maxPair + secPair + highCard;  // 90-126
	}
	else if (pair == 1) {
		//std::cout << "PAIR WWWWWW!!!!" << std::endl;
		int highCard = 0;
		if (cp(combo[0].getValue()) == maxPair)
			highCard = cp(combo[2].getValue());
		else
			highCard = cp(combo[0].getValue());
		return 60 + maxPair + highCard;  // 60-85
	}
	else {
		//std::cout << "nothing L" << std::endl;
		int sum = 0;
		sum += cp(combo[0].getValue());
		sum += cp(combo[1].getValue());
		sum += cp(combo[2].getValue());
		sum += cp(combo[3].getValue());
		sum += cp(combo[4].getValue());
		return sum;  // 1-55
	}
}

std::string Player::getName() {
	return name;
}

void Player::setName(std::string name) {
	this->name = name;
}

Card Player::getHand(int i) {
	return hand[i];
}

void Player::setHand(Card card, int index) {
	this->hand[index] = card;
}

float Player::getCash() {
	return cash;
}

void Player::setCash(float cash) {
	this->cash = cash;
}

float Player::getBet() {
	return bet;
}

float Player::takeBet() {
	float b = bet;
	bet = 0;
	return b;
}