#include "Deck.h"

BasicCard::BasicCard(int rank, string suit, bool plus)
{
 	this->rank = rank;
 	if(suit == "red")
		this->suit = 1;
	else if(suit == "green")
		this->suit = 2;
	else if(suit == "yellow")
		this->suit = 3;
	else
		this->suit = 4;
	this->plus = plus;   
}

BasicCard::BasicCard(int rank, int suit, bool plus)
{
	this->rank = rank;
	this->suit = suit;
	this->plus = plus;
}

BasicCard* makeBasicCard(int rank, int suit, bool plus)
{
    BasicCard* theCard = new BasicCard(rank, suit, plus);
    return theCard;
}

WildCard* makeWildCard(bool plus)
{
    WildCard* theCard = new WildCard(plus);
    return theCard;
}

ReverseCard* makeReverseCard(int suit)
{
    ReverseCard* theCard = new ReverseCard(suit);
    return theCard;
}

SkipCard* makeSkipCard(int suit)
{
    SkipCard* theCard = new SkipCard(suit);
    return theCard;
}

void Deck::fillDeck()
{
	//Number Cards
	for (int rank = 0; rank < 10; rank++)
	{
		for(int color = 0; color < 4; color++)
		{
			cards.push_back(makeBasicCard(rank, color + 1));
			if (rank != 0)
				cards.push_back(makeBasicCard(rank, color + 1));
		}
	}
	//Special cards
	for (int color = 0; color < 4; color++)
	{
		//Plus Cards
		cards.push_back(makeBasicCard(2, color + 1, true));
		cards.push_back(makeBasicCard(2, color + 1, true));
		//Reverse Cards
		cards.push_back(makeReverseCard(color + 1));
		cards.push_back(makeReverseCard(color + 1));
		//Skip Card
		cards.push_back(makeSkipCard(color + 1));
		cards.push_back(makeSkipCard(color + 1));
	}
	//Wild Cards
	for (int wildNumber = 0; wildNumber < 4; wildNumber++)
	{
		cards.push_back(makeWildCard());
		cards.push_back(makeWildCard(true));
	}
};

void Deck::shuffle()
{
    random_shuffle(cards.begin(), cards.end());
}

Card* Deck::drawTop()
{
    if (cards.empty())
    {
        if (playPile.end() - playPile.begin() <= 1)
            throw playPile.end() - playPile.begin();
        if (playPile[0]->getRank() == -1)
            playPile[0]->fixWildSuit(); //Return color to wild before shuffle
        cards = playPile;
        shuffle();
        playPile.clear();
        playPile.insert(playPile.begin(), drawTop());
        cout << "Cards were empty" << endl;
    }
    Card* topCard = cards[0];
    cards.erase(cards.begin());
    return topCard;
}

Deck::~Deck()
{
    cout << cards.end() - cards.begin();
    for (Card* card: cards)
    {
        delete card;
    }
    for (Card* card: playPile)
    {
        delete card;
    }
}

void Deck::startGame()
{
    fillDeck();
    shuffle();
    playPile.insert(playPile.begin(), drawTop());
}

bool Deck::onPlay(Card* c)
{
    if (((c->getRank() == playPile[0]->getRank()) && (c->getPlus() == playPile[0]->getPlus())) //Check if plus card
    ||
    (c->getSuit() == playPile[0]->getSuit())
    ||
    c->getRank() == -1
    ||
    playPile[0]->getSuit() == -1)
    {
        if(playPile[0]->getRank() == -1)
            playPile[0]->fixWildSuit(); //Return color to wild once a card is played on top
        playPile.insert(playPile.begin(), c);
        return true;
    }
    return false;
}

int getValidInt(string message)
{
	int getInt;
	cout << message;
	cin >> getInt;
	while (!cin)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Error: Not an Int" << endl;
		cin >> getInt;
	}
	return getInt;
}

