#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions
#include <vector>

#include "Deck.h"
#include "Player.h"

using namespace std;

void giveCard(Card& c)
{
	hand.push_back(c);
}