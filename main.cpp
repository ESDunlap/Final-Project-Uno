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

int getValidInt(string message)
{
    int getInt;
    cout<<message<<endl;
    cin>>getInt;
    while(!cin)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout<<"Error: Not an Int"<<endl;
        cin>>getInt;
    }
    return getInt;
}


int main()
{
    srand(time(0));
    bool someoneWon;
	Deck newDeck;
	newDeck.startGame();
	/*
	int numAi= getValidInt("How many AI's will you be fighting? (1-3): ");
	while (numAi > 3 || numAi < 1)
	{
	    cout<<"Error: Outside of Range"<<endl;
	    numAi= getValidInt("How many AI's will you be fighting? (1-3): ");
	}
	*/
	int numAi=3;
	int startCards= getValidInt("How many cards will a player start with? (3-10):");
	while (startCards > 10 || startCards < 3)
	{
	    cout<<"Error: Outside of Range"<<endl;
	    startCards= getValidInt("How many cards will a player start with? (3-10):");
	}
	Player allPlayers[numAi+1];
	for(int i = 0; i<=numAi;i++)
	{
	    if (i!=0)
	        allPlayers[i].setAi();
	    for(int v = 0; v<startCards; v++)
	        allPlayers[i].giveCard(newDeck);
	}
	int currentPlayer= rand() % (numAi+1);
	bool reverse= false;
	bool skip= false;
	bool plus= false;
	try
	{
    	while (!someoneWon)
    	{
    	    if(reverse)
    	        currentPlayer = (currentPlayer+1) % (numAi+1);
    	    else
    	        currentPlayer = (currentPlayer-1) % (numAi+1);
    	    allPlayers[currentPlayer].playTurn(reverse, skip, plus, newDeck);
    	    if(allPlayers[currentPlayer].getSize() == 0)
    	        someoneWon=true;
    	}
	}
	catch(long tooSmall)
	{
	    cout<<"Playpile and Deck are too small to continue the game"<<endl;
	}
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
