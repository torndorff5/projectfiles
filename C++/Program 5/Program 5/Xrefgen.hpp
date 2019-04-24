//
//  Xrefgen.hpp
//  Program 5
//
//  Created by Tanner Orndorff on 3/27/18.
//  Copyright © 2018 Monocle Heads. All rights reserved.
//

#ifndef Xrefgen_hpp
#define Xrefgen_hpp

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

class Xrefgen
{
    //know
    //vector of word objects
    string input;
    string longword;
    int linenumber;
    vector<string> iterator;
    vector<string>::iterator it;
    const int NUM_SPACES = 9;
    vector<string> buffer;
    map<string, vector<tuple<int,int>>> word_map;
    //do
public:
    Xrefgen(vector<string>& buf);
    //find all unique words that start with a letter and create an object for them
    void makeXRef();
    void displayXRef();
};


#endif /* Xrefgen_hpp */
