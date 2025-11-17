#include "Deck.h"
#include "Player.h"
#include "CardPrint.h"

int main()
{
    srand(time(0));
    string possibleNames[10]= {"Erik", "Kaeden", "Amanda", "Davis", "Tim",
                               "Jack", "Willow", "Wanda", "Penny", "Samantha"};
    bool someoneWon;
	Deck newDeck;
	newDeck.startGame();
	int numAi = 3;
	int startCards = getValidInt("How many cards will a player start with? (3-10): ");
	while (startCards > 10 || startCards < 3)
	{
	    cout << "Error: Outside of Range" << endl;
	    startCards = getValidInt("How many cards will a player start with? (3-10): ");
	}
	Player allPlayers[numAi + 1];
	cout << "What is your name? ";
	cin >> allPlayers[0].playerName;
	for(int player = 0; player <= numAi; player++)
	{
	    if (player != 0)
	    {
	        allPlayers[player].setAi();
	        allPlayers[player].playerName = possibleNames[rand() % 10];
	    }
	    for (int card = 0; card < startCards; card++)
	        allPlayers[player].giveCard(newDeck);
	}
	int currentPlayer = rand() % (numAi + 1);
	bool reverse = false, skip = false, plus = false;
	int nextPlayer, crossPlayer, previousPlayer;
	try
	{
    	while (!someoneWon)
    	{
    	    if (!reverse)
    	    {
    	        currentPlayer = (currentPlayer + 1) % (numAi + 1);
    	        nextPlayer = (currentPlayer + 1) % 4;
    	        crossPlayer = (currentPlayer + 2) % 4;
    	        previousPlayer = (currentPlayer + 3) % 4;
    	    }
    	    else
    	    {
    	        currentPlayer = (currentPlayer + 3) % (numAi + 1);
    	        nextPlayer = (currentPlayer + 3) % 4;
    	        crossPlayer = (currentPlayer + 2) % 4;
    	        previousPlayer = (currentPlayer + 1) % 4;
    	    }
    	    if (currentPlayer ==0 )
    	    {
    	    cout << allPlayers[nextPlayer].playerName << "'s Hand Size: ";
    	    cout << allPlayers[nextPlayer].getSize() << endl;
            cout << allPlayers[crossPlayer].playerName << "'s Hand Size: ";
            cout << allPlayers[crossPlayer].getSize() << endl;
	        cout << allPlayers[previousPlayer].playerName << "'s Hand Size: ";
	        cout << allPlayers[previousPlayer].getSize() << endl;
	        }
	        cout << allPlayers[currentPlayer].playerName << " turn: " << endl;
    	    allPlayers[currentPlayer].playTurn(reverse, skip, plus, newDeck,
    	                                       allPlayers[nextPlayer].getSize(),
    	                                       allPlayers[crossPlayer].getSize(),
    	                                       allPlayers[previousPlayer].getSize(),
    	                                       allPlayers[0]);
    	    if (allPlayers[currentPlayer].getSize() == 0)
    	        someoneWon = true;
    	}
    	cout << allPlayers[currentPlayer].playerName << " HAS WON!!" << endl;
	}
	catch (long tooSmall)
	{
	    cout << "Playpile and Deck are too small to continue the game" << endl;
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
