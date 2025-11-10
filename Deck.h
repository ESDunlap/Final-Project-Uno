#pragma once
#include <iostream> //Generic c++
#include <vector>
#include <string>

using namespace std;

class Card
{
public:
    virtual int getRank(){return 0;}
	void virtual onPlay();
};

class BasicCard : public Card
{
private:
	int rank; //0=0, 1=1...
	string suit; //red, green, yellow, blue
	bool plus;
public:
	BasicCard(int, string, bool= false);
	BasicCard(int, int, bool= false);
	int getRank(){return rank;}
	string getSuit(){return suit;}
	bool getPlus(){return plus;}
	void onPlay(){};
};

class WildCard : public Card
{
private:
	bool plus;
	int rank = -1;
public:
	WildCard(bool plus=false){this->plus = plus;}
	bool getPlus(){return plus;}
	int getRank(){return rank;}
};

class Deck
{
private:
	vector<Card*> cards;
	vector<Card*> playPile;
	int numCards;
public:
	void fillDeck();
	void shuffle();
	Card* drawTop();
	~Deck();
};

BasicCard* makeBasicCard(int rank, int suit, bool plus = false);

WildCard* makeWildCard(bool plus = false);
