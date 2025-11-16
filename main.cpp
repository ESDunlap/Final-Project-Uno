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
    string possibleNames[10]= {"Erik", "Kaeden", "Amanda", "Davis", "Tim",
                               "Jack", "Willow", "Wanda", "Penny", "Samantha"};
    bool someoneWon;
	Deck newDeck;
	newDeck.startGame();
	int numAi=3;
	int startCards= getValidInt("How many cards will a player start with? (3-10):");
	while (startCards > 10 || startCards < 3)
	{
	    cout<<"Error: Outside of Range"<<endl;
	    startCards= getValidInt("How many cards will a player start with? (3-10):");
	}
	Player allPlayers[numAi+1];
	cout<<"What is your name?"<<endl;
	cin>>allPlayers[0].playerName;
	for(int i = 0; i<=numAi;i++)
	{
	    if (i!=0)
	    {
	        allPlayers[i].setAi();
	        allPlayers[i].playerName=possibleNames[rand()%10];
	    }
	    for(int v = 0; v<startCards; v++)
	        allPlayers[i].giveCard(newDeck);
	}
	int currentPlayer= rand() % (numAi+1);
	bool reverse= false;
	bool skip= false;
	bool plus= false;
	int nextPlayerSize;
	int crossPlayerSize;
	int previousPlayerSize;
	try
	{
    	while (!someoneWon)
    	{
    	    if(!reverse)
    	    {
    	        currentPlayer = (currentPlayer+1) % (numAi+1);
    	        nextPlayerSize= allPlayers[(currentPlayer+1)%4].getSize();
    	        crossPlayerSize= allPlayers[(currentPlayer+2)%4].getSize();
    	        previousPlayerSize= allPlayers[(currentPlayer+3)%4].getSize();
    	    }
    	    else
    	    {
    	        currentPlayer = (currentPlayer+3) % (numAi+1);
    	        nextPlayerSize= allPlayers[(currentPlayer+3)%4].getSize();
    	        crossPlayerSize= allPlayers[(currentPlayer+2)%4].getSize();
    	        previousPlayerSize= allPlayers[(currentPlayer+1)%4].getSize();
    	    }
    	    if (currentPlayer==0)
    	    {
    	    cout<<"Next Player Hand Size: "<<nextPlayerSize<<endl;
            cout<<"Across Player Hand Size: "<<crossPlayerSize<<endl;
	        cout<<"Previous Player Hand Size: "<<previousPlayerSize<<endl;
	        }
	        cout<<allPlayers[currentPlayer].playerName<<" turn: "<<endl;
    	    allPlayers[currentPlayer].playTurn(reverse, skip, plus, newDeck,
    	                                       nextPlayerSize, crossPlayerSize,
    	                                       previousPlayerSize);
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
