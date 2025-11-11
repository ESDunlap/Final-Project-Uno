#pragma once
#include <iostream> //Generic c++
#include <vector>

#include "Deck.h"

using namespace std;

class Player
{
private:
	vector<Card*> hand;
	int size;
public: 
    Card* lastPlayedCard;
	int getSize() { return size; }
	void giveCard(Deck&);
	int decideCard(BasicCard lastCard); // Overloaded
	bool findCardType(int type, int suit, int& spot);
	void playCard(int, Deck&);
	~Player();
};
