#pragma once
#include <iostream> //Generic c++
#include <fstream>
#include <vector>

#include "Deck.h"

using namespace std;

string getFileContents(ifstream& File);
string printAscii(string file);
ostream& suitColor(ostream& os, int suit);
string getMultiFileContents(const vector<string>& Files, const vector<int>& suits);
