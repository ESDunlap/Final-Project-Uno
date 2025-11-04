#pragma once
#include <iostream> //Generic c++
#include <vector>

#include "Deck.h"

using namespace std;

class Card
{
public:
	void virtual onPlay();
};

class BasicCard : public Card
{
private:
	int rank; //0=0, 1=1...
	string suit; //red, green, yellow, blue
	bool plus;
public:
	BasicCard(int rank, string suit, bool plus = false);
	BasicCard(int rank, int suit, bool plus = false);
	int getRank();
	string getSuit();
	bool getPlus();
	void onPlay();
};

class WildCard : public Card
{
private:
	bool plus;
public:
	WildCard(bool plus = false);
};

class Deck
{
private:
	Card* cards;
	int numCards;
public:
	Deck(int size);
	void fillDeck();
	void shuffle();
	bool draw(int);
};
