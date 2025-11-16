#include <iostream> //Generic c++
#include <fstream> // Allows file reading
#include <limits> // Credit to Google "fstream c++ skip lines"
#include <string> //Allows use of string functions
#include <climits> //Adds INT_MAX
#include <iomanip> //Input Output additions
#include <vector>

#include "Deck.h"
#include "Player.h"
#include "CardPrint.h"

string getFileContents(ifstream& File)
{
    string Lines = "";        //All lines

    if (File)                      //Check if everything is good
    {
        while (File.good())
        {
            string TempLine;                //Temp line
            getline(File, TempLine);        //Get temp line
            TempLine += "\n";               //Add newline character

            Lines += TempLine;              //Add newline
        }
        return Lines;
    }
    else                           //Return error
    {
        return "ERROR File does not exist.";
    }
}

string printAscii(string file)
{
    ifstream Reader(file);      //Open file

    string Art = getFileContents(Reader);       //Get file

    Reader.close();

    return Art;     //Return Art
}

string suitColor(int suit)
{
    switch (suit)
    {
    case -1:
        return "\e[0;37m";
        break;
    case 1:
        return "\e[0;31m";
        break;
    case 2:
        return "\e[0;32m";
        break;
    case 3:
        return "\e[0;33m";
        break;
    case 4:
        return "\e[0;34m";
        break;
    }
}

string BasicCard::getFileName()
{
    string file("");
    file += (string)"Basic";
    file += to_string(rank);
    if (plus) { file += (string)"P.txt"; }
    else { file += (string)".txt"; }
    return file;
}

ostream& operator<<(ostream& os, const BasicCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
}

string WildCard::getFileName()
{
    string file("");
    file += (string)"Wild";
    if (plus) { file += (string)"P.txt"; }
    else { file += (string)".txt"; }
    return file;
}

ostream& operator<<(ostream& os, const WildCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
}

string ReverseCard::getFileName()
{
    string file("");
    file += (string)"Reverse";
    file += (string)".txt";
    return file;
}

ostream& operator<<(ostream& os, const ReverseCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
}

string SkipCard::getFileName()
{
    string file("");
    file += (string)"Skip";
    file += (string)".txt";
    return file;
}

ostream& operator<<(ostream& os, const SkipCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
}

string getMultiFileContents(int size, string& Files[size], int& suits[size])
{
    string Lines = "";        //All lines

    for (int file = 0; file < size; file++)
    {
        ifstream Reader(Files[file]);
        if (!Reader)                      //Check if everything is good
        {
            return "ERROR File does not exist.";    //Return error
        }
    }

    bool loop = true;
    int loops = 0;
    while (loop)
    {
        string TempLine("");                //Temp line
        for (int file = 0; file < size; file++)
        {
            string temp;
            ifstream Reader(Files[file]);
            for (int skip = 0; skip < loops; skip++)
            {
                Reader.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            getline(Reader, temp);        //Get temp line
            TempLine += suitColor(suits[file]) + temp + (string)"   \e[0m";
            if (!Files[file].good())                      //Check if files are empty
            {
                loop = false;    //Stop loop
            }
            Reader.close();
        }
        TempLine += "\n";               //Add newline character
        Lines += TempLine;              //Add newline
        loops++;
    }
    return Lines;
}

ostream& operator<<(ostream& os, const Player& p)
{

    string Art;
    string Files[p.getSize()];
    int suits[p.getSize()];
    for (int file = 0; file < p.getSize(); file++)
    {
        Card card = p.getCard(file);
        string fName = card.getFileName();
        Files[file] = fName;    //Set files

        suits[file] = card.getSuit();
    }

    Art = getMultiFileContents(p.getSize(), Files, suits);  //Get all Art

    return Art;     //Return Art
}
