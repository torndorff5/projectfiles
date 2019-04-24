//
//  main.cpp
//  Program 5
//
//  Created by Tanner Orndorff on 3/27/18.
//  Copyright © 2018 Monocle Heads. All rights reserved.
//

//cross ref generator
//read in file or standard input***********
//read in whole file into buffer***********
//find each word , which line it apears, and how many times for that line.
//write results out to file
//replace absolute path with argv[1]

#include "Xrefgen.hpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    //if there is a command line argument, read that file
    vector<string> buffer;
    string input;
    if (true)
    {
        //read in file to buffer
        ifstream f;
        f.open("/Users/codeslinger/Desktop/C++/Program 5/Program 5/string.txt", ios::in);
        if(f.is_open())
        {
            while(!f.fail())
            {
                getline(f,input);
                buffer.push_back(input);
            }
            Xrefgen* test = new Xrefgen(buffer);
            
            test->makeXRef();
            test->displayXRef();
        }
        else
        {
            cout << "File failed to open." << endl;
        }
    }
    else
    {
        //read standard input into buffer
        while(!cin.fail())
        {
            getline(cin, input);
            buffer.push_back(input);
        }
        Xrefgen* test = new Xrefgen(buffer);
        
        test->makeXRef();
        test->displayXRef();
    }
    return 0;
}

//Reflection
//I really enjoyed this assignment because it again forced me to learn new containers and use the standard library algorithms. I really learned a lot about maps, tuples, sets, and vectors.
//I think I made big strides in how I designed and implemented this program in a simple way. I had a lot of fun. It was pretty
