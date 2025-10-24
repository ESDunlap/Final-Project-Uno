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
	string suit; //purple, green, yellow, blue
public:
	BasicCard(int rank, string suit)
	{
		this->rank = rank;
		this->suit = suit;
	}
	BasicCard(int rank, int suit)
	{
		this->rank = rank;
		switch (suit)
		{
		case 1:
			this->suit = "purple";
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
	}
	int getRank() { return rank; }
	string getSuit() { return suit; }

};