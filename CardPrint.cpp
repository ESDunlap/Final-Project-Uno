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
    return "\e[0m";
}

string BasicCard::getFileName() const
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
    return os;
}

string WildCard::getFileName() const
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
    return os;
}

string ReverseCard::getFileName() const
{
    string file("");
    file += (string)"Reverse";
    file += (string)".txt";
    return file;
}

ostream& operator<<(ostream& os, const ReverseCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
    return os;
}

string SkipCard::getFileName() const
{
    string file("");
    file += (string)"Skip";
    file += (string)".txt";
    return file;
}

ostream& operator<<(ostream& os, const SkipCard& card)
{
    os << suitColor(card.getSuit()) << printAscii(card.getFileName()) << endl << "\e[0m";
    return os;
}

string getMultiFileContents(const vector<string>& Files, const vector<int>& suits)
{
    string Lines = "\n";        //All lines

    for (int file = 0; file < Files.size(); file++)
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
        for (int file = 0; file < Files.size(); file++)
        {
            string temp;
            ifstream Reader(Files[file]);
            for (int skip = 0; skip < loops; skip++)
            {
                Reader.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            getline(Reader, temp);        //Get temp line
            TempLine += suitColor(suits[file]) + temp + (string)"   \e[0m";
            if (!Reader.good())                      //Check if files are empty
            {
                loop = false;    //Stop loop
            }
            Reader.close();
        }
        TempLine += "\n";               //Add newline character
        Lines += TempLine;              //Add newline
        loops++;
    }
    if (Files.size() == 1) { return Lines; }
    string indexes("");
    for (int index = 0; index < Files.size(); index++)
    {
        indexes += (string)"     ";
        indexes += to_string(index + 1);
        indexes += (string)"       ";
        if (index < 10) { indexes += (string)" "; }
    }
    Lines += indexes + "\n\n";
    return Lines;
}

ostream& operator<<(ostream& os, const Player& player)
{

    string Art;
    vector<string> Files;
    vector<int> suits;
    for (int file = 0; file < player.getSize(); file++)
    {
        Card* card = player.getCard(file);
        string fName = card->getFileName();
        Files.push_back(fName);    //Set files

        suits.push_back(card->getSuit());
    }

    Art = getMultiFileContents(Files, suits);  //Get all Art

    os << Art;

    return os;     //Return Art
}

ostream& operator<<(ostream& os, const Deck& deck)
{
    string Art;
    vector<string> Files;
    vector<int> suits;
    Card* card = deck.playPile[0];
    string fName = card->getFileName();
    Files.push_back(fName);    //Set files
    suits.push_back(card->getSuit());

    Art = getMultiFileContents(Files, suits);  //Get all Art

    os << Art;

    return os;     //Return Art
}
