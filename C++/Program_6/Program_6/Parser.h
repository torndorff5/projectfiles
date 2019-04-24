//
//  Parser.h
//  Program_6
//
//  Created by codeslinger on 3/25/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#ifndef Parser_h
#define Parser_h

#include <map>
#include <regex>

using namespace std;

//Lexical ************************************************************************************************************************************
class lexical{
    public:
        std::map<string,int> KEYWORDS = { std::pair<string,int>("atoi",0), std::pair<string,int>("and",1), std::pair<string,int>("bool",2), std::pair<string,int>("block",3) , std::pair<string,int>("break",4) , std::pair<string,int>("case",5) , std::pair<string,int>("class",6) , std::pair<string,int>("char",7), std::pair<string,int>("cin",8), std::pair<string,int>("cout",9), std::pair<string,int>("default",10), std::pair<string,int>("else",11), std::pair<string,int>("false",12), std::pair<string,int>("if",13) , std::pair<string,int>("int",14) , std::pair<string,int>("itoa",15), std::pair<string,int>("kxi2019",16), std::pair<string,int>("lock",17), std::pair<string,int>("main",18), std::pair<string,int>("new",19), std::pair<string,int>("null",20), std::pair<string,int>("object",21), std::pair<string,int>("or",22), std::pair<string,int>("public",23) , std::pair<string,int>("private",24), std::pair<string,int>("protected",25), std::pair<string,int>("return",26), std::pair<string,int>("release",27), std::pair<string,int>("string",28), std::pair<string,int>("spawn",29), std::pair<string,int>("sym",30), std::pair<string,int>("set",31), std::pair<string,int>("switch",32), std::pair<string,int>("this",33), std::pair<string,int>("true",34), std::pair<string,int>("thread",35), std::pair<string,int>("unprotected",36), std::pair<string,int>("unlock",37), std::pair<string,int>("void",38), std::pair<string,int>("while",39), std::pair<string,int>("wait",40)};

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

        lexical(string filename){
            in.open(filename);
            if(!in.is_open()){
                cout << "Error opening file";
                exit(1);
            }
            buffer = "";
            line_number = 1;
            updateNext(one,two);//sets the first token read in to token "two"
            nextToken(one, two);//gets the next token and puts it in "two", sets one to two
            lexicalAnalysis(one, two);//repeats process to get the first whole token
            next = one;//saves first whole token to next
            getNextToken();//sets curr to next, gets next whole token
        }

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
            //printToken(curr);
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
                buffer.insert(buffer.begin(), '\0');
                if(in.eof())
                {
                    c = n;
                    tokenEOF(n);//set next to EOF
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
            while (c.type == space || c.type == nl)
                nextToken(c,n);//disregard and get next token
            if(c.lexeme == "/"){//catch the comments
                if(n.lexeme == "/"){
                    addnextToken(c,n);
                    while(c.type != nl)//find end of line
                        nextToken(c,n);
                    return lexicalAnalysis(c, n);
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
};



#endif /* Parser_h */
