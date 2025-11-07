#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions
#include <vector>

#include "Deck.h"
#include "Player.h"

using namespace std;

void Player::giveCard(Card& c)
{
	hand.push_back(c);
}

/*
	Priorities

	Top Card	Next CC		Prev CC		Cross CC	Decision List (draw ends each list)

	basic -		1-2			1-2			1-2			{basic+, wild+, wild, skip, rev, basic}
	wild -								3+			{basic+, skip, wild+, wild, rev, basic}

							3+			1-2			{basic+, rev, wild+, wild, skip, basic}
										3+			{basic+, skip, rev, wild+, wild, basic}


				3+			1-2			1-2			{basic, b+, wild, wild+, skip, rev}
										3+			{basic, b+, wild, skip, wild+, rev}

							3+			1-2			{basic, b+, rev, wild, wild+, skip}
										3+			{basic, b+, wild, skip, rev, wild+}

	basic+ -	any			any			any			{basic+, (rules) wild+}

	wild+ -		any			any			any			{(rules) basic+, wild+}

	reverse -	1-2			1-2			1-2			{basic+, wild+, wild, skip, rev, basic}
										3+			{basic+, skip, wild+, wild, rev, basic}

							3+			1-2			{basic+, rev, wild+, wild, skip, basic}
										3+			{basic+, rev, skip, wild+, wild, basic}


				3+			1-2			1-2			{basic, b+, wild, wild+, skip, rev}
										3+			{basic, b+, wild, skip, wild+, rev}

							3+			1-2			{basic, rev, b+, wild, wild+, skip}
										3+			{basic, b+, wild, rev, skip, wild+}

	skip -		1-2			1-2			1-2			{basic+, wild+, wild, skip, rev, basic}
										3+			{basic+, skip, wild+, wild, rev, basic}

							3+			1-2			{basic+, rev, wild+, wild, skip, basic}
										3+			{basic+, skip, rev, wild+, wild, basic}


				3+			1-2			1-2			{basic, b+, wild, wild+, skip, rev}
										3+			{basic, skip, b+, wild, wild+, rev}

							3+			1-2			{basic, b+, rev, wild, wild+, skip}
										3+			{basic, skip, b+, wild, rev, wild+}

*/
Card Player::playCard(int c)
{
	Card play = hand[c];
	play.onPlay();
	hand.erase(hand.begin() + c);
	return play;
}
