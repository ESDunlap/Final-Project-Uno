#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions
#include <vector>

#include "Deck.h"
#include "Player.h"

using namespace std;

void Player::giveCard(Deck& d)
{
	Card* newCard= d.drawTop();
	hand.push_back(newCard);
	size++;
}

/*
	Priorities

	Top Card	Next CC		Prev CC		Cross CC	Decision List (draw ends each list)

	basic -		1-2			1-2			1-2			{basic+, wild+, wild, skip, rev, basic}
	wild -								3+			{basic+, skip, wild+, wild, rev, basic}

							3+			1-2			{basic+, rev, wild+, wild, skip, basic}
										3+			{basic+, skip, rev, wild+, wild, basic}


				3+			1-2			1-2			{basic, basic+, wild, wild+, skip, rev}
										3+			{basic, basic+, wild, skip, wild+, rev}

							3+			1-2			{basic, basic+, rev, wild, wild+, skip}
										3+			{basic, basic+, wild, skip, rev, wild+}

	basic+ -	any			any			any			{basic+, (rules) wild+}

	wild+ -		any			any			any			{(rules) basic+, wild+}

	reverse -	1-2			1-2			1-2			{basic+, wild+, wild, skip, rev, basic}
										3+			{basic+, skip, wild+, wild, rev, basic}

							3+			1-2			{basic+, rev, wild+, wild, skip, basic}
										3+			{basic+, rev, skip, wild+, wild, basic}


				3+			1-2			1-2			{basic, basic+, wild, wild+, skip, rev}
										3+			{basic, basic+, wild, skip, wild+, rev}

							3+			1-2			{basic, rev, basic+, wild, wild+, skip}
										3+			{basic, rev, basic+, wild, skip, wild+}

	skip -		1-2			1-2			1-2			{basic+, wild+, wild, skip, rev, basic}
										3+			{basic+, skip, wild+, wild, rev, basic}

							3+			1-2			{basic+, rev, wild+, wild, skip, basic}
										3+			{basic+, skip, rev, wild+, wild, basic}


				3+			1-2			1-2			{basic, basic+, wild, wild+, skip, rev}
										3+			{basic, skip, basic+, wild, wild+, rev}

							3+			1-2			{basic, basic+, rev, wild, wild+, skip}
										3+			{basic, skip, basic+, wild, rev, wild+}

*/
int Player::decideCard(Card* lastCard, int nextPlayer, int crossPlayer, int previousPlayer)
{
	int location = -1;
	int priority[6] = { 3, 3, 3, 3, 3, 3 }; //Moved as it said it was out of scope before
	/*
	if (lastCard->getPlus()) // + Check
	{
		if (lastCard->getRank() == Wild)// Wild Check
		{
			if (findCardType(WildP, lastCard->getSuit(), location))
			{
				return location;
			}
		}
		else // Basic
		{
			if (findCardType(BasicP, lastCard->getSuit(), location))
			{
				return location;
			}
		}
	}*/
	if(true)
	{
		if (nextPlayer<=2) // Next Player On Low Cards
		{
			priority[0] = BasicP;
			priority[5] = Basic;
			if (previousPlayer<=2) // Previous Player On Low Cards
			{
				priority[4] = Reverse;
				if (crossPlayer<=2) // Cross Player On Low Cards
				{
					priority[1] = WildP;
					priority[2] = Wild;
					priority[3] = Skip;
				}
				else // Cross Player Not On Low Cards
				{
					priority[1] = Skip;
					priority[2] = WildP;
					priority[3] = Wild;
				}
			}
			else // Previous Player Not On Low Cards
			{
				if (crossPlayer<=2) // Cross Player On Low Cards
				{
					priority[1] = Reverse;
					priority[2] = Wild;
					priority[3] = WildP;
					priority[4] = Skip;
				}
				else // Cross Player Not On Low Cards
				{
					if (lastCard->getRank() == Reverse) // Last Card Was Reverse
					{
						priority[1] = Reverse;
						priority[2] = Skip;
					}
					else
					{
						priority[1] = Skip;
						priority[2] = Reverse;
					}
					priority[3] = Wild;
					priority[4] = WildP;
				}
			}
		}
		else // Next Player Not On Low Cards
		{
			priority[0] = Basic;
			if (previousPlayer<=2) // Previous Player On Low Cards
			{
				priority[5] = Reverse;
				if (crossPlayer<=2) // Cross Player On Low Cards
				{
					priority[1] = BasicP;
					priority[2] = Wild;
					priority[3] = WildP;
					priority[4] = Skip;
				}
				else // Cross Player Not On Low Cards
				{
					if (lastCard->getRank() == Skip) // Last Card Was Skip
					{
						priority[1] = Skip;
						priority[2] = BasicP;
						priority[3] = Wild;
					}
					else
					{
						priority[1] = BasicP;
						priority[2] = Wild;
						priority[3] = Skip;
					}
					priority[4] = WildP;
				}
			}
			else // Previous Player Not On Low Cards
			{
				if (crossPlayer<=2) // Cross Player On Low Cards
				{
					if (lastCard->getRank()== Reverse) // Last Card Was Reverse
					{
						priority[1] = Reverse;
						priority[2] = BasicP;
					}
					else
					{
						priority[1] = BasicP;
						priority[2] = Reverse;
					}
					priority[3] = Wild;
					priority[4] = WildP;
					priority[5] = Skip;
				}
				else // Cross Player Not On Low Cards
				{
					if (lastCard->getRank() == Reverse) // Last Card Was Reverse
					{
						priority[1] = Reverse;
						priority[2] = BasicP;
						priority[3] = Wild;
						priority[4] = Skip;
					}
					else if(lastCard->getRank() == Skip)
					{
						priority[1] = Skip;
						priority[2] = BasicP;
						priority[3] = Wild;
						priority[4] = Reverse;
					}
					else
					{
						priority[1] = BasicP;
						priority[2] = Wild;
						priority[3] = Skip;
						priority[4] = Reverse;
					}
					priority[5] = WildP;
				}
			}
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (findCardType(priority[i], lastCard->getSuit(), location))
		{
			return location;
		}
	}
	cout<<"No Valid Card"<<endl;
	return -1; //Draw
}

bool Player::findCardType(int type, int suit, int& spot)
{
	for (int i = 0; i < size; i++)
	{
		if (hand[i]->getSuit() == -1 || hand[i]->getSuit() == suit)
		{

			switch (type)
			{
			case Basic: // Basic Card
				if (!hand[i]->getPlus()) // NonPlus variant
				{
					if (hand[i]->getRank() != Wild && hand[i]->getRank() != Reverse && hand[i]->getRank() != Skip) // Not Wild, Reverse, or Skip
					{
						spot = i;
						return true;
					}
				}
				break;
			case BasicP: // Basic+ Card
				if (hand[i]->getPlus()) // Plus variant
				{
					if (hand[i]->getRank() != Wild && hand[i]->getRank() != Reverse && hand[i]->getRank() != Skip) // Not Wild, Reverse, or Skip
					{
						spot = i;
						return true;
					}
				}
				break;
			case Wild: // Wild Card
				if (!hand[i]->getPlus()) // NonPlus variant
				{
					if (hand[i]->getRank() == Wild) // Wild
					{
						spot = i;
						return true;
					}
				}
				break;
			case WildP: // Wild+ Card
				if (hand[i]->getPlus()) // Plus variant
				{
					if (hand[i]->getRank() == Wild) // Wild
					{
						spot = i;
						return true;
					}
				}
				break;
			case Reverse: // Reverse Card
				if (hand[i]->getRank() == Reverse) // Reverse
				{
					spot = i;
					return true;
				}
				break;
			case Skip: // Skip Card
				if (hand[i]->getRank() == Skip) // Skip
				{
					spot = i;
					return true;
				}
				break;
			}

		}
	}
	return false; //Added so I can compile it change later
}

bool Player::playCard(int c, Deck& d, bool& reverse, bool& skip, bool& plus)
{
	Card* play = hand[c];
	if(d.onPlay(play))
	{
		switch(play->getRank())
		{
		case -1:
		{
			int newColor;
			bool colorChosen=false;
			if(!AiPlayer)
			{
				while(!colorChosen)
				{
					cout<<"What color are you playing it as?"<<endl;
					cout<<"(1 Red, 2 Green, 3 Yellow, 4 Blue)"<<endl;
					newColor=getValidInt("What color are you playing it as?");
					if(newColor<5 && newColor>0)
					{
						play->changeWild(newColor);
						colorChosen=true;
					}
					else
					{
						cout<<"Invalid Input"<<endl;
					}
				}
			}
			else
			{
			    colorChosen=rand() % 4 + 1;
			    play->changeWild(colorChosen);
			}
			break;
		}
		case -2:
		{
			cout<<"Turn Order Reversed!"<<endl;
			reverse=true;
			break;
		}
		case -3:
		{
			skip=true;
			break;
		}
		}
		if(play->getPlus())
		{
			plus=true;
		}
		hand.erase(hand.begin() + c);
		size--;
		return true;
	}
	else
	{
		cout<<"Invalid Card"<<endl;
		return false;
	}
}

void Player::playTurn(bool& reverse, bool& skip, bool& plus, Deck& d,
                      int nextPlayer, int crossPlayer, int previousPlayer)
{
	if(skip)
	{
		skip=false;
		return;
	}
	else if(plus)
	{
	    cout<<"Forced to Draw"<<endl;
		if (d.playPile[0]->getRank()==-1)
		{
			giveCard(d);
			giveCard(d);
			giveCard(d);
			giveCard(d);
		}
		else
		{
			giveCard(d);
			giveCard(d);
		}
		plus=false;
		return;
	}
	else if (AiPlayer==false)
	{
		for(int i = 0; i < size; i++)
		{
			cout<<"Card: "<<i<<endl;
			cout<<"Rank: "<<hand[i]->getRank()<<endl;
			cout<<"Suit: "<<hand[i]->getSuit()<<endl; //Replace these later
			cout<<"Plus: "<<hand[i]->getPlus()<<endl<<endl;
		}
		cout<<"Top Rank: "<<d.playPile[0]->getRank()<<endl; //debug
		cout<<"Top Suit: "<<d.playPile[0]->getSuit()<<endl; //debug
		cout<<"Plus Card: "<<d.playPile[0]->getPlus()<<endl;//debug
		int playedCardNum;
		bool cardPlayed=false;
		while(!cardPlayed)
		{
			playedCardNum= getValidInt("Which card would you like to play? (Enter -1 to draw)");
			if (playedCardNum>=size||playedCardNum<-1)
				cout<<"Invalid Card/Input"<<endl;
			else if(playedCardNum==-1)
				giveCard(d);
			else if(playCard(playedCardNum, d, reverse, skip, plus))
				cardPlayed=true;
		}
	}
	else
	{
		int playedCardNum;
		bool cardPlayed=false;
		while(!cardPlayed)
		{
			playedCardNum= decideCard(d.playPile[0], nextPlayer, crossPlayer, previousPlayer);
			if(playedCardNum==-1)
				giveCard(d);
			else if(playCard(playedCardNum, d, reverse, skip, plus))
			{
				cardPlayed=true;
			}
		}
	}
}

Player::~Player()
{
	for(Card* card: hand)
	{
		delete card;
		cout<<"Deleted a card"<<endl;
	}
}
