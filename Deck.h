#pragma once
#include <iostream> //Generic c++
#include <vector>
#include <string>

using namespace std;
class Deck;

class Card
{
protected:
	int rank; //-3,-2,-1, 0-9
	int suit; //wild, red, green, yellow, blue
public:
	int getRank() { return rank; }
	int getSuit() { return suit; }
	virtual bool getPlus() { return false; }
};

class BasicCard : public Card
{
private:
	bool plus;
public:
	BasicCard(int, string, bool= false);
	BasicCard(int, int, bool= false);
	bool getPlus(){return plus;}
};

class WildCard : public Card
{
private:
	bool plus;
	rank = -1;
	suit = -1;
	string chosenSuit;
public:
	WildCard(bool plus=false){this->plus = plus;}
	bool getPlus() { return plus; }
	string getChosenSuit() { return chosenSuit; }
};

class ReverseCard : public Card
{
private:
	rank = -2;
public:
	ReverseCard(int suit){this->suit = suit;}
};

class WildCard : public Card
{
private:
	rank = -3;
public:
	SkipCard(int suit){this->suit = suit;}
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
	bool onPlay(Card*);
	~Deck();
};


BasicCard* makeBasicCard(int rank, int suit, bool plus = false);

WildCard* makeWildCard(bool plus = false);
