#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions
#include <iostream>
#include <fstream>


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

void Deck::fillDeck()
{
	//number cards
	for(int rank = 0; rank < 10; rank++)
	{
		for(int color = 0; color < 4; color++)
		{
			cards[color + rank * 4] = BasicCard(rank, color + 1);
			if (rank != 0)
				cards[40 + color + (rank - 1) * 4] = BasicCard(rank, color + 1);
		}
	}
	//plus cards
	for(int color = 0; color < 4; color++)
	{
		cards[76 + color] = BasicCard(2, color + 1, true);
		cards[80 + color] = BasicCard(2, color + 1, true);
	}
	//wild cards
	for(int wildNumber = 0; wildNumber < 4; wildNumber++)
	{
		cards[84 + wildNumber] = WildCard();
		cards[88 + wildNumber] = WildCard(true);
	}
};

void Deck::shuffle()
{
	Card shuffledCards[numCards];
	int alreadyChosenSlots[numCards];
	int chosenSlot;
	bool slotChosen = false;
	bool alreadyBeenChosen = false;
	int slots;
	for(int chosenCard= 0; chosenCard < numCards; chosenCard++)
	{
		do
		{
			chosenSlot= rand() % numCards;
			for(int alreadyChosen: alreadyChosenSlots)
			{
				if (chosenSlot == alreadyChosen)
				{
					alreadyBeenChosen= true;
				}
			}
			if(alreadyBeenChosen==false)
			{
				shuffledCards[chosenSlot] = cards[chosenCard];
				alreadyChosenSlots[chosenCard]= chosenSlot;
				slotChosen= true;
			}
			alreadyBeenChosen= false;

		}
		while(slotChosen== false);
		slotChosen=false;
	}
	for(int randomSpot = 0; randomSpot < numCards; randomSpot++)
	{
		cards[randomSpot]= shuffledCards[randomSpot];
	}
	for(int alreadyChosen: alreadyChosenSlots)
	{
		cout<<alreadyChosen<<endl;
	}
}

int main()
{
	srand(time(0));
	Deck newDeck(88);
	newDeck.fillDeck();
	newDeck.shuffle();
	return 0;
}
