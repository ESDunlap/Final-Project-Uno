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

Card Player::playCard(int c)
{
	Card play = hand[c];
	play.onPlay();
	hand.erase(hand.begin() + c);
	return play;
}