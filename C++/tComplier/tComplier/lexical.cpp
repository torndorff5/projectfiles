//
//  lexical.cpp
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <cstdlib>

using namespace std;


//lexical struct
//contains all functions and members necessary to run a lexical analysis on a .kxi file.
//
struct lexical {
    
    
    
    //type enumeration
    enum Type {numb, charact, id, punct, keyw, symb, uk, eof};
    //token class that has a lexeme, line# and type
    struct token {
        string lexeme;
        int line_num;
        Type t;
    };
    
    //checks type of token and sets its type value
    static void checkType(token &t){
        //Reg expressions
        std::regex reg_num("[0-9]");
        std::smatch match;
        
        if (std::regex_search(t.lexeme,match, reg_num)){//istoken a number?
            cout << "curr is number" << endl; //debug output
            t.t = numb;
        }
    }
    
    //gets token from front char of string, places char in token, and pops front char
    static void getChar(string& s, token& t){
        t.lexeme = s.front();
        s.erase(s.begin());//assign next token to front of line
    }
    
    //token interface
    struct tokenface {
        string buffer;
        token curr;
        token next;
        token getToken(){
            return curr;
        }
        token peekToken(){
            return next;
        }
        void nextToken(){
            //check to see if end of line
            //if end of line, get next line.
            curr = next;
            getChar(buffer, next);//get char for lexeme
            checkType(next);//check type
        }
    };
    
    
    static void execute(std::string filename){
        //*************************Open file***************************
        //2.    Tokenize the input of the source file by grouping individual characters together to form tokens by scanning the input from LEFT-TO-RIGHT. Don't try to build a context into your scanner that is part of parsing this is just lexical analysis just work LEFT-TO-RIGHT.
        //3.    For each token created output the token type , line number and the lexeme associated with the token. This is debug code that you should make easy to turn off and on.
        //4.    Discard all comments until the end of a line is reached.
        fstream in;
        in.open(filename, ios::in);
        tokenface tf;
        if (in.is_open()){
            cout << "File opened successfully." << endl;//debug output
            std::getline(in,tf.buffer);//read in first line
            cout << tf.buffer << endl;//debug output
            
            getChar(tf.buffer, tf.next);//place first char of first line into next
            checkType(tf.next);//check type of next token
            tf.nextToken();//move to next token
            tanner orndorff : i am about to test my code to see if it has successfully scanned the first two chars and set their token data to the right values. 

            
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
};
