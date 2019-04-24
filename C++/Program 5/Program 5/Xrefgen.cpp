//
//  Xrefgen.cpp
//  Program 5
//
//  Created by Tanner Orndorff on 3/27/18.
//  Copyright © 2018 Monocle Heads. All rights reserved.
//

#include "Xrefgen.hpp"


Xrefgen::Xrefgen(vector<string>& buf)
{
    buffer = buf;
    longword = "";
}

//finds all the unique words and creates an object for them. putting them in the vector
void Xrefgen::makeXRef()
{
    regex e("\\b[a-zA-Z]+'?[a-zA-Z]*\\b");
    for(int i =0; i < buffer.size(); i++)
    {
        regex_iterator<string::iterator> rit(buffer[i].begin(), buffer[i].end(), e);
        regex_iterator<string::iterator> rend;
        //go through each line
        while (rit != rend)
        {
            //find the string
            input = rit->str();
            //find longest word
            if(longword < input)
                longword = input;
            //what is the line number
            linenumber = i+1;
            //how many times does it happen on this line
            size_t lastIndex = 0;
            int count = 0;
            while(lastIndex != string::npos){
                
                lastIndex = buffer[i].find(input,lastIndex);
                
                if(lastIndex != string::npos){
                    count ++;
                    lastIndex += input.length();
                }
            }
            //store in map
            tuple<int,int> temp(linenumber, count);
            word_map[input].push_back(temp);
            iterator.push_back(input);
            rit++;
        }
    }
    //get rid of duplicates in iterator and then in the map
    sort(iterator.begin(), iterator.end());
    it = unique(iterator.begin(), iterator.end());
    iterator.resize(distance(iterator.begin(),it));
    vector<tuple<int,int>>::iterator iter;
    for (int i = 0; i < iterator.size(); i++)
    {
        iter = unique(word_map[iterator[i]].begin(), word_map[iterator[i]].end());
        word_map[iterator[i]].resize(distance(word_map[iterator[i]].begin(), iter));
    }
}

struct size_small
{
    template<class T> bool operator()(T const &a, T const &b) const
    {
        return a.size() < b.size();
    }
};

void Xrefgen::displayXRef()
{
    auto longword = max_element(iterator.begin(), iterator.end(), size_small())->size();
    longword++;
    //iterate through map
    for (int i = 0; i < iterator.size(); i++)
    {
        //print string
        cout << endl << iterator[i];
        //subtract string length from longest word length
        cout.width(longword-iterator[i].size());
        cout << ": ";
        //print out locations
        int k = 0;
        for (int j = 0; j < word_map[iterator[i]].size(); j++)
        {
            k++;
            if(word_map[iterator[i]].size() == 1)
            {
                cout<< get<0>(word_map[iterator[i]][j]) << ":" << get<1>(word_map[iterator[i]][j]);
            }
            else if(j == 0)
            {
                cout<< get<0>(word_map[iterator[i]][j]) << ":" << get<1>(word_map[iterator[i]][j]);
            }
            else if (k < NUM_SPACES)
            {
                cout<< ", " << get<0>(word_map[iterator[i]][j]) << ":" << get<1>(word_map[iterator[i]][j]);
            }
            else
            {
                //create new line
                cout << endl;
                //indent line
                cout.width(longword);
                //put colon
                cout << ": ";
                k=0;
                //output next number
                cout<< get<0>(word_map[iterator[i]][j]) << ":" << get<1>(word_map[iterator[i]][j]);
            }
        }
    }
    cout << endl;
}
