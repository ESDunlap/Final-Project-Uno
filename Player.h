#pragma once
#include <iostream> //Generic c++
#include <vector>

#include "Deck.h"

#define Basic 1 // Any Value
#define BasicP 2 // Any Value
#define Wild -1 // Same as Rank
#define WildP 0 // Any Value
#define Reverse -2 // Same as Rank
#define Skip -3 // Same as Rank

using namespace std;

class Player
{
private:
	vector<Card*> hand;
	int size = 0;
public: 
    Card* lastPlayedCard;
	int getSize() { return size; }
	void giveCard(Deck&);
	int decideCard(BasicCard lastCard); // Overloaded
	bool findCardType(int type, int suit, int& spot);
	void playCard(int, Deck&);
	~Player();
};
