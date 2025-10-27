#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions

using namespace std;

class Deck
{
private:
	Card* cards;
	int numCards;
public:
	Deck(int size)
	{
		cards = new Card[size];
		numCards = size;
	}
	void fillDeck();
	void shuffle();
	bool draw(int);
};

class Card
{
private:

public:

};

class BasicCard : public Card
{
private:
	int rank; //0=0, 1=1...
	string suit; //red, green, yellow, blue
	bool plus;
public:
	BasicCard(int rank, string suit, bool plus = false)
	{
		this->rank = rank;
		this->suit = suit;
		this->plus = plus;
	}
	BasicCard(int rank, int suit, bool plus = false)
	{
		this->rank = rank;
		switch (suit)
		{
		case 1:
			this->suit = "red";
			break;
		case 2:
			this->suit = "green";
			break;
		case 3:
			this->suit = "yellow";
			break;
		case 4:
			this->suit = "blue";
			break;
		}
		this->plus = plus;
	}
	int getRank() { return rank; }
	string getSuit() { return suit; }
	bool getPlus() { return plus; }
	void onPlay();

};

class WildCard : public Card
{
private:
	bool plus;
	WildCard(bool plus = false)
	{
		this->plus = plus;
	}
}
