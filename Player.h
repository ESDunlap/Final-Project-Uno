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
	void giveCard(Card& c);
	Card playCard(int c);
};