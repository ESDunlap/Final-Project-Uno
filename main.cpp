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
#include "Player.h"


int main()
{
    srand(time(0));
	Deck newDeck;
	Player p;
	newDeck.startGame();
	p.giveCard(newDeck);
	try
	{
	for(int i = 0;i<130;i++)
	    newDeck.drawTop();
	}
	catch(long tooSmall)
	{
	    cout<<"Playpile and Deck are too small to continue the game"<<endl;
	}
	p.playCard(0, newDeck);
	/*
	newDeck.fillDeck();
	newDeck.shuffle();
	p.giveCard(newDeck);
	p.giveCard(newDeck);
	p.playCard(0);
	newDeck.drawTop();
	*/
	return 0;
}
