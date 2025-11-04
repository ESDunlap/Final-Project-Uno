#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector> //vectors
#include <bits/stdc++.h> //for random_shuffle() https://www.geeksforgeeks.org/cpp/how-to-shuffle-a-vector-in-cpp/


using namespace std;

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
	int getRank() {
		return rank;
	}
	string getSuit() {
		return suit;
	}
	bool getPlus() {
		return plus;
	}
	void onPlay();

};

class WildCard : public Card
{
private:
	bool plus;
public:
	WildCard(bool plus = false)
	{
		this->plus = plus;
	}
};

BasicCard* makeBasicCard(int rank, int suit, bool plus = false)
{
    BasicCard* theCard= new BasicCard(rank, suit, plus);
    return theCard;
}

WildCard* makeWildCard(bool plus = false)
{
    WildCard* theCard= new WildCard(plus);
    return theCard;
}

class Deck
{
private:
	vector<Card*> cards;
	int numCards;
public:
	void fillDeck();
	void shuffle()
	{
	    random_shuffle(cards.begin(), cards.end());
	};
	bool draw(int);
	~Deck();
};

void Deck::fillDeck()
{
	//number cards
	for(int rank = 0; rank < 10; rank++)
	{
		for(int color = 0; color < 4; color++)
		{
			cards.push_back(makeBasicCard(rank, color + 1));
			if (rank != 0)
				cards.push_back(makeBasicCard(rank, color + 1));
		}
	}
	//plus cards
	for(int color = 0; color < 4; color++)
	{
		cards.push_back(makeBasicCard(2, color + 1, true));
		cards.push_back(makeBasicCard(2, color + 1, true));
	}
	//wild cards
	for(int wildNumber = 0; wildNumber < 4; wildNumber++)
	{
		cards.push_back(makeWildCard());
		cards.push_back(makeWildCard(true));
	}
};

Deck::~Deck()
{
    for(Card* card: cards)
    {
        delete card;
    }
}

int main()
{
	srand(time(0));
	Deck newDeck;
	newDeck.fillDeck();
	newDeck.shuffle();
	return 0;
}
