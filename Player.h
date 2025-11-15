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
	bool AiPlayer=false;
public: 
    Card* lastPlayedCard;
	int getSize() { return size; }
	vector<Card*> getHand() { return hand; }
	Card* getCard(int spot) { return hand[spot]; }
	void setAi() { AiPlayer=true; }
	void giveCard(Deck&);
	int decideCard(Card* lastCard, int nextPlayer, int oppositePlayer, int previousPlayer);
	bool findCardType(int type, int suit, int& spot);
	bool playCard(int, Deck&, bool&, bool&, bool&);
	void playTurn(bool&, bool&, bool&, Deck&, int, int, int);
	~Player();
};
