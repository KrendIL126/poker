#pragma once

class Bet {
private:
	char choice;
	float size;

public:
	Bet() {
		choice = 'f';
		size = 0;
	}

	Bet(char choice, float size) {
		this->choice = choice;
		this->size = size;
	}

	char getChoice();
	float getSize();
	void setChoice(char c);
	void addSize(float s);
};
