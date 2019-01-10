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
    enum Type {space, numb, charact, id, punct, keyw, symb, uk, eof};
    
    //token class that has a lexeme, line# and type
    struct token {
        string lexeme;
        int line_num;
        Type type;
    };
    
    
    
    //checks type of token and sets its type value
    static void checkType(token &t){
        //Reg expressions
        std::regex reg_space("[ ]");
        std::regex reg_numb("[0-9]");
        std::regex reg_charact("[^0-9]");
        
        std::smatch match;
        
        if (std::regex_search(t.lexeme,match, reg_space)){//is token a space
            cout << "curr is space" << endl;//debug output
            t.type = space;
        }
        else if (std::regex_search(t.lexeme,match, reg_numb)){//istoken a number?
            cout << "curr is number" << endl; //debug output
            t.type = numb;
        }
        else if(std::regex_search(t.lexeme,match, reg_charact)){
            cout << "curr is char" << endl; //debug output
            t.type = charact;
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
            tanner orndorff : i was just about to write the code that would check for end of line and fetch another line into the buffer. 
            //if end of line, get next line.
            curr = next;
            getChar(buffer, next);//get char for lexeme
            checkType(next);//check type
        }
        void addnextToken(){
            //test to see if end of line
            //add lexeme of next to that of current and fetch the following char
            curr.lexeme += next.lexeme;
            getChar(buffer, next);
            checkType(next);
        }
    };
    
    
    static void execute(std::string filename){
        //*************************Open file***************************
        //2.    Tokenize the input of the source file by grouping individual characters together to form tokens by scanning the input from LEFT-TO-RIGHT. Don't try to build a context into your scanner that is part of parsing this is just lexical analysis just work LEFT-TO-RIGHT.
        //3.    For each token created output the token type , line number and the lexeme associated with the token. This is debug code that you should make easy to turn off and on.
        //4.    Discard all comments until the end of a line is reached.
        //vector of tokens
        vector<token> tokens;
        fstream in;
        in.open(filename, ios::in);
        tokenface tf;
        if (in.is_open()){
            cout << "File opened successfully." << endl;//debug output
            std::getline(in,tf.buffer);//read in first line
            cout << tf.buffer << endl;//debug output
            getChar(tf.buffer, tf.next);//place first char of first line into next
            checkType(tf.next);//check type of next token
            while(tf.curr.type != eof){
                tf.nextToken();//move to next token, set current to next
                if(tf.curr.type == space){//if the current token is a space
                    //discard and go to next
                    continue;
                }
                else if(tf.curr.type == numb){//if current is a number
                    //check to see if next is a number
                    while(tf.next.type == numb){
                        //add next to current and fetch next
                        tf.addnextToken();
                    }
                }
                tokens.push_back(tf.curr);
            }
            
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
};
