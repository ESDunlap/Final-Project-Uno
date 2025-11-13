#include <iostream> //Generic c++
#include <fstream> // Allows file reading
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
    string file = "Basic";
    file += to_string(rank);
    if (plus) { file += (string)"P.txt"; }
    else { file += (string)".txt"; }
    return file;
}

friend ostream& operator<<(ostream& os, const BasicCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
}

string WildCard::getFileName()
{
    string file("");
    string file = "Wild";
    if (plus) { file += (string)"P.txt"; }
    else { file += (string)".txt"; }
    return file;
}

friend ostream& operator<<(ostream& os, const WildCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
}

friend ostream& operator<<(ostream& os, const ReverseCard& card)
{
    string art = "Reverse";
    art += (string)".txt";
    os << suitColor(card.getSuit()) << printAscii(art) << endl << "\e[0m";
}

friend ostream& operator<<(ostream& os, const SkipCard& card)
{
    string art = "Skip";
    art += (string)".txt";
    os << suitColor(card.getSuit()) << printAscii(art) << endl << "\e[0m";
}

string getMultiFileContents(int size, ifstream& Files[size], int& suits[size])
{
    string Lines = "";        //All lines

    for (int file = 0; file < size; file++)
    {
        if (!Files[file])                      //Check if everything is good
        {
            return "ERROR File does not exist.";    //Return error
        }
    }

    bool loop = true;
    while (loop)
    {
        string TempLine("");                //Temp line
        for (int file = 0; file < size; file++)
        {
            string temp;
            getline(Files[file], temp);        //Get temp line
            TempLine += suitColor(suits[file]) + temp + (string)"   \e[0m";
            if (!Files[file].good())                      //Check if files are empty
            {
                loop = false;    //Stop loop
            }
        }
        TempLine += "\n";               //Add newline character
        Lines += TempLine;              //Add newline
        
    }
    return Lines;
}

friend ostream& operator<<(ostream& os, const Player& p)
{
    ifstream Files[p.getSize()];
    for (int file = 0; file < p.getSize(); file++)
    {
        ifstream Reader();
        Files[file] = Reader;    //Open files
    }

    string Art = getMultiFileContents(p.getSize(), Files, suits);  //Get all Art


    for (int file = 0; file < p.getSize(); file++)
    {
        Files[file].close();    //Close files
    }

    return Art;     //Return Art
}