#pragma once
#include <iostream> //Generic c++

#include "Deck.h"

using namespace std;

string getFileContents(ifstream& File);
string printAscii(string file);
ostream& suitColor(ostream& os, int suit);