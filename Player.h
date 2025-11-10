#pragma once
#include <iostream> //Generic c++
#include <vector>

#include "Deck.h"

using namespace std;

class Player
{
private:
	vector<Card> hand;
	int size;
public: 
	int getSize() { return size; }
	void giveCard(Card& c);
	int decideCard(BasicCard lastCard); // Overloaded
	bool findCardType(int type, int suit, int& spot);
	Card playCard(int c);
};
