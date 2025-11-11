#pragma once
#include <iostream> //Generic c++
#include <vector>
#include <string>

using namespace std;

class Card
{
public:
    virtual int getRank(){return 0;}
    virtual int getSuit(){return 0;}
	virtual bool onPlay(){return false;}
};

class WildCard : public Card
{
private:
	bool plus;
	int rank = -1;
	int suit = -1;
	string chosenSuit;
public:
	WildCard(bool plus=false){this->plus = plus;}
	bool getPlus() { return plus; }
	int getRank() { return rank; }
	int getSuit() { return suit; }
	string getChosenSuit() { return chosenSuit; }
};

class Deck
{
private:
	int numCards;
public:
	vector<Card*> cards;
	vector<Card*> playPile;
    friend class Card; //fix later
	void fillDeck();
	void shuffle();
	void startGame();
	Card* drawTop();
	~Deck();
};

class BasicCard : public Card
{
private:
	int rank; //0=0, 1=1...
	int suit; //red, green, yellow, blue
	bool plus;
public:
	BasicCard(int, string, bool= false);
	BasicCard(int, int, bool= false);
	int getRank(){return rank;}
	int getSuit(){return suit;}
	bool getPlus(){return plus;}
	bool onPlay(Deck&);
};

BasicCard* makeBasicCard(int rank, int suit, bool plus = false);

WildCard* makeWildCard(bool plus = false);
