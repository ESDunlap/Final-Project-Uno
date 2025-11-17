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
    void fixWildSuit() {suit=-1;}
	int getRank() const { return rank; }
	int getSuit() const { return suit; }
	virtual void changeWild(int newSuit){};
	virtual bool getPlus() const { return false; }
	virtual string getFileName() const { return (string)"File.txt"; }
};

class BasicCard : public Card
{
private:
	bool plus;
public:
	BasicCard(int, string, bool= false);
	BasicCard(int, int, bool= false);
	bool getPlus() const { return plus; }
	string getFileName() const;
	friend ostream& operator<<(ostream& os, const BasicCard& card);
};

class WildCard : public Card
{
private:
	bool plus;
public:
	WildCard(bool plus=false){this->plus = plus; rank=-1; suit=-1;}
	void changeWild(int newSuit) {suit=newSuit;}
	bool getPlus() const { return plus; }
	string getFileName() const;
	friend ostream& operator<<(ostream& os, const WildCard& card);
};

class ReverseCard : public Card
{
public:
	ReverseCard(int suit){this->suit = suit; rank = -2;}
	string getFileName() const;
	friend ostream& operator<<(ostream& os, const ReverseCard& card);
};

class SkipCard : public Card
{
public:
	SkipCard(int suit){this->suit = suit; rank = -3;}
	string getFileName() const;
	friend ostream& operator<<(ostream& os, const SkipCard& card);
};

class Deck
{
private:
	int numCards;
public:
	vector<Card*> cards;
	vector<Card*> playPile;
	void fillDeck();
	void shuffle();
	void startGame();
	Card* drawTop();
	bool onPlay(Card*);
	~Deck();
	friend ostream& operator<<(ostream& os, const Deck& d);
};


BasicCard* makeBasicCard(int rank, int suit, bool plus = false);

WildCard* makeWildCard(bool plus = false);

ReverseCard* makeReverseCard(int suit);

SkipCard* makeSkipCard(int suit);

int getValidInt(string message);
