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
	cout<<newCard->getRank()<<endl; //debug
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
int Player::decideCard(BasicCard lastCard)
{ 
	int location = -1;
	if (lastCard.getPlus()) // + Check
	{
		if (lastCard.getRank() == -1)// Wild Check
		{
			if (findCardType(3, lastCard.getSuit(), location))
			{
				return location;
			}
		}
		else // Basic
		{
			if (findCardType(1, lastCard.getSuit(), location))
			{
				return location;
			}
		}
	}
	else
	{
		int priority[6] = { 3, 3, 3, 3, 3, 3 };
		if (NextPlayerOnLowCard) // Next Player On Low Cards
		{
			priority[0] = BasicP;
			priority[5] = Basic;
			if (PreviousPlayerOnLowCard) // Previous Player On Low Cards
			{
				priority[4] = Reverse;
				if (CrossPlayerOnLowCard) // Cross Player On Low Cards
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
				if (CrossPlayerOnLowCard) // Cross Player On Low Cards
				{
					priority[1] = Reverse;
					priority[2] = Wild;
					priority[3] = WildP;
					priority[4] = Skip;
				}
				else // Cross Player Not On Low Cards
				{
					if (lastCard.getRank() == Reverse) // Last Card Was Reverse
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
			if (PreviousPlayerOnLowCard) // Previous Player On Low Cards
			{
				priority[5] = Reverse;
				if (CrossPlayerOnLowCard) // Cross Player On Low Cards
				{
					priority[1] = BasicP;
					priority[2] = Wild;
					priority[3] = WildP;
					priority[4] = Skip;
				}
				else // Cross Player Not On Low Cards
				{
					if (lastCard.getRank() == Skip) // Last Card Was Skip
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
				if (CrossPlayerOnLowCard) // Cross Player On Low Cards
				{
					if (lastCard.getRank() == Reverse) // Last Card Was Reverse
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
					if (lastCard.getRank() == Reverse) // Last Card Was Reverse
					{
						priority[1] = Reverse;
						priority[2] = BasicP;
						priority[3] = Wild;
						priority[4] = Skip;
					}
					else if(lastCard.getRank() == Skip)
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
		if (findCardType(priority[i], lastCard.getSuit(), location))
		{
			return location;
		}
	}
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

void Player::playCard(int c, Deck& d)
{
	Card* play = hand[c];
	//Errors out right now
	//if(play->onPlay(d));
	//{
    	hand.erase(hand.begin() + c);
    	size--;
    	lastPlayedCard= play;
	//}
}

Player::~Player()
{
    for(Card* card: hand)
    {
        delete card;
        cout<<"Deleted a card"<<endl;
    }
}
