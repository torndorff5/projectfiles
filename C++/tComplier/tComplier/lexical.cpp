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
            curr = next;
            next.lexeme = buffer.front();
            buffer.erase(buffer.begin());
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
            tf.next.lexeme = tf.buffer.front();
            tf.buffer.erase(tf.buffer.begin());
            
            tf.nextToken();
            if (tf.peekToken() == tanner orndorff : i was just checking to see if the next char in my test sequence was a number. We need to use regex to get a number. 
            
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
};
