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
    
    const vector<string> KEYWORDS = { "atoi" , "and" , "bool" , "block" , "break", "case" , "class" , "char" , "cin" , "cout" , "default" , "else" , "false" , "if" , "int" , "itoa" , "kxi2019" , "lock" , "main", "new" , "null" , "object" , "or" , "public" , "private" , "protected" , "return" , "release" , "string" , "spawn" , "sym" , "set", "switch" , "this" , "true" , "thread" , "unprotected" , "unlock" , "void" , "while" , "wait" };
    
    //type enumeration
    //space, number, potential character literal, character literal, identifier, punctuation, keyword, symbol, unknown, end of file
    enum Type {space, nl, numb, pchar, charact, id, punct, keyw, mathop,logicop,relop,assop,arrayb,arraye,blockb,blocke,parentho,parenthc, uk, eof};
    
    //token class that has a lexeme, line# and type
    struct token {
        string lexeme;
        size_t line_num;
        Type type;
    };
    
    //struct level variables
    size_t line_number;
    fstream in;
    string buffer;
    token curr;
    token next;
    

    
    //checks type of token and sets its type value
    void checkType(token &t){
        //Reg expressions
        std::regex reg_space("[ ]");
        std::regex reg_numb("[0-9]");
        std::regex reg_id("[a-zA-Z]|_");
        std::regex reg_mathop("[+*/]");//
        std::regex reg_relop("[<>!]");
        std::regex reg_punct("[:,;.]");
        std::regex reg_pchar("[']");
        std::smatch match;
        
        if (std::regex_search(t.lexeme,match, reg_space))//is token a space
            t.type = space;
        else if (std::regex_search(t.lexeme,match, reg_relop))//istoken a number?
            t.type = relop;
        else if (t.lexeme == "=")
            t.type = assop;
        else if (std::regex_search(t.lexeme,match, reg_pchar))//istoken a number?
            t.type = pchar;
        else if(std::regex_search(t.lexeme,match, reg_mathop) || t.lexeme == "-")
            t.type = mathop;
        else if(t.lexeme == "&" || t.lexeme == "|")
            t.type = logicop;
        else if (std::regex_search(t.lexeme,match, reg_numb))//istoken a number?
            t.type = numb;
        else if(std::regex_search(t.lexeme,match, reg_id))
            t.type = id;
        else if(std::regex_search(t.lexeme,match, reg_punct))
            t.type = punct;
        else if(t.lexeme == "(")
            t.type = parentho;
        else if(t.lexeme == ")")
            t.type = parenthc;
        else if(t.lexeme == "[")
            t.type = arrayb;
        else if(t.lexeme == "]")
            t.type = arraye;
        else if(t.lexeme == "{")
            t.type = blockb;
        else if(t.lexeme == "}")
            t.type = blocke;
        else
            t.type = uk;
        
    }
    
    //check to see if current is charact
    void charCheck(){
        std::regex reg_charact(".");
        std::regex reg_pchar("[']");
        std::smatch match;
        
        if(next.lexeme == "\\"){
            addnextToken();
        }
        if (std::regex_search(next.lexeme,match, reg_charact)){//if next is anything but new line or eof
            addnextToken();
            if (std::regex_search(next.lexeme,match, reg_pchar)){
                addnextToken();
                curr.type = charact;
            }
        }
    }
    
    //checks to see if a string is a keyw
    void checkKeyW(token& t){
        if(find(KEYWORDS.begin(), KEYWORDS.end(), t.lexeme) != KEYWORDS.end())
            t.type = keyw;
    }
    
    //gets token from front char of string, places char in token, and pops front char
    void getChar(string& s, token& t){
        t.lexeme = s.front();
        s.erase(s.begin());//assign next token to front of line
    }

    token getToken(){
        return curr;
    }
    token peekToken(){
        return next;
    }
    void nextToken(){
        //check to see if end of line
        if(!buffer.empty()){
            //if end of line, get next line.
            curr = next;
            updateNext();
        }
        //get new line
        else{
            getLine();
            if(in.eof())
            {
                curr = next;
                tokenEOF(next);
            }
            else if (buffer.empty()){
                curr = next;
                updateNext();
            }
            else{
                curr = next;
                //set next to new line
                next.lexeme = "\n";
                next.type = nl;
                next.line_num = line_number;
            }
        }
    }
    void addnextToken(){
        //add lexeme of next to that of current and fetch the following char
        curr.lexeme += next.lexeme;
        updateNext();
    }
    //gets next line of file and puts in buffer, updates line number
    void getLine(){
        std::getline(in,buffer);
        line_number++;
    }
    //updates next token with next char, checks type, and the right line number
    void updateNext(){
        getChar(buffer, next);
        checkType(next);
        next.line_num = line_number;
    }
    //sets token to eof
    void tokenEOF(token& t){
        t.lexeme = "eof";
        t.line_num = line_number;
        t.type = eof;
    }
    
    void execute(std::string filename){
        //*************************Open file***************************
        //2.    Tokenize the input of the source file by grouping individual characters together to form tokens by scanning the input from LEFT-TO-RIGHT. Don't try to build a context into your scanner that is part of parsing this is just lexical analysis just work LEFT-TO-RIGHT.
        //3.    For each token created output the token type , line number and the lexeme associated with the token. This is debug code that you should make easy to turn off and on.
        //4.    Discard all comments until the end of a line is reached.
        //vector of tokens
        vector<token> tokens;
        in.open(filename, ios::in);
        if (in.is_open()){
            cout << "File opened successfully." << endl;//debug output
            std::getline(in,buffer);//read in first line
            line_number = 1;
            cout << buffer << endl;//debug output
            updateNext();
            while(curr.type != eof){
                nextToken();//move to next token, set current to next
                if(curr.type == eof){
                    tokens.push_back(curr);//debug output
                    cout << curr.lexeme << "\t\t" << curr.type << endl;//debug output
                    break;
                }
                else if(curr.type == space)//if the current token is a space
                    continue;//discard and go to next
                else if(curr.lexeme == "/"){//catch the comments
                    if(next.lexeme == "/"){
                        addnextToken();
                        while(curr.type != nl)
                            nextToken();
                    }
                }
                else if(curr.type == numb)//if current is a number
                    while(next.type == numb)//check to see if next is a number
                        addnextToken();//add next to current and fetch next
                else if (curr.type == id){
                    while(next.type == numb || next.type == id)//check to see if next is a number or id
                        addnextToken();//add next to current and fetch next
                    checkKeyW(curr);
                }
                else if (curr.type == pchar)
                    charCheck();//check to see if next is a letter
                else if (curr.type == logicop){
                    if(curr.lexeme == "&" && next.lexeme == "&")
                        addnextToken();
                    else if(curr.lexeme == "|" && next.lexeme == "|")
                        addnextToken();
                    else
                        curr.type = uk;
                }
                else if(curr.type == assop){
                    if(next.type == assop){
                        addnextToken();
                        curr.type = relop;
                    }
                }
                else if(curr.type == relop){
                    if(curr.lexeme == "<" || curr.lexeme == ">" || curr.lexeme == "!"){
                        if(next.type == assop)
                            addnextToken();
                        else if (curr.lexeme == "!")
                            curr.type = uk;
                    }
                }
                printToken(curr);
            }
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
    void printToken(token t){
        switch(t.type){
            case space:
                cout << t.lexeme << "\t\t" << "space" << endl;
                break;
            case nl:
                cout << "nl\t\tnewLine" << endl;
                break;
            case numb:
                cout << t.lexeme << "\t\t" << "number" << endl;
                break;
            case pchar:
                cout << t.lexeme << "\t\t" << "potential character" << endl;
                break;
            case charact:
                cout << t.lexeme << "\t\t" << "character" << endl;
                break;
            case id:
                cout << t.lexeme << "\t\t" << "identifier" << endl;
                break;
            case punct:
                cout << t.lexeme << "\t\t" << "punctuation" << endl;
                break;
            case keyw:
                cout << t.lexeme << "\t\t" << "keyword" << endl;
                break;
            case mathop:
                cout << t.lexeme << "\t\t" << "math operation" << endl;
                break;
            case logicop:
                cout << t.lexeme << "\t\t" << "logic operator" << endl;
                break;
            case relop:
                cout << t.lexeme << "\t\t" << "relational operator" << endl;
                break;
            case assop:
                cout << t.lexeme << "\t\t" << "assignment operation" << endl;
                break;
            case arrayb:
                cout << t.lexeme << "\t\t" << "array begin" << endl;
                break;
            case arraye:
                cout << t.lexeme << "\t\t" << "array end" << endl;
                break;
            case blockb:
                cout << t.lexeme << "\t\t" << "block begin" << endl;
                break;
            case blocke:
                cout << t.lexeme << "\t\t" << "block end" << endl;
                break;
            case parentho:
                cout << t.lexeme << "\t\t" << "parenthesis open" << endl;
                break;
            case parenthc:
                cout << t.lexeme << "\t\t" << "parenthesis close" << endl;
                break;
            case uk:
                cout << t.lexeme << "\t\t" << "unknown" << endl;
                break;
            case eof:
                cout << t.lexeme << "\t\t" << "eof" << endl;
                break;
        }
    }
    
    
};
