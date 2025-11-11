#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector> //vectors
#include <bits/stdc++.h> //for random_shuffle() https://www.geeksforgeeks.org/cpp/how-to-shuffle-a-vector-in-cpp/

//Clear found by https://www.geeksforgeeks.org/cpp/vector-clear-in-cpp-stl/
//Erase found by https://www.w3schools.com/cpp/trycpp.asp?filename=demo_ref_vector_erase

#include "Deck.h"

using namespace std;

BasicCard::BasicCard(int rank, string suit, bool plus)
{
 	this->rank = rank;
 	if(suit=="red")
		this->suit = 1;
	else if(suit=="green")
		this->suit = 2;
	else if(suit=="yellow")
		this->suit = 3;
	else
		this->suit = 4;
	this->plus = plus;   
}

BasicCard::BasicCard(int rank, int suit, bool plus)
{
	this->rank = rank;
	this->suit = suit;
	this->plus = plus;
}

BasicCard* makeBasicCard(int rank, int suit, bool plus)
{
    BasicCard* theCard= new BasicCard(rank, suit, plus);
    return theCard;
}

bool BasicCard::onPlay(Deck& d)
{
    cout<<d.playPile[0]->getRank()<<endl;//debug
    cout<<d.playPile[0]->getSuit()<<endl;//debug
    if((getRank()==d.playPile[0]->getRank())||(getSuit()==d.playPile[0]->getSuit()))
    {
        return true;
    }
    return false;
}

WildCard* makeWildCard(bool plus)
{
    WildCard* theCard= new WildCard(plus);
    return theCard;
}

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

void Deck::shuffle()
{
    random_shuffle(cards.begin(), cards.end());
    cout<<"Shuffle Shuffle Shuffle"<<endl; //debug
}

Card* Deck::drawTop()
{
    if(cards.empty())
    {
        cards= playPile;
        shuffle();
        playPile.clear();
    }
    Card* topCard = cards[0];
    cards.erase(cards.begin());
    cout<<topCard->getRank()<<endl; //debug
    return topCard;
}

Deck::~Deck()
{
    for(Card* card: cards)
    {
        delete card;
    }
    for(Card* card: playPile)
    {
        delete card;
    }
    
}

void Deck::startGame()
{
    fillDeck();
    shuffle();
    playPile.push_back(drawTop());
}



