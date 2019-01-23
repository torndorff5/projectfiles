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

#include "symtable.h"

using namespace std;


//lexical struct
//contains all functions and members necessary to run a lexical analysis on a .kxi file.
//
struct compiler {
    
    map<string,int> KEYWORDS = { std::pair<string,int>("atoi",0), std::pair<string,int>("and",1), std::pair<string,int>("bool",2), std::pair<string,int>("block",3) , std::pair<string,int>("break",4) , std::pair<string,int>("case",5) , std::pair<string,int>("class",6) , std::pair<string,int>("char",7), std::pair<string,int>("cin",8), std::pair<string,int>("cout",9), std::pair<string,int>("default",10), std::pair<string,int>("else",11), std::pair<string,int>("false",12), std::pair<string,int>("if",13) , std::pair<string,int>("int",14) , std::pair<string,int>("itoa",15), std::pair<string,int>("kxi2019",16), std::pair<string,int>("lock",17), std::pair<string,int>("main",18), std::pair<string,int>("new",19), std::pair<string,int>("null",20), std::pair<string,int>("object",21), std::pair<string,int>("or",22), std::pair<string,int>("public",23) , std::pair<string,int>("private",24), std::pair<string,int>("protected",25), std::pair<string,int>("return",26), std::pair<string,int>("release",27), std::pair<string,int>("string",28), std::pair<string,int>("spawn",29), std::pair<string,int>("sym",30), std::pair<string,int>("set",31), std::pair<string,int>("switch",32), std::pair<string,int>("this",33), std::pair<string,int>("true",34), std::pair<string,int>("thread",35), std::pair<string,int>("unprotected",36), std::pair<string,int>("unlock",37), std::pair<string,int>("void",38), std::pair<string,int>("while",39), std::pair<string,int>("wait",40)};
    
    //type enumeration
    //space, number, potential character literal, character literal, identifier, punctuation, keyword, symbol, unknown, end of file
    enum Type {space, nl, numb, pchar, charact, id, punct, keyw, mathop,logicop,relop,assop,arrayb,arraye,blockb,blocke,parentho,parenthc,streamop, uk, eof};
    
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
    token one;
    token two;
    

    
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
        else if(0 == toascii(t.lexeme.front()))
            t.type = nl;
        else
            t.type = uk;
        
    }
    
    //check to see if current is charact
    void charCheck(token& c, token& n){
        std::regex reg_charact(".");
        std::regex reg_pchar("[']");
        std::smatch match;
        
        if(n.lexeme == "\\"){
            addnextToken(c,n);
        }
        if (std::regex_search(n.lexeme,match, reg_charact)){//if next is anything but new line or eof
            addnextToken(c,n);
            if (std::regex_search(n.lexeme,match, reg_pchar)){
                addnextToken(c,n);
                c.type = charact;
            }
        }
    }
    
    //checks to see if a string is a keyw
    void checkKeyW(token& t){
        if(KEYWORDS.end() != KEYWORDS.find(t.lexeme))
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
    void getNextToken(){
        nextToken(one, two);
        lexicalAnalysis(one, two);
        curr = next;
        next = one;
        printToken(curr);
    }
    void nextToken(token& c, token& n){
        //check to see if end of line
        if(!buffer.empty()){
            //if end of line, get next line.
            c = n;
            updateNext(c,n);
        }
        //get new line
        else{
            getLine();
            if(in.eof())
            {
                c = n;
                tokenEOF(n);//set next to EOF
            }
            else if (buffer.empty()){
                c = n;
                updateNext(c,n);
            }
            else{
                c = n;
                //set next to first of new line
                updateNext(c,n);
            }
        }
        
    }
    void addnextToken(token& c, token& n){
        //add lexeme of next to that of current and fetch the following char
        c.lexeme += n.lexeme;
        updateNext(c,n);
    }
    //gets next line of file and puts in buffer, updates line number
    void getLine(){
        std::getline(in,buffer);
        line_number++;
    }
    //updates next token with next char, checks type, and the right line number
    void updateNext(token& c, token& n){
        getChar(buffer, n);
        checkType(n);
        n.line_num = line_number;
    }
    //sets token to eof
    void tokenEOF(token& t){
        t.lexeme = "eof";
        t.line_num = line_number;
        t.type = eof;
    }
    
    void lexicalAnalysis(token& c, token& n){
        if(c.type == eof){
            return;
        }
        while (c.type == space)
            nextToken(c,n);//disregard and get next token
        while(c.type == nl)
            nextToken(c,n);
        if(c.lexeme == "/"){//catch the comments
            if(n.lexeme == "/"){
                addnextToken(c,n);
                while(c.type != nl)
                    nextToken(c,n);
            }
        }
        else if(c.type == numb)//if current is a number
            while(n.type == numb)//check to see if next is a number
                addnextToken(c,n);//add next to current and fetch next
        else if (c.type == id){
            while(n.type == numb || n.type == id)//check to see if next is a number or id
                addnextToken(c,n);//add next to current and fetch next
            checkKeyW(c);
        }
        else if (c.type == pchar)
            charCheck(c,n);//check to see if next is a letter
        else if (c.type == logicop){
            if(c.lexeme == "&" && n.lexeme == "&")
                addnextToken(c,n);
            else if(c.lexeme == "|" && n.lexeme == "|")
                addnextToken(c,n);
            else
                c.type = uk;
        }
        else if(c.type == assop){
            if(n.type == assop){
                addnextToken(c,n);
                c.type = relop;
            }
        }
        else if(c.type == relop){
            if(c.lexeme == "<" || c.lexeme == ">" || c.lexeme == "!"){
                if(n.type == assop)
                    addnextToken(c,n);
                else if (c.lexeme == "!")
                    c.type = uk;
                else if (c.lexeme == "<" && n.lexeme == "<"){
                    addnextToken(c, n);
                    c.type = streamop;
                }
                else if (c.lexeme == ">" && n.lexeme == ">"){
                    addnextToken(c, n);
                    c.type = streamop;
                }
            }
        }
    }
    void printToken(token t){
        cout << t.lexeme << "\t\t";
        switch(t.type){
            case space:
                cout << "space";
                break;
            case nl:
                cout << "newLine";
                break;
            case numb:
                cout << "number";
                break;
            case pchar:
                cout << "potential character";
                break;
            case charact:
                cout << "character";
                break;
            case id:
                cout << "identifier";
                break;
            case punct:
                cout << "punctuation";
                break;
            case keyw:
                cout << "keyword";
                break;
            case mathop:
                cout << "math operation";
                break;
            case logicop:
                cout << "logic operator";
                break;
            case relop:
                cout << "relational operator";
                break;
            case assop:
                cout << "assignment operation";
                break;
            case arrayb:
                cout << "array begin";
                break;
            case arraye:
                cout << "array end";
                break;
            case blockb:
                cout << "block begin";
                break;
            case blocke:
                cout << "block end";
                break;
            case parentho:
                cout << "parenthesis open";
                break;
            case parenthc:
                cout << "parenthesis close";
                break;
            case streamop:
                cout << "stream operator";
                break;
            case uk:
                cout << "unknown";
                break;
            case eof:
                cout << "eof";
                break;
        }
        cout << "\t\t" << t.line_num << endl;
        
    }
    
    //SYTNAX FUNCTIONS AND DATA
    void genSynError(token& c, string expected){
        cout << c.line_num << ": Found \"" << c.lexeme << "\" expecting \""<< expected << "\"" << endl;
        //exit program
        exit(1);
    }
    void statement(token&c, token& n){
        if(c.type == blockb){//************* "{" {statement} "}"
            getNextToken();
            while(c.type != blocke)
                statement(c, n);
            getNextToken();
        }
        else if(c.lexeme == "if"){
            getNextToken();//************** "(" expression ")" statement [ "else" statement ]
            if(c.type != parentho)
                genSynError(c, "(");
            getNextToken();
            expression(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            getNextToken();
            statement(c, n);
            if(c.lexeme == "else"){
                getNextToken();
                statement(c, n);
            }
            
        }
        else if(c.lexeme == "while"){
            getNextToken();//***************** "while" "(" expression ")" statement
            if(c.type != parentho)
                genSynError(c, "(");
            getNextToken();
            expression(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            getNextToken();
            statement(c, n);
        }
        else if (c.lexeme == "return"){//************* "return" [ expression ] ";"
            getNextToken();
            if(c.lexeme != ";"){
                expression(c, n);
            }
            if(c.lexeme != ";")
                genSynError(c, ";");
            getNextToken();
        }
        else if (c.lexeme == "cout"){
            getNextToken();//******************
            i am about to do the cout case for the statement grammar 
        }
        else{//***************** expression ";"
            expression(c, n);
            if(c.lexeme != ";")
                genSynError(c, ";");
            getNextToken();
        }
    }
    //checks syntax for an expression
    void expression(token& c, token& n){
        if(c.type == parentho){//************** "(" expression ")" [ expressionz ]
            getNextToken();
            expression(c, n);
            if(c.type == parenthc){
                getNextToken();
            }
            else
                genSynError(c, ")");
            if(c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop )
                expressionz(c,n);
        }
        else if(c.lexeme == "true" || c.lexeme == "false" || c.lexeme == "null" || c.type == charact || c.type == numb){//**************| "true" [expressionz] | "false" [expressionz] | "null" [expressionz] | char_literal [expressionz] | number literal [expressionz]
            getNextToken();
            if (c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop)
                expressionz(c, n);
        }
        else if(c.lexeme == "this"){
            getNextToken();
            if(c.lexeme == ".")//************ [member_refz]
                member_refz(c,n);
            if(c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop )//************** [expressionz]
                expressionz(c,n);
        }
        else if(c.type == id){//************* | identifier [fn_arr_member] [member_refz] [expressionz]
            getNextToken();
            if(c.type == parentho)
                fn_arr_memberORnew_declaration(c, n);
            if(c.lexeme == ".")
                member_refz(c,n);
            if(c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop )
                expressionz(c,n);
        }
        else
            genSynError(c, "valid expression");
            
    }
    void expressionz(token& c, token& n){
        if(c.type == mathop || c.type == relop || c.type == logicop ){//************** "+" expression | "-" expression | "*" expression | "&&" expression | "||" expression | "==" expression | "!=" expression | "<=" expression | ">=" expression | "<" expression | ">" expression
            getNextToken();
            expression(c, n);
        }
        
        else if (c.type == assop ){// | "=" assignment_expression
            getNextToken();
            assignment_expression(c,n);
        }
        else
            genSynError(c, "binary expression operator");
    }
    void assignment_expression(token& c, token& n){
        if(c.lexeme == "new"){//*************** "new" type new_declaration
            getNextToken();
            if(c.lexeme != "int" && c.lexeme != "char" && c.lexeme != "void" && c.lexeme != "bool" && c.lexeme != "sym" && c.type != id )
                genSynError(c, "type or class name");
            getNextToken();
            fn_arr_memberORnew_declaration(c, n);
        }
        else if (c.lexeme == "atoi" || c.lexeme == "itoa"){//*********** | "atoi" "(" expression ")" | "itoa" "(" expression ")"
            getNextToken();
            if(c.type != parentho)
                genSynError(c, "(");
            getNextToken();
            expression(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            getNextToken();
        }
        else
            expression(c, n);
    }
    void fn_arr_memberORnew_declaration(token& c, token& n){
        if(c.type == parentho){//************* "(" [ argument_list ] ")"
            getNextToken();
            argument_list(c,n);
            if(c.type != parenthc)
                genSynError(c, ")");
            getNextToken();
        }
        else if (c.type == arrayb){//************| "[" expression "]"
            getNextToken();
            expression(c, n);
            if(c.type != arraye)
                genSynError(c, "]");
            getNextToken();
        }
        else
            genSynError(c, "(\" or \"[");
    }
    void member_refz(token& c, token& n){
        if(c.lexeme != ".")
            genSynError(c, ".");
        getNextToken();
        if(c.type != id)
            genSynError(c, "identifier");
        getNextToken();
        if(c.type == parentho)
            fn_arr_memberORnew_declaration(c, n);
        if(c.lexeme == ".")
            member_refz(c, n);
    }
    void argument_list(token& c, token& n){
        expression(c, n);//**************** expression { "," expression }
        while(c.lexeme == ","){
            getNextToken();
            expression(c, n);
        }
    }
    void passOne(std::string filename){
        //Lexical Analysis
        //*************************Open file***************************
        //2.    Tokenize the input of the source file by grouping individual characters together to form tokens by scanning the input from LEFT-TO-RIGHT. Don't try to build a context into your scanner that is part of parsing this is just lexical analysis just work LEFT-TO-RIGHT.
        //3.    For each token created output the token type , line number and the lexeme associated with the token. This is debug code that you should make easy to turn off and on.
        //4.    Discard all comments until the end of a line is reached.
        in.open(filename, ios::in);
        if (in.is_open()){
            cout << "File opened successfully." << endl;//debug output
            std::getline(in,buffer);//read in first line
            line_number = 1;
            updateNext(one,two);//sets the first token read in to token "two"
            nextToken(one, two);//gets the next token and puts it in "two", sets one to two
            lexicalAnalysis(one, two);//repeats process to get the first whole token
            next = one;//saves first whole token to next
                getNextToken();//sets curr to next, gets next whole token
                //Here my syntax analysis occurs on current and next
                statement(curr,next);
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
};
