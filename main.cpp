#include <iostream> //Generic c++
#include <climits> //Adds INT_MAX
#include <string> //Allows use of string functions
#include <iomanip> //Input Output additions
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector> //vectors
#include <bits/stdc++.h> //for random_shuffle() https://www.geeksforgeeks.org/cpp/how-to-shuffle-a-vector-in-cpp/

#include "Deck.h"

int main()
{
    srand(time(0));
	Deck newDeck;
	newDeck.fillDeck();
	newDeck.shuffle();
	return 0;
}
