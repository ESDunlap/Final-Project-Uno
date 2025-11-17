#pragma once
#include <iostream> //Generic c++
#include <fstream> // Allows file reading
#include <vector>
#include <limits> // Credit to Google "fstream c++ skip lines"

#include "Deck.h"
#include "Player.h"

using namespace std;

string getFileContents(ifstream& File);
string printAscii(string file);
string suitColor(ostream& os, int suit);
string getMultiFileContents(const vector<string>& Files, const vector<int>& suits);
