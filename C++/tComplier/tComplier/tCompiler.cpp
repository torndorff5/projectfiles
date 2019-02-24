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
#include <map>
#include <algorithm>

using namespace std;


//lexical struct
//contains all functions and members necessary to run a lexical analysis on a .kxi file.
//
static bool semantic;
static bool syntax;

class compiler {
public:
    compiler(){
        syntax = false;
        semantic = true;
    }
    
    //Lexical ************************************************************************************************************************************
    
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
    
    //symbol table functions and data ****************************************************************************************************************************************
    //sym struct to place in map
    //Data struct to hold symbol specific data
    struct Data{
        string type;
        string accessMod;
        vector<string> param;
        int size;
        string asslit;
        void clear(){
            type="";
            accessMod="";
            asslit = "";
            size = 0;
            param.clear();
        }
    };
    struct sym{
        string scope;
        string symid;
        string value;
        string kind;
        Data data;
        void clear(){
            scope = "";
            symid = "";
            value = "";
            kind = "";
            data.clear();
        }
    };
    
    class symboltable {
        //know
        //symbol counter
        int count;
        //key - > values table
        map<string,sym> symtab;
        //do
        //construct itself
    public:
        symboltable(){
            count = 1;
        };
        //generate symid
        //takes a char and adds the symbol counter to it to create a unique symbol id
        string genSymID(char c){
            string s = "";
            s+=c;
            s+=(to_string(count++));
            return s;
        }
        //add global s variable to the table. also gen symid and clears s after
        void addBaseSymbol(sym& s){
            //generate symid
            s.symid = genSymID(s.value.at(0));
            sym* temp = new sym(s);
            symtab.insert(std::pair<string,sym>(s.symid,*temp));
            s.clear();//resets s
        }
        void removeSymbol(sym s){
            symtab.erase(s.symid);
        }
        //add any symbol to the table
        void addSymbol(sym& s){
            symtab.insert(std::pair<string,sym>(s.symid,s));
        }
        //fecth symbol with symid
        sym fetchSymbol(string s){
            try{
                sym r = symtab.at(s);
                return r;
            }
            catch (std::out_of_range e){
                throw e;
            }
        }
        //check to see if lexeme exists in current scope, or outer scope, returns symid
        string containsLexeme(string l, string currscope){
            for(auto x: symtab){
                if(x.second.value == l)
                    if(currscope == x.second.scope)
                        l = x.second.symid;
            }
            return l;
        }
        void printST(){
            for(auto s:symtab){
                cout << "Symid: " << s.second.symid << endl;
                cout << "Scope: " << s.second.scope << endl;
                cout << "Kind: " << s.second.kind << endl;
                cout << "Value: " << s.second.value << endl;
                cout << "\tType: " << s.second.data.type << endl;
                cout << "\tAccessMod: " << s.second.data.accessMod << endl;
                cout << "\tParam: ";
                for(auto p: s.second.data.param){
                    cout << p << " ";
                }
                cout << endl;
                cout << "\tSize: " << s.second.data.size << endl;
                cout << endl;
            }
        }
        int removeDup(){
            vector<string> global_values;
            vector<string> removelist;
            int c = 0;
            for(auto s:symtab){
                if(s.second.kind == "lit"){
                    if(std::find(global_values.begin(), global_values.end(), s.second.value) != global_values.end()) {
                        /* global_values contains second value */
                        //delete symbol
                        removelist.push_back(s.second.symid);
                        c++;
                    }
                    else {
                        /* does not contain */
                        global_values.push_back(s.second.value);
                    }
                }
            }
            for(string s:removelist){
                symtab.erase(s);
            }
            return c;
        }
    };
    //Semantic Functions and Data ******************************************************************************************************************
    //precedence
    int precedence(token t){
        if(t.lexeme == "*" || t.lexeme == "/")
            return 8;
        else if (t.lexeme == "+" || t.lexeme == "-")
            return 7;
        else if (t.lexeme == "<" || t.lexeme == "<=" || t.lexeme == ">" || t.lexeme == ">=")
            return 6;
        else if (t.lexeme == "==" || t.lexeme == "!=")
            return 5;
        else if (t.lexeme == "&&")
            return 4;
        else if (t.lexeme == "||")
            return 3;
        else if (t.lexeme == "=")
            return 2;
        else if (t.lexeme == "(" || t.lexeme == ")" || t.lexeme == "[" || t.lexeme == "]")
            return 1;
        else
            return 0;
    }
    void genSymError(){
        cout << line_number <<  ": Semantic Error" << endl;
        exit(1);
    }
    //Semantic Action Stack
    vector<string> SAS;
    string popSAS(){
        if(SAS.empty())
            genSymError();
        string s = SAS.back();
        SAS.pop_back();
        return s;
    }
    //Operator Stack
    vector<token> OS;
    token popOS(){
        token t = OS.back();
        OS.pop_back();
        return t;
    }
    token peekOS(){
        token t=OS.back();
        return t;
    }
    //iPush - push SAR
    void iPush(token& c){
        SAS.push_back(c.lexeme);
    }
    //oPush
    void oPush(token& c){
        //check precedence with curr and top of stack. If top of stack is high then run a "#op"
        if(!OS.empty()){//something on the stack
            if(precedence(c)>precedence(peekOS()))
               OS.push_back(c);trying to figure out why a parenthesis would be considered lower precedence than a function
            else{
                p_op();//pop back operator
                //push current operator on the stack
                OS.push_back(c);
            }
        }
        else
            OS.push_back(c);
    }
    //iExist
    void iExist(){
        //pop the top SAR off the SAS
        string top_sar = popSAS();
        //test if the SAR exists in the current scope.
        string temp = st->containsLexeme(top_sar, scope);
        if(top_sar != temp){
        //if exists, push id_sar onto the SAS
            SAS.push_back(temp);
        }
        else{
        //if does not exist, throw semantic errors
            genSymError();
        }
    }
    //#rexist
    void rExist(){
        //pop top sar from sas
        string top_sar = popSAS();
        //pop next sar
        string next_sar = popSAS();
        //is top sar a public member of next sar?
        sym t = st->fetchSymbol(next_sar);
        string s = GLOBAL;
        push_scope(s, t.data.type);
        string temp = st->containsLexeme(top_sar, s);
        if(top_sar != temp){
        //if yes, push onto SAS
            t = st->fetchSymbol(temp);
            if(t.data.accessMod == PUBLIC){
                SAS.push_back(temp);
            }
            else
                genSymError();
        }
        else
        //if no, throw sym error
            genSymError();
        
    }
    //#BAL
    void BAL(){
        SAS.push_back("(");
    }
    //#EOE
    void EOE(){
        while (!OS.empty()){
            p_op();//pop off operator stack until its empty
        }
    }
    //#op
    void p_op(){
        token t = popOS();
        if(t.type == assop){//#=
            passop();
        }
        //#*
        else if(t.lexeme == "*")
            pmultop();
        //#/
        else if(t.lexeme == "/")
            pdivop();
        else if (t.lexeme == "+")
            paddop();
    }
    //#+
    void paddop(){
        sym y = st->fetchSymbol(popSAS());
        sym x = st->fetchSymbol(popSAS());
        //is x + y valid?
        if(x.data.type != INT || y.data.type != INT)//are x and y both ints?
            genSymError();
        //push x onto SAS to store type of answer
        SAS.push_back(x.symid);
    }
    //#*
    void pmultop(){
        sym y = st->fetchSymbol(popSAS());
        sym x = st->fetchSymbol(popSAS());
        //is x*y valid?
        if(x.data.type != INT || y.data.type != INT)//are x and y both ints?
            genSymError();
        //push x onto SAS
        SAS.push_back(x.symid);
    }
    //#/
    void pdivop(){
        //get y and x from the SAS
        sym y = st->fetchSymbol(popSAS());
        sym x = st->fetchSymbol(popSAS());
        //is x / y valid?
        if(x.data.type != INT || y.data.type != INT)//are x and y both ints?
            genSymError();
        //push x onto SAS
        SAS.push_back(x.symid);
    }
    //#=
    void passop(){//#=
        sym y = st->fetchSymbol(popSAS());
        sym x = st->fetchSymbol(popSAS());
        //is x = y valid?
        if(x.kind == LITERAL)//is x a valid lValue?
            genSymError();
        if(x.data.type != y.data.type)//do x and y share the same type
            genSymError();
    }
    //SYTNAX FUNCTIONS AND DATA******************************************************************************************************************
    symboltable* st = new symboltable();
    sym s;
    string scope;
    const string IVAR = "ivar";
    const string LVAR = "lvar";
    const string LITERAL = "lit";
    const string CHAR = "char";
    const string INT = "int";
    const string BOOL = "bool";
    const string nul = "null";
    const string GLOBAL = "g";
    const string ARRAY = ":@";
    const string PARAM = "param";
    const string METHOD = "method";
    const string CONSTR = "constructor";
    const string PUBLIC = "public";
    const string PRIVATE = "private";
    
    void push_scope(string& s,string temp){
        s += "." + temp;
    }
    static string pop_scope(string& s){
        size_t pos = s.find_last_of('.');
        s.erase(pos, s.length());
        return s;
    }
    void addLit(token& c){
        s.clear();
        s.value = c.lexeme;
        s.kind = LITERAL;
        synType(c);
        s.scope = GLOBAL;
        s.data.accessMod = PUBLIC;
        st->addBaseSymbol(s);
    }
    void synType(token& c){
        if(c.type == charact)
            s.data.type = CHAR;
        if(c.type == numb)
            s.data.type = INT;
        if(c.lexeme == "true" || c.lexeme == "false")
            s.data.type = BOOL;
        if(c.lexeme == "null")
            s.data.type = nul;
    }
    void addClass(token& c){
        s.kind = "class";
        s.value = c.lexeme;
        //change scope to whatever it is currently
        s.scope = scope;
        st->addBaseSymbol(s);
    }
    void genSynError(token& c, string expected){
        cout << c.line_num << ": Found \"" << c.lexeme << "\" expecting \""<< expected << "\"" << endl;
        //exit program
        exit(1);
    }
    void checkSemiColon(token& c){
        if(c.lexeme != ";")
            genSynError(c, ";");
    }
    void compilation_unit(token&c, token&n){
        //********************* {class_declaration} "void" "kxi2019" "main" "(" ")" method_body
        scope = GLOBAL;
        while(c.lexeme != "void")
            class_declaration(c, n);
        if(c.lexeme != "void")
            genSynError(c, "void");
        getNextToken();
        if(c.lexeme != "kxi2019")
            genSynError(c, "kxi2019");
        getNextToken();
        if(c.lexeme != "main")
            genSynError(c, "main");
        push_scope(scope,c.lexeme);
        getNextToken();
        if(c.type != parentho)
            genSynError(c, "(");
        getNextToken();
        if(c.type != parenthc)
            genSynError(c, ")");
        getNextToken();
        method_body(c, n);
        pop_scope(scope);
    }
    void class_declaration(token&c, token&n){
        //********************** "class" class_name "{" {class_member_declaration} "}"
        if(c.lexeme != "class")
            genSynError(c, "class");
        getNextToken();
        if(syntax)
            addClass(c);
        push_scope(scope,c.lexeme);
        if(c.type != id)
            genSynError(c, "class_name identifier");
        getNextToken();
        if(c.type != blockb)
            genSynError(c, "{");
        getNextToken();
        while(c.type != blocke)
            class_member_declaration(c, n);
        if(c.type != blocke)
            genSynError(c, "}");
        getNextToken();
        pop_scope(scope);
    }
    void class_member_declaration(token& c, token& n){
        //************** modifier type identifier field_declaration | constructor declaration
        if(c.lexeme == PRIVATE || c.lexeme == PUBLIC){
            if(syntax)
                s.data.accessMod = c.lexeme;
            getNextToken();
            if(!type(c,n))
                if(c.type != id && n.type != id)
                    genSynError(c, "type or class_name identifier");
            if(syntax)
                s.data.type = c.lexeme;
            getNextToken();
            if(c.type != id)
                genSynError(c, "identifier");
            if(syntax)
                s.value = c.lexeme;
            push_scope(scope,c.lexeme);
            getNextToken();
            field_declaration(c, n);
        }
        else if (c.type == id && n.type == parentho){
            constructor_declaration(c, n);
        }
        else
            genSynError(c, "access modifier or class_name indentifer ");
    }
    void field_declaration(token& c, token& n){
        //************* ["[" "]"] ["=" assignment_expression ] ";" | "(" [parameter_list] ")" method_body
        if(c.type == parentho){
            if(syntax)
                s.scope = scope;
            getNextToken();
            if(c.type != parenthc)
                parameter_list(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            getNextToken();
            if(syntax){
                s.kind = METHOD;
                st->addBaseSymbol(s);
            }
            method_body(c, n);
            pop_scope(scope);
        }
        else{
            pop_scope(scope);
            if(c.type == arrayb){//***********
                getNextToken();
                if(c.type != arraye)
                    genSynError(c, "]");
                getNextToken();
                if(syntax)
                    s.data.type += ARRAY;
            }
            if(syntax){
                s.kind = IVAR;
                s.scope = scope;
                st->addBaseSymbol(s);
            }
            if(c.type == assop){
                getNextToken();
                assignment_expression(c, n);
            }
            checkSemiColon(c);
            getNextToken();
        }
        
    }
    void constructor_declaration(token& c, token& n){
        // *************** class_name "(" [parameter_list] ")" method_body
        if(c.type != id)
            genSynError(c, "class_name identifier");
        if(syntax){
            s.scope = scope;
            s.kind = CONSTR;
            s.value = c.lexeme;
            s.data.type = c.lexeme;
            s.data.accessMod = PUBLIC;
        }
        push_scope(scope,c.lexeme);
        getNextToken();
        if(c.type != parentho)
            genSynError(c, "(");
        getNextToken();
        if(c.type != parenthc)
            parameter_list(c, n);
        if(c.type != parenthc)
            genSynError(c, ")");
        getNextToken();
        if(syntax)
            st->addBaseSymbol(s);
        method_body(c, n);
        pop_scope(scope);
    }
    void method_body(token& c, token& n){
        //******************** "{" {variable_declaration} {statement} "}"
        if(c.type != blockb)
            genSynError(c, "{");
        getNextToken();
        while(c.type != blocke){
            if(c.lexeme == "int" || c.lexeme == "char" || c.lexeme == "void" || c.lexeme == "bool" || c.lexeme == "sym" )
                variable_declaration(c, n);
            else if(c.type == id && n.type == id)
                variable_declaration(c, n);
            else
                statement(c, n);
        }
        getNextToken();
    }
    void variable_declaration(token& c, token& n){
        type(c, n);//***************** type identifier ["[" "]"] ["=" assignment_expression ] ";"
        //set s type, value, change to array if need be and push before assignment call
        if(syntax)
            s.data.type = c.lexeme;
        getNextToken();
        if(c.type != id)
            genSynError(c, "identifier");
        if(syntax)
            s.value = c.lexeme;
        getNextToken();
        if(c.type == arrayb){
            if(syntax)
                s.data.type += ARRAY;
            getNextToken();
            if(c.type != arraye)
                genSynError(c, "]");
            getNextToken();
        }
        if(syntax){
            s.kind = LVAR;
            s.data.accessMod = PRIVATE;
            s.scope = scope;
            st->addBaseSymbol(s);
        }
        if(c.type == assop){
            getNextToken();
            assignment_expression(c, n);
        }
        checkSemiColon(c);
        getNextToken();
    }
    void numeric_literal(token& c){
        //************* ["+" | "-"]number ;
        if(c.lexeme == "+"){
            getNextToken();
            if(c.type != numb)
                genSynError(c, "number");
        }
        else if (c.lexeme == "-"){
            getNextToken();
            if(c.type != numb)
                genSynError(c, "number");
            //add negative to number
            c.lexeme = "-"+c.lexeme;
        }
        else{
            if(c.type != numb)
                genSynError(c, "number");
        }
        if(syntax)
            addLit(c);
        getNextToken();
    }
    void parameter_list(token& c, token& n){
        //*********** parameter { "," parameter }
        parameter(c, n);
        while(c.lexeme == ","){
            getNextToken();
            parameter(c, n);
        }
    }
    void parameter(token&c, token&n){
        //************** type identifier ["[" "]"] ;
        sym temp;//add all info and add to st
        //take symid and add to s.param
        if(!type(c,n) && (c.type != id && n.type != id))
            genSynError(c, "type or class_name");
        if(syntax)
            temp.data.type = c.lexeme;
        getNextToken();
        if(c.type != id)
            genSynError(c, "identifier");
        if(syntax)
            temp.value = c.lexeme;
        getNextToken();
        if(c.type == arrayb){
            if(syntax)
                temp.data.type += ARRAY;
            getNextToken();
            if(c.type != arraye)
                genSynError(c, "]");
            getNextToken();
        }
        if(syntax){
            temp.kind = PARAM;
            temp.scope = scope;
            temp.data.accessMod = PRIVATE;
            temp.symid = st->genSymID(temp.value.at(0));
            st->addSymbol(temp);
            s.data.param.push_back(temp.symid);
        }
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
            checkSemiColon(c);
            getNextToken();
        }
        else if (c.lexeme == "cout"){
            getNextToken();//****************** "cout" "<<" expression ";"
            if(c.lexeme != "<<")
                genSynError(c, "<<");
            getNextToken();
            expression(c, n);
            checkSemiColon(c);
            getNextToken();
        }
        else if(c.lexeme == "cin"){
            getNextToken();//****************** "cin" ">>" expression ";"
            if(c.lexeme != ">>")
                genSynError(c, ">>");
            getNextToken();
            expression(c, n);
            checkSemiColon(c);
            getNextToken();
        }
        else if(c.lexeme == "switch"){
            getNextToken();//*********************"switch" "(" expression ")" case_block
            if(c.type != parentho)
                genSynError(c, "(");
            getNextToken();
            expression(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            getNextToken();
            case_block(c, n);
        }
        else if(c.lexeme == "break"){
            getNextToken();
            checkSemiColon(c);
            getNextToken();
        }
        else{//***************** expression ";" #EOE
            expression(c, n);
            checkSemiColon(c);
            getNextToken();
            if(semantic)
                EOE();
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
        else if(c.lexeme == "true" || c.lexeme == "false" || c.lexeme == "null" || c.type == charact){//**************| "true" [expressionz] | "false" [expressionz] | "null" [expressionz] | char_literal [expressionz]
            if(syntax)
                addLit(c);
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
        else if(c.type == id){//************* | identifier #iPush [fn_arr_member] #iExist [member_refz] [expressionz]
            if(semantic){
                //iPush
                iPush(c);
            }
            getNextToken();
            if(c.type == parentho || c.type == arrayb)
                fn_arr_member(c, n);
            if(semantic){
                //iExist
                iExist();
            }
            if(c.lexeme == ".")
                member_refz(c,n);
            if(c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop )
                expressionz(c,n);
        }
        else if(c.type == numb || c.lexeme == "-" || c.lexeme == "+"){
            //************** number literal [expressionz]
            numeric_literal(c);
            if (c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop)
                expressionz(c, n);
        }
        else
            genSynError(c, "valid expression");
            
    }
    void expressionz(token& c, token& n){
        if(c.type == mathop || c.type == relop || c.type == logicop ){//************** "+" expression | "-" expression | "*" expression | "&&" expression | "||" expression | "==" expression | "!=" expression | "<=" expression | ">=" expression | "<" expression | ">" expression
            //oPush
            if(semantic)
                oPush(c);
            getNextToken();
            expression(c, n);
        }
        
        else if (c.type == assop ){// | "=" #oPush assignment_expression
            if(semantic)
                oPush(c);
            getNextToken();
            assignment_expression(c,n);
        }
        else
            genSynError(c, "binary expression operator");
    }
    void assignment_expression(token& c, token& n){
        if(syntax)
            s.clear();//start new for the right side of assop
        if(c.lexeme == "new"){//*************** "new" type new_declaration
            getNextToken();
            if(!type(c,n) && c.type != id)
                genSynError(c, "type");
            if(syntax)
                s.value = c.lexeme + LITERAL;
            getNextToken();
            new_declaration(c, n);
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
    void new_declaration(token& c, token& n){
        if(c.type == parentho){//************* "(" [ argument_list ] ")"
            getNextToken();
            if(c.type != parenthc)
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
    void fn_arr_member(token& c, token& n){
        if(c.type == parentho){//************* "(" #oPush #BAL [ argument_list ] ")" #) #EAL #func | "[" #oPush expression "]" #] #arr
            if(semantic){
                oPush(c);
                BAL();
            }
            getNextToken();
            if(c.type != parenthc)
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
        if(c.lexeme != ".")//"." identifier #iPush [ fn_arr_member ] #rExist [ member_refz ] ;
            genSynError(c, ".");
        getNextToken();
        if(c.type != id)
            genSynError(c, "identifier");
        if(semantic)
            iPush(c);
        getNextToken();
        if(c.type == parentho || c.type == arrayb)
            fn_arr_member(c, n);
        if(semantic)
            rExist();
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
    void case_block(token&c, token&n){
        //*************** "{" {case_label} "}"
        if(c.type != blockb)
            genSynError(c, "{");
        getNextToken();
        while(c.type != blocke)
            case_label(c, n);
        if(c.type != blocke)
            genSynError(c, "}");
        getNextToken();
    }
    void case_label(token&c,token&n){
        if(c.lexeme != "case")//*************** "case" literal ":" statement
            genSynError(c, "case");
        getNextToken();
        literal(c);
        if(c.lexeme != ":")
            genSynError(c, ":");
        getNextToken();
        statement(c, n);
    }
    void literal(token&c){
        //************** charact | numb
        if(c.type == charact){
            if(syntax)
                addLit(c);
            getNextToken();
        }
        else if(c.type == numb || c.lexeme == "+" || c.lexeme == "-")
            numeric_literal(c);
        else
            genSynError(c, "character or number literal");
    }
    //checks only type keywords, not class_names
    bool type(token&c,token&n){
        if(c.lexeme != "int" && c.lexeme != "char" && c.lexeme != "void" && c.lexeme != "bool" && c.lexeme != "sym")
                return false;
        return true;
    }
    void passOne(std::string filename){
        //Lexical Analysis
        in.open(filename, ios::in);
        if (in.is_open()){
            std::getline(in,buffer);//read in first line
            line_number = 1;
            updateNext(one,two);//sets the first token read in to token "two"
            nextToken(one, two);//gets the next token and puts it in "two", sets one to two
            lexicalAnalysis(one, two);//repeats process to get the first whole token
            next = one;//saves first whole token to next
            getNextToken();//sets curr to next, gets next whole token
            semantic = false;
            syntax = true;
            compilation_unit(curr, next);//Calls syntax analysis
            if(curr.type != eof)
                genSynError(curr, "EOF");
            st->removeDup();
            st->printST();
            in.close();
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
    //Semantic Pass
    void passTwo(std::string filename){
        in.open(filename,ios::in);
        if(in.is_open()){
            //read in first line
            std::getline(in,buffer);//read in first line
            line_number = 1;
            updateNext(one,two);//sets the first token read in to token "two"
            nextToken(one, two);//gets the next token and puts it in "two", sets one to two
            lexicalAnalysis(one, two);//repeats process to get the first whole token
            next = one;//saves first whole token to next
            getNextToken();//sets curr to next, gets next whole token
            semantic = true;//do semantic operations on next pass through
            syntax = false;
            compilation_unit(curr, next);
        }
        else{
            cout << "Error opening file." << endl;
        }
        
    }
};
