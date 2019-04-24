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

static bool semantic;
static bool syntax;


class compiler {
    //Class Level Variables****************************************************************************************************************************
    string scope;
    const string IVAR = "ivar";
    const string LVAR = "lvar";
    const string LITERAL = "lit";
    const string CHAR = "char";
    const string INT = "int";
    const string BOOL = "bool";
    const string VOID = "void";
    const string nul = "null";
    const string GLOBAL = "g";
    const string ARRAY = ":@";
    const string PARAM = "param";
    const string METHOD = "method";
    const string CONSTR = "constructor";
    const string PUBLIC = "public";
    const string PRIVATE = "private";
    const string OBJECT = "object";
    const string TEMP = "tval";
    const string FUNC = "func";
    const string THIS = "this";
    const string REF = "reference";
    const string CLASS = "class";
    const static int SIZEINT = 4;
    const static int SIZEBYT = 1;
    const string BYT_SIZE = "BYT_SIZE";
    const string INT_SIZE = "INT_SIZE";
    const int DEFAULT_FUNC_SIZE = 12;
    vector<string> types;
    map<string,int> size_types;
    map<string,int> func_types;
    size_t line_number;
    fstream in;
    string buffer;
    map<string,int> KEYWORDS = { std::pair<string,int>("atoi",0), std::pair<string,int>("and",1), std::pair<string,int>("bool",2), std::pair<string,int>("block",3) , std::pair<string,int>("break",4) , std::pair<string,int>("case",5) , std::pair<string,int>("class",6) , std::pair<string,int>("char",7), std::pair<string,int>("cin",8), std::pair<string,int>("cout",9), std::pair<string,int>("default",10), std::pair<string,int>("else",11), std::pair<string,int>("false",12), std::pair<string,int>("if",13) , std::pair<string,int>("int",14) , std::pair<string,int>("itoa",15), std::pair<string,int>("kxi2019",16), std::pair<string,int>("lock",17), std::pair<string,int>("main",18), std::pair<string,int>("new",19), std::pair<string,int>("null",20), std::pair<string,int>("object",21), std::pair<string,int>("or",22), std::pair<string,int>("public",23) , std::pair<string,int>("private",24), std::pair<string,int>("protected",25), std::pair<string,int>("return",26), std::pair<string,int>("release",27), std::pair<string,int>("string",28), std::pair<string,int>("spawn",29), std::pair<string,int>("sym",30), std::pair<string,int>("set",31), std::pair<string,int>("switch",32), std::pair<string,int>("this",33), std::pair<string,int>("true",34), std::pair<string,int>("thread",35), std::pair<string,int>("unprotected",36), std::pair<string,int>("unlock",37), std::pair<string,int>("void",38), std::pair<string,int>("while",39), std::pair<string,int>("wait",40)};
    //ICODE DATA********************************************************************************************************************
    fstream icode;
    string icodeFile = "icode.txt";
    const string DOTINT = ".INT";
    const string DOTBYT = ".BYT";
    const string ADD = "ADD";
    const string MUL = "MUL";
    const string SUB = "SUB";
    const string DIV = "DIV";
    const string LT = "LT";
    const string GT = "GT";
    const string NE = "NE";
    const string EQ = "EQ";
    const string LE = "LE";
    const string GE = "GE";
    const string AND = "AND";
    const string OR = "OR";
    const string MOV = "MOV";
    const string JMP = "JMP";
    const string iFUNC = "FUNC";
    const string NEWI = "NEWI";
    const string FRAME = "FRAME";
    const string CALL = "CALL";
    const string PUSH = "PUSH";
    const string POP = "POP";
    const string PEEK = "PEEK";
    const string RETURN = "RETURN";
    const string RTN = "RTN";
    const string WRITE = "WRITE";
    const string READ = "READ";
    const string iREF = "REF";
    const string AEF = "AEF";
    const string BF = "BF";
    const string BT = "BT";
    const string NEW = "NEW";
    const string SKIPIF = "SKIPIF";
    const string ELSE = "else";
    const string SKIPELSE = "SKIPELSE";
    const string BEGIN = "BEGIN";
    const string ENDWHILE = "ENDWHILE";
    const string COMMA = ",";
    const string IO_ONE = "1";
    const string IO_TWO = "2";
    int label_count;
    vector<string> label_stack;
    //Semantic DATA********************************************************************************************************************
    const string bal_sar = "BAL";
    const string FUNCTION_ERROR = "Function ";
    const string VARIABLE_ERROR = "Variable ";
    const string ARRAY_ERROR = "Array ";
    const string NOT_DEFINED = " not defined";
    //tcode data ********************************************************************************************************************
    fstream tcode;
    string tcodeFile = "tcode.asm";
    const string xINT = ".INT";
    const string xBYT = ".BYT";
    const string MAIN = "MAIN";
    const int REG_SIZE = 14;
    const string REG_0 = "R0";
    const string REG_1 = "R1";
    const string OUT_REG = "R3";
    const string F = "FALSE";
    const string T = "TRUE";
    vector<string> registers[14];
    map<string,vector<string>> stack;
    map<string,vector<string>> heap;
    const string STACK = "STACK";
    const string HEAP = "HEAP";
    const string TYPE = "TYPE";
    const string TRP_INT = "1";
    const string TRP_BYT = "3";
    const string JMR = "JMR";
    const string BNZ = "BNZ";
    const string BGT = "BGT";
    const string BLT = "BLT";
    const string BRZ = "BRZ";
    const string LDA = "LDA";
    const string STR = "STR";
    const string LDR = "LDR";
    const string STB = "STB";
    const string LDB = "LDB";
    const string ADI = "ADI";
    const string CMP = "CMP";
    const string TRP = "TRP";
    const string SL = "SL";
    const string SP = "SP";
    const string FP = "FP";
    const string SB = "SB";
    const string PC = "PC";
    const string OVERFLOW = "OVERFLOW";
    const string UNDERFLOW = "UNDERFLOW";
    const int DEFAULT_FRAME_SIZE = -12;
public:
    compiler(){
        syntax = false;
        semantic = true;
        label_count = 0;
    }
    //Defined Types for tCompiler ****************************************************************************************************************************
    enum Type {space, nl, numb, pchar, charact, id, punct, keyw, mathop,logicop,relop,assop,arrayb,arraye,blockb,blocke,parentho,parenthc,streamop, uk, eof};
    //token class that has a lexeme, line# and type
    struct token {
        string lexeme;
        size_t line_num;
        Type type;
    };
    token curr;
    token next;
    token one;
    token two;
    //Operator Stack
    vector<token> OS;
    struct SAR {
        vector<string> arg_list;
        string value;
        string index;
        size_t ln;
    };
    vector<SAR> SAS;
    struct Data{
        string type;
        string accessMod;
        vector<string> param;
        string size;
        bool pointer;
        void clear(){
            type="";
            accessMod="";
            pointer = false;
            size = "";
            param.clear();
        }
    };
    struct sym{
        string scope;
        string symid;
        string value;
        string kind;
        int size = 0;
        Data data;
        void clear(){
            scope = "";
            symid = "";
            value = "";
            kind = "";
            size = 0;
            data.clear();
        }
    };
    sym s;
    vector<sym> sizeStack;
    class Symboltable {
    public:
        //know
        //symbol counter
        int count;
        //key - > values table
        map<string,sym> symtab;
        //do
        //construct itself
        Symboltable(){
            count = 1;
        };
        //generate symid
        //takes a char and adds the symbol counter to it to create a unique symbol id
        string genSymID(char c){
            if(c=='-'||c=='+'||c=='\''){
                c = 'l';
            }
            string s = "";
            s+=c;
            s+=(to_string(count++));
            return s;
        }
        //add global s variable to the table. also gen symid and clears s after
        sym addBaseSymbol(sym& s){
            //generate symid
            s.symid = genSymID(s.value.at(0));
            sym* temp = new sym(s);
            symtab.insert(std::pair<string,sym>(s.symid,*temp));
            //if method, add parameters to stack
            s.clear();//resets s
            return *temp;
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
        sym fetchObj(string objname, string scope){
            string symid = containsLexeme(objname, scope);
            sym s = fetchSymbol(symid);
            return s;
        }
        //checks to see if duplicate st values are in same scope.
        //takes value and scope
        bool containsDupCurrScope(string value, string sco){
            int symcount = 0;
            for(auto s: symtab){
                if(s.second.scope == sco){
                    if(s.second.value == value){
                        symcount++;
                    }
                }
            }
            if(symcount > 1)
                return true;
            else
                return false;
        }
        string containsLexemeCurrScope(string l, string currscope){
            for(auto x: symtab){
                if(x.second.value == l){
                    if(currscope == x.second.scope){
                        l = x.second.symid;
                        return l;
                    }
                }
            }
            return l;
        }
        vector<sym> getScope(string currscope){
            vector<sym> scopeobjects;
            for(auto x:symtab){
                if(x.second.scope == currscope)
                    scopeobjects.push_back(x.second);
            }
            return scopeobjects;
        }
        //check to see if lexeme exists in current scope, or outer scope, returns symid
        string containsLexeme(string l, string currscope){
            string k = l;
            while(currscope != "g"){
                k = containsLexemeCurrScope(l, currscope);
                pop_scope(currscope);
                if(k!=l)
                    return k;
            }
            l = containsLexemeCurrScope(l, currscope);
            return l;
        }
        void printST(){
            for(auto s:symtab){
                /*cout << "Symid: " << s.second.symid << endl;
                
                cout << "Scope: " << s.second.scope << endl;
                cout << "Kind: " << s.second.kind << endl;
                 
                cout << "Value: " << s.second.value << endl;
                cout << "\tType: " << s.second.data.type << endl;
                
                cout << "\tAccessMod: " << s.second.data.accessMod << endl;
                cout << "\tParam: ";
                 
                cout << "Size: " << s.second.size << endl;
                 for(auto p: s.second.data.param){
                    cout << p << " ";
                }
                 
                cout << endl;
                
                cout << "\tSize: " << s.second.data.size << endl;
                cout << endl;
                */
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
    Symboltable* st = new Symboltable();
    //METHODS****************************************************************************************************************************
    //LEXICAL ANALYISIS****************************************************************************************************************************
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
            nextToken(c, n);
            if(c.type == eof)
                return;
        }
        while (c.type == space || c.type == nl || c.lexeme == "\t" || c.lexeme == "\r")
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
    //iCODE FUNCTIONS **************************************************************************************************************************
    void iCodeGen(string operation, string a_symid, string b_symid, string c_symid){
        icode << "\t" << operation + " " << a_symid << COMMA + " " << b_symid << COMMA + " "<< c_symid << "\n";
    }
    void iCodeGen(string operation, string a_symid, string b_symid){
        icode << "\t" << operation + " " << a_symid << COMMA + " " << b_symid << "\n";
    }
    void iCodeGen(string operation, string label){
        icode << "\t" << operation + " " << label << "\n";
    }
    void iCodeGen(string label){
        icode << "\n" << label + ":";
    }
    string genLabel(string start){
        string label = start + to_string(st->count++);
        return label;
    }
    string pop_label_stack(){
        string label = label_stack.back();
        label_stack.pop_back();
        return label;
    }
    string opcheck(string op){
        if(op == "<")
            return LT;
        else if (op == ">")
            return GT;
        else if (op == "!=")
            return NE;
        else if (op == "==")
            return EQ;
        else if (op == "<=")
            return LE;
        else if (op == ">=")
            return GE;
        else if (op == "&&")
            return AND;
        else
            return OR;
    }
    void __backpatch(char c,size_t pos,string label){
        //backpatch
        size_t len = -1;
        while(c!='\n'){
            icode.seekg(--pos);
            c = icode.get();
            len++;
        }
        char temp[256];
        icode.get(temp,len,':');
        string label_to_replace = temp;
        //replace label with label_to_replace in whole file
        icode.seekg(0);
        string buffer;
        string final_buffer = "";
        len = label_to_replace.length();
        while(getline(icode,buffer)){
            while (true)
            {
                size_t pos = buffer.find(label_to_replace);
                if (pos != string::npos)
                    buffer.replace(pos, len, label);
                else
                    break;
            }
            final_buffer += buffer + "\n";
        }
        final_buffer.erase(final_buffer.length()-1,final_buffer.length());
        icode.close();
        icode.open(icodeFile,ios::in|ios::out|ios::trunc);
        icode << final_buffer;
    }
    void __skip(){
        if(curr.lexeme == ELSE){//check if there is an else
            string label = genLabel(SKIPELSE);
            iCodeGen(JMP, label );//if there is an else, put jmp skipelse
            string label1 = pop_label_stack();
            iCodeGen(label1);
            label_stack.push_back(label);
        }
        else{
            string label = pop_label_stack();
            iCodeGen(label);
        }
    }
    void __if(string s){
        string label = genLabel(SKIPIF);
        label_stack.push_back(label);
        iCodeGen(BF, s, label);
    }
    void __else(){
        //get previous char
        size_t pos = icode.tellg();
        icode.seekg(pos-1);
        char c = icode.get();
        icode.seekg(pos);
        string label = pop_label_stack();
        if(c == ':'){
            __backpatch(c, pos, label);
        }
        else{
            iCodeGen(label);
        }
    }
    void __while(string s){
        string label = genLabel(ENDWHILE);
        label_stack.push_back(label);
        iCodeGen(BF, s, label);
    }
    void __begin(){
        size_t pos = icode.tellg();
        icode.seekg(pos-1);
        char c = icode.get();
        icode.seekg(pos);
        if(c == ':'){
            string label = genLabel(BEGIN);
            label_stack.push_back(label);
            __backpatch(c, pos,label);
        }
        else{
            string label = genLabel(BEGIN);
            label_stack.push_back(label);
            iCodeGen(label);
        }
    }
    void __end(){
        string endlabel = pop_label_stack();
        string beglabel = pop_label_stack();
        iCodeGen(JMP, beglabel);
        iCodeGen(endlabel);
    }
    void __declareFunc(string s){
        iCodeGen(s);
        iCodeGen(iFUNC, s);
    }
    void __func(string symid,SAR top_sar,string object){
        iCodeGen(FRAME, symid, object);
        for(auto s: top_sar.arg_list){
            iCodeGen(PUSH, s);
        }
        iCodeGen(CALL, symid);
        sym f = st->fetchSymbol(symid);
        if(f.data.type!=VOID){
            iCodeGen(PEEK, top_sar.value);
        }
    }
    //Semantic Functions******************************************************************************************************************
    //precedence
    int stackprecedence(token t){
        if(t.lexeme == "*" || t.lexeme == "/")
            return 13;
        else if (t.lexeme == "+" || t.lexeme == "-")
            return 11;
        else if (t.lexeme == "<" || t.lexeme == "<=" || t.lexeme == ">" || t.lexeme == ">=")
            return 9;
        else if (t.lexeme == "==" || t.lexeme == "!=")
            return 7;
        else if (t.lexeme == "&&")
            return 5;
        else if (t.lexeme == "||")
            return 3;
        else if (t.lexeme == "=")
            return 1;
        else if (t.lexeme == "(" || t.lexeme == "." || t.lexeme == "[")
            return -1;
        else if (t.lexeme == ")" || t.lexeme == "]")
            return 0;
        else
            return 0;
    }
    int inputprecedence(token t){
        if(t.lexeme == "*" || t.lexeme == "/")
            return 13;
        else if (t.lexeme == "+" || t.lexeme == "-")
            return 11;
        else if (t.lexeme == "<" || t.lexeme == "<=" || t.lexeme == ">" || t.lexeme == ">=")
            return 9;
        else if (t.lexeme == "==" || t.lexeme == "!=")
            return 7;
        else if (t.lexeme == "&&")
            return 5;
        else if (t.lexeme == "||")
            return 3;
        else if (t.lexeme == "=")
            return 1;
        else if (t.lexeme == "(" || t.lexeme == "." || t.lexeme == "[")
            return 15;
        else if (t.lexeme == ")" || t.lexeme == "]")
            return 0;
        else
            return 0;
    }
    //Semantic Action Stack
    string formatFunc(SAR sar, string value){
        value += "(";
        for(int i = int(sar.arg_list.size()-1); i >= 0; i--){
            if(i != int(sar.arg_list.size()-1))
                value += ", ";
            //fetch param
            sym param = st->fetchSymbol(sar.arg_list[i]);
            value += param.data.type;
        }
        value += ")";
        return value;
    }
    void genSemError(SAR sar, string value, string s){
        cout << sar.ln <<  ": ";
        if(!sar.arg_list.empty()){
            cout << FUNCTION_ERROR;
            //get parameters
            value = formatFunc(sar, value);
            cout << value;
        }
        //array
        else if (sar.index != "")
            cout << ARRAY_ERROR + value;
        //variable
        else
            cout << VARIABLE_ERROR + value;
        cout << s <<  "." << endl;
        exit(1);
    }
    void genSemError(string t1, string l1, string t2, string l2,token op){
        cout << op.line_num <<  ": Invalid Expression ";
        cout << t1 + " " + l1 + " " + op.lexeme + " " + t2 + " " + l2 + "." << endl;
        exit(1);
    }
    void genSemError(string s, SAR sar){
        cout << sar.ln << ": " << s + "." << endl;
        exit(1);
    }
    SAR popSAS(){
        SAR s = SAS.back();
        SAS.pop_back();
        return s;
    }
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
        SAR s;
        s.value = c.lexeme;
        s.ln = c.line_num;
        s.index = "";
        SAS.push_back(s);
    }
    //lpush
    void lPush(token& c){
        SAR lit_sar;
        string temp = st->containsLexeme(c.lexeme, GLOBAL);
        lit_sar.value = temp;
        lit_sar.ln = line_number;
        lit_sar.index ="";
        SAS.push_back(lit_sar);
    }
    //oPush
    void oPush(token& c){
        //check precedence with curr and top of stack. If top of stack is high then run a "#op"
        if(!OS.empty()){//something on the stack
            if(inputprecedence(c)>stackprecedence(peekOS()))
               OS.push_back(c);
            else{
                p_op();//pop back operator
                //push current operator on the stack
                OS.push_back(c);
            }
        }
        else
            OS.push_back(c);
    }
    //#tPush
    void tPush(token& c){
        SAR type_sar;
        type_sar.value = c.lexeme;
        type_sar.ln = c.line_num;
        type_sar.index ="";
        SAS.push_back(type_sar);
    }
    //vPush
    void vPush(token& c){
        SAR s;
        s.value = st->containsLexeme(c.lexeme, scope);
        s.ln = c.line_num;
        s.index = "";
        SAS.push_back(s);
        //f FUNC f
        sym func = st->fetchSymbol(s.value);
        if(func.kind == METHOD){
            __declareFunc(s.value);
        }
    }
    //iExist
    void iExist(){
        //pop the top SAR off the SAS
        SAR top_sar = popSAS();
        //test if the SAR exists in the current scope.
        string temp = st->containsLexeme(top_sar.value, scope);
        if(top_sar.value != temp){
        //if exists, push id_sar onto the SAS
            //if is an array with an index, create temp value
            sym var = st->fetchSymbol(temp);
            if(top_sar.index != ""){
                string type =var.data.type;
                size_t pos = type.find(":");
                if(pos == string::npos)
                    genSemError(top_sar, top_sar.value, NOT_DEFINED);
                type.erase(pos,type.length());
                sym t;
                addTemp2ST(t, type);
                top_sar.value = t.symid;
                //Array iCOde
                iCodeGen(AEF, var.symid, top_sar.index, t.symid);
            }
            else if(!top_sar.arg_list.empty()){
                //fetch temp and compare parameters with top_sar parameters to check them
                int i = int(top_sar.arg_list.size()-1);
                int j = 0;
                while(i >= 0){
                    if(top_sar.arg_list.size() != var.data.param.size())
                        genSemError(top_sar, top_sar.value, NOT_DEFINED);
                    sym param1 = st->fetchSymbol(top_sar.arg_list[i]);
                    sym param2 = st->fetchSymbol(var.data.param[j]);
                    if(param1.data.type != param2.data.type)
                        genSemError(top_sar, top_sar.value, NOT_DEFINED);
                    i--;
                    j++;
                }
                top_sar.value = temp;
            }
            else{
                top_sar.value = temp;
            }
            top_sar.index = "";
            SAS.push_back(top_sar);
            //iCODE
            if(var.kind == METHOD){
                //create temp to store return value in.
                sym t;
                addTemp2ST(t, var.data.type);
                top_sar.value = t.symid;
                __func(var.symid,top_sar,THIS);
                popSAS();
                SAS.push_back(top_sar);
            }
        }
        else{
            genSemError(top_sar, top_sar.value, NOT_DEFINED);
        }
    }
    //#rexist
    void rExist(){
        //pop top sar from sas
        SAR top_sar = popSAS();
        //pop next sar
        SAR next_sar = popSAS();
        //is top sar a public member of next sar?
        sym t = st->fetchSymbol(next_sar.value);
        string s = GLOBAL;
        push_scope(s, t.data.type);
        string temp = st->containsLexeme(top_sar.value, s);
        sym ref;
        sym arr;
        if(top_sar.value != temp){
        //if yes, push onto SAS
            top_sar.value = temp;
            string tvalue = t.value;
            t = st->fetchSymbol(top_sar.value);
            size_t pos = string::npos;
            pos = t.data.type.find("@");
            if(pos != string::npos && (t.data.accessMod == PUBLIC || tvalue == THIS)){//array
                ref.scope = GLOBAL;
                ref.kind = REF+ARRAY;
                ref.value = t.value;
                ref.data.accessMod = PUBLIC;
                ref.data.type = t.data.type;
                ref.symid = st->genSymID('t');
                //if index!= "" type is not array but array type
                if(top_sar.index != ""){
                    //erase array type
                    size_t pos = ref.data.type.find(":");
                    ref.data.type.erase(pos,ref.data.type.length());
                    //create temp on symbol table with index
                    addTemp2ST(arr, ref.data.type);
                    top_sar.value = arr.symid;
                }
                else
                    top_sar.value = ref.symid;
                addSymbol(ref);
            }
            else if(t.data.accessMod == PUBLIC || tvalue == THIS){//function or variable
                //add top_sar to symbol table
                if(!t.data.param.empty()){//function
                    if(top_sar.arg_list.empty())//param is empty when it shouldnt be
                        genSemError(top_sar, t.value, NOT_DEFINED);
                    if(top_sar.arg_list.size()!=t.data.param.size())
                        genSemError(top_sar, t.value, NOT_DEFINED);
                    //check params
                    int i = int(top_sar.arg_list.size()-1);
                    int j = 0;
                    while(i >= 0){
                        sym param1 = st->fetchSymbol(top_sar.arg_list[i]);
                        sym param2 = st->fetchSymbol(t.data.param[j]);
                        if(param1.data.type != param2.data.type)
                            genSemError(top_sar, t.value, NOT_DEFINED);
                        i--;
                        j++;
                    }
                    top_sar.value = "";
                }
                ref.scope = scope;
                ref.kind = TEMP;
                ref.value = top_sar.value;
                ref.data.accessMod = PUBLIC;
                for(auto p: top_sar.arg_list){
                    ref.data.param.push_back(p);
                }
                ref.data.type = t.data.type;
                ref.symid = st->genSymID('t');
                addSymbol(ref);
                top_sar.value = ref.symid;
            }
            else{
                string s = pop_tail_scope(t.scope);
                if(t.kind == METHOD && top_sar.arg_list.empty())
                    top_sar.arg_list.push_back("\n");
                genSemError(top_sar,t.value, " not definded/public in class " + s);
            }
            //iCode
            if(t.kind == METHOD){//function
                __func(t.symid,top_sar,next_sar.value);
            }
            else if(tvalue == THIS)
                iCodeGen(iREF, tvalue, t.symid, ref.symid);
            else//variable
                iCodeGen(iREF, next_sar.value, t.symid, ref.symid);
            //Additional Array iCOde
            if(pos != string::npos && top_sar.index != ""){
                //AEF top_sar.value, top_sar.index,  ???
                iCodeGen(AEF, ref.symid, top_sar.index, arr.symid);
            }
            top_sar.index = "";
            SAS.push_back(top_sar);
        }
        else{
        //if no, throw sym error
            string s = pop_tail_scope(t.scope);
            genSemError(top_sar,top_sar.value, " not defined/public in class " + t.data.type);
        }
    }
    //#tExist
    string tExist(token& c){
        SAR type_sar = popSAS();
        if (type_sar.value == "int" || type_sar.value == "char" || type_sar.value  == "bool" || type_sar.value == "void" || type_sar.value == "sym")
            return type_sar.value;
        string s = GLOBAL;
        string temp = st->containsLexeme(type_sar.value, s);
        if (temp != type_sar.value)
            return type_sar.value;
        else
            genSemError("Type " + type_sar.value +  NOT_DEFINED, type_sar);
        return type_sar.value;
    }
    //#BAL
    void BAL(){
        SAR s;
        s.value = bal_sar;
        s.index = "";
        SAS.push_back(s);
    }
    //#EAL
    void EAL(){
        SAR s = popSAS();
        SAR al_sar;
        while( s.value != "BAL"){
            al_sar.arg_list.push_back(s.value);
            al_sar.ln = s.ln;
            s = popSAS();
        }
        SAS.push_back(al_sar);
    }
    //#func
    void func(){
        SAR func_sar;
        SAR al_sar = popSAS();
        SAR f = popSAS();
        func_sar.value = f.value;
        func_sar.arg_list = al_sar.arg_list;
        func_sar.ln = f.ln;
        func_sar.index = "";
        SAS.push_back(func_sar);
    }
    //#arr
    void arr(){
        sym index = st->fetchSymbol(popSAS().value);
        SAR arr = popSAS();
        if(index.data.type != INT)
            genSemError("Array requires int index got " + index.data.type, arr);
        arr.index = index.symid;
        SAS.push_back(arr);
    }
    //#if
    void _if(){
        if(SAS.empty()){
            SAR sar;
            sar.ln = line_number;
            genSemError("if requires bool",sar);
        }
        SAR sar = popSAS();
        sym exp = st->fetchSymbol(sar.value);
        if(exp.data.type != BOOL)
            genSemError("if requires bool got " + exp.data.type,sar);
        //iCode
        __if(sar.value);
    }
    //#while
    void _while(){
        SAR sar = popSAS();
        sym exp = st->fetchSymbol(sar.value);
        if(exp.data.type != BOOL)
            genSemError("while requires bool got " + exp.data.type,sar);
        __while(sar.value);
    }
    //#return
    void _return(){
        while (!OS.empty()){
            p_op();//pop off operator stack until its empty
        }
        SAR sar;
        sym exp;
        if(!SAS.empty()){
            sar = popSAS();
            exp = st->fetchSymbol(sar.value);
        }
        else{
            exp.data.type = VOID;
            sar.ln = line_number;
        }
        //get current function with scope
        string name = pop_tail_scope(scope);
        sym func = st->fetchSymbol(st->containsLexeme(name, scope));
        if(exp.data.type != func.data.type){//check to see if expression type is the same as function return type
            if(!class_name(func.data.type) || exp.data.type != "null")
                genSemError("Function requires " + func.data.type + " returned " + exp.data.type,sar);
        }
        if(exp.data.type == VOID)
            iCodeGen(RTN, "");
        else
            iCodeGen(RETURN, exp.symid);
    }
    //#cout
    void _cout(){
        while (!OS.empty()){
            p_op();//pop off operator stack until its empty
        }
        SAR sar = popSAS();
        sym exp = st->fetchSymbol(sar.value);
        //is int or char
        if(exp.data.type != INT && exp.data.type != CHAR)
            genSemError("cout not defined for " + exp.data.type,sar);
        if(exp.data.type == INT)
            iCodeGen(WRITE, IO_ONE, exp.symid);
        else
            iCodeGen(WRITE, IO_TWO, exp.symid);
    }
    //#cin
    void _cin(){
        while (!OS.empty()){
            p_op();//pop off operator stack until its empty
        }
        SAR sar = popSAS();
        sym exp = st->fetchSymbol(sar.value);
        //is int or char
        if(exp.data.type != INT && exp.data.type != CHAR)
            genSemError("cin not defined for " + exp.data.type,sar);
        //can not be lit
        if(exp.kind == LITERAL)
            genSemError("cin not defined for literal",sar);
        if(exp.data.type == INT)
            iCodeGen(READ, IO_ONE, exp.symid);
        else
            iCodeGen(READ, IO_TWO, exp.symid);
    }
    //#newObj
    void newObj(){
        SAR al_sar =popSAS();
        SAR type_sar = popSAS();
        SAR constructor_sar;
        //see if constructor exists in scope of type
        string s = GLOBAL;
        push_scope(s, type_sar.value);
        string temp = st->containsLexemeCurrScope(type_sar.value, s);
        if(temp != type_sar.value){
            //does constructor take argument list
            sym c = st->fetchSymbol(temp);
            if(c.data.param.size() == al_sar.arg_list.size()){
                //check to see if types match up
                int i = int(al_sar.arg_list.size()-1);
                int j = 0;
                while(i>=0){
                    sym x = st->fetchSymbol(c.data.param[i]);
                    sym y = st->fetchSymbol(al_sar.arg_list[j]);
                    if(x.data.type != y.data.type)
                        genSemError("Constructor " + formatFunc(al_sar, type_sar.value) + " not defined",al_sar);
                    i--;
                    j++;
                }
                //create temp sym to represent instance of constructor
                sym temp;
                temp.kind = TEMP;
                temp.scope = scope;
                temp.size = func_types[c.value];
                temp.symid = st->genSymID('t');
                temp.data.type = c.value;
                temp.data.accessMod = PUBLIC;
                temp.data.param = al_sar.arg_list;
                st->addSymbol(temp);
                constructor_sar.value = temp.symid;
                constructor_sar.arg_list = al_sar.arg_list;
                constructor_sar.ln = al_sar.ln;
                constructor_sar.index = "";
                SAS.push_back(constructor_sar);
                //iCode
                //NEWI SIZEOFCAT, NEWTEMP
                sym t;
                addTemp2ST(t, INT);
                //get class symbol
                string _class = st->containsLexeme(type_sar.value,GLOBAL);
                iCodeGen(NEWI, _class, t.symid);
                __func(c.symid, constructor_sar, t.symid);
                return;
            }
        }
        genSemError("Constructor " + formatFunc(al_sar, type_sar.value) + " not defined",type_sar);
    }
    //#newArray
    void newArray(){
        SAR new_sar;
        SAR top_sar = popSAS();
        sym size = st->fetchSymbol(top_sar.value);
        if(size.data.type == INT){
            token t;
            new_sar.value = tExist(t);//is next type sar able to have an array made.
            sym x;
            x.value = new_sar.value;
            x.kind = TEMP;
            x.scope = scope;
            x.data.type = new_sar.value + ARRAY;
            x.data.size = size.symid;
            x.data.accessMod = PUBLIC;
            x.symid = st->genSymID('t');
            new_sar.value = x.symid;
            addSymbol(x);
            new_sar.index = "";
            new_sar.ln = top_sar.ln;
            SAS.push_back(new_sar);
            //iCode
            sym temp;
            addTemp2ST(temp, x.data.type);
            //mul sizeofpointer, top_sar.value, new temp variable
            iCodeGen(MUL, x.value, top_sar.value, temp.symid);
            //NEW, new temp variable, new new temp variable
            iCodeGen(NEW, temp.symid, x.symid);
        }
        else{
            genSemError("Array requires int index, got " + size.data.type,top_sar);
        }
        
    }
    //#CD
    void CD(token& t){
        //check that this lexeme matches the name of the class
        //get name of the class
        string name = pop_tail_scope(scope);
        if(t.lexeme != name){
            SAR sar;
            sar.ln = t.line_num;//pass in line num
            genSemError("Constructor " + t.lexeme + " must match class name " + name,sar);
        }
        //get constructor symid
        string symid = st->containsLexeme(name, scope);
        __declareFunc(symid);
    }
    //#dup
    void dup(token& c, string s){
        //check that current lexeme is not a duplicate in current scope
        if(st->containsDupCurrScope(c.lexeme, s)){
            //get sym
            sym t = st->fetchSymbol(st->containsLexeme(c.lexeme, s));
            SAR sar;
            sar.ln = c.line_num;//
            if(t.kind == "class")//array
                genSemError("Duplicate class " + t.value,sar);
            else if(t.kind == METHOD || !t.data.param.empty())//function
                genSemError("Duplicate function " + t.value,sar);
            else //variable
                genSemError("Duplicate variable " + t.value,sar);
        }
        
    }
    //#switch implementation goes here
    /*void _switch(){
    }*/
    //#)
    void pparenc(){
        token t = peekOS();
        while(t.lexeme != "("){
            p_op();
            t=peekOS();
        }
        popOS();//pop off the "("
    }
    //#]
    void parraye(){
        token t = peekOS();
        while(t.lexeme != "["){
            p_op();
            t=peekOS();
        }
        popOS();//pop off the "["
    }
    //#,
    void pcomma(){
        token t = peekOS();
        while(t.type != parentho){
            p_op();
            t=peekOS();
        }
    }
    //#EOE
    void EOE(){
        while (!OS.empty()){
            p_op();//pop off operator stack until its empty
        }
        SAS.clear();
    }
    //#op
    token p_op(){
        token t = popOS();
        if(t.type == assop){//#=
            passop(t);
        }
        //#*
        else if(t.lexeme == "*")
            pmultop(t);
        //#/
        else if(t.lexeme == "/")
            pdivop(t);
        else if(t.lexeme == "-")
            psubtr(t);
        else if (t.lexeme == "+")
            paddop(t);
        else if (t.lexeme == ")")
            pparenc();
        else if (t.lexeme == "]")
            parraye();
        else if (t.lexeme == ",")
            pcomma();
        else if (t.lexeme == "<" || t.lexeme == ">" || t.lexeme == ">=" || t.lexeme == "<=")
            pcomp(t);
        else if (t.lexeme == "==" || t.lexeme == "!=")
            pequals(t);
        else if (t.lexeme == "||" || t.lexeme == "&&")
            pcompexp(t);
        return t;
    }
    void addTemp2ST(sym& temp, string type){
        temp.kind = TEMP;
        temp.scope = scope;
        temp.data.accessMod = PUBLIC;
        temp.data.type = type;
        temp.symid = st->genSymID('t');
        addSymbol(temp);
    }
    //#+
    void paddop(token t){
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //is x + y valid?
        if(x.data.type != INT || y.data.type != INT)//are x and y both ints?
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        //push x onto SAS to store type of answer
        SAR s;
        sym temp;
        addTemp2ST(temp, INT);
        s.value = temp.symid;
        s.index = "";
        SAS.push_back(s);
        //ICODE generation
        iCodeGen(ADD, x.symid, y.symid, s.value);
    }
    //#-
    void psubtr(token t){
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //is x + y valid?
        if(x.data.type != INT || y.data.type != INT)//are x and y both ints?
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        //push x onto SAS to store type of answer
        SAR s;
        sym temp;
        addTemp2ST(temp, INT);
        s.value = temp.symid;
        s.index = "";
        SAS.push_back(s);
        iCodeGen(SUB, x.symid, y.symid, s.value);
    }
    //#*
    void pmultop(token t){
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //is x*y valid?
        if(x.data.type != INT || y.data.type != INT)//are x and y both ints?
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        //push x onto SAS
        SAR s;
        sym temp;
        addTemp2ST(temp, INT);
        s.value = temp.symid;
        s.index = "";
        SAS.push_back(s);
        iCodeGen(MUL, x.symid, y.symid, s.value);
    }
    //#/
    void pdivop(token t){
        //get y and x from the SAS
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //is x / y valid?
        if(x.data.type != INT || y.data.type != INT)//are x and y both ints?
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        //push x onto SAS
        SAR s;
        sym temp;
        addTemp2ST(temp, INT);
        s.value = temp.symid;
        s.index = "";
        SAS.push_back(s);
        iCodeGen(DIV, x.symid, y.symid, s.value);
    }
    //#=
    void passop(token t){//#=
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //is x = y valid?
        if(x.kind == LITERAL)//is x a valid lValue?
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        if(x.data.type != y.data.type){//do x and y share the same type
            if(!class_name(x.data.type) || y.data.type != "null")
                genSemError(x.data.type, x.value, y.data.type , y.value, t);
        }
        
        //iCode
        iCodeGen(MOV, y.symid, x.symid);
    }
    //#< #<= #>= # #>
    //works on only ints and chars
    void pcomp(token t){
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //is x < y valid (int or char)
        if(x.data.type != y.data.type)//do x and y share the same type
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        if(x.data.type != INT && x.data.type != CHAR)//is it either int or char?
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        sym temp;
        SAR t_var;
        addTemp2ST(temp, BOOL);
        t_var.value = temp.symid;
        t_var.index = "";
        SAS.push_back(t_var);
        iCodeGen(opcheck(t.lexeme), x.symid, y.symid, t_var.value);
    }
    //#== #!= works if left side is same as right side
    void pequals(token t){
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //do x and y have same type?
        if(x.data.type != y.data.type){
            if(!class_name(x.data.type) || y.data.type != "null")
                genSemError(x.data.type, x.value, y.data.type , y.value, t);
        }
        sym temp;
        SAR t_var;
        addTemp2ST(temp, BOOL);
        t_var.value = temp.symid;
        SAS.push_back(t_var);
        iCodeGen(opcheck(t.lexeme), x.symid, y.symid, t_var.value);
    }
    //#|| #&& works if both are boolean
    void pcompexp(token t){
        sym y = st->fetchSymbol(popSAS().value);
        sym x = st->fetchSymbol(popSAS().value);
        //are x and y both boolean
        if(x.data.type != BOOL || y.data.type != BOOL)
            genSemError(x.data.type, x.value, y.data.type , y.value, t);
        sym temp;
        SAR t_var;
        addTemp2ST(temp, BOOL);
        t_var.value = temp.symid;
        SAS.push_back(t_var);
        iCodeGen(opcheck(t.lexeme), x.symid, y.symid, t_var.value);
    }
    //SYTNAX FUNCTIONS******************************************************************************************************************
    void addBaseSymbol(sym& s){
        calcSize(s);
        sym temp = st->addBaseSymbol(s);
        if(temp.kind == METHOD || temp.kind == CONSTR){
            for(auto i = temp.data.param.rbegin();i != temp.data.param.rend(); ++i ){
                setStack(st->fetchSymbol(*i));
            }
        }
    }
    void addSymbol(sym& s){
        calcSize(s);
        st->addSymbol(s);
    }
    int calcSize(sym& s){
        if(s.kind == LVAR || s.kind == PARAM || s.kind == TEMP){
            if(size_types.find(s.data.type)!= size_types.end()){
                s.size = size_types[s.data.type];
            }
            else
                s.size = SIZEINT;
        }
        else{
            if(s.data.type == INT){
                s.size = SIZEINT;
            }
            else if (s.data.type == CHAR){
                s.size = SIZEBYT;
            }
            else if (s.data.type == BOOL){
                s.size = SIZEBYT;
            }
            else{
                if(size_types.find(s.data.type)!= size_types.end()){
                    s.size = size_types[s.data.type];
                }
            }
        }
        return s.size;
    }
    void calcObjSize(string currscope){
        //get all symbols in class
        vector<sym> scopeobjects = st->getScope(currscope);
        //add up all the sizes
        int sum = 0;
        for(auto s: scopeobjects){
            if(s.kind == METHOD || s.kind == CONSTR){
                calcObjSize(push_scope_noref(s.scope, s.value));
            }
            else
                sum += s.size;
        }
        //store as size of class
        string objname = pop_tail_scope(currscope);
        string scope = pop_scope(currscope);
        sym obj;
        obj = st->fetchObj(objname,scope);
        st->removeSymbol(obj);
        if(obj.kind == METHOD || obj.kind == CONSTR){
            obj.size = sum + DEFAULT_FUNC_SIZE;
            func_types.insert(pair<string,int>(obj.value,obj.size));
        }
        else{
            obj.size = sum;
            size_types.insert(pair<string,int>(obj.value,obj.size));
        }
        st->addSymbol(obj);
    }
    static string pop_scope(string& s){
        if(s == "g")
            return s;
        size_t pos = s.find_last_of('.');
        s.erase(pos, s.length());
        return s;
    }
    void push_scope(string& s,string temp){
        s += "." + temp;
    }
    string push_scope_noref(string s, string temp){
        s+= "." + temp;
        return s;
    }
    string pop_tail_scope(string s){
        size_t pos = s.find_last_of('.');
        s.erase(0,pos+1);
        return s;
    }
    void addLit(token& c){
        s.clear();
        s.value = c.lexeme;
        s.kind = LITERAL;
        synType(c);
        s.scope = GLOBAL;
        s.data.accessMod = PUBLIC;
        addBaseSymbol(s);
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
        addBaseSymbol(s);
    }
    //takes scope and class name and adds a this to the symbol table at that scope
    void addThis(string s, string name){
        sym t;
        t.data.type = name;
        t.kind = OBJECT;
        t.value = THIS;
        t.scope = s;
        t.data.accessMod = PRIVATE;
        t.symid = st->genSymID('t');
        addSymbol(t);
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
    //RECURSIVE PARSER *****************************************************************************************************************
    void compilation_unit(token&c, token&n){
        //********************* {class_declaration} "void" "kxi2019" "main" "(" ")" method_body
        scope = GLOBAL;
        while(c.lexeme != "void")
            class_declaration(c, n);
        if(semantic){
            OS.clear();
            SAS.clear();
        }
        if(c.lexeme != "void")
            genSynError(c, "void");
        getNextToken();
        if(c.lexeme != "kxi2019")
            genSynError(c, "kxi2019");
        getNextToken();
        if(c.lexeme != "main")
            genSynError(c, "main");
        if(semantic){
            sym m = st->fetchSymbol(st->containsLexeme(c.lexeme, scope));
            __declareFunc(m.symid);
        }
        push_scope(scope,c.lexeme);
        getNextToken();
        if(c.type != parentho)
            genSynError(c, "(");
        getNextToken();
        if(c.type != parenthc)
            genSynError(c, ")");
        getNextToken();
        if(syntax){
            sym m;
            m.scope = GLOBAL;
            m.kind = METHOD;
            m.symid = st->genSymID('m');
            m.value = "main";
            m.data.type = VOID;
            m.data.accessMod = PUBLIC;
            addSymbol(m);
        }
        method_body(c, n);
        if(semantic){
            iCodeGen(RTN,"");
            iCodeGen(MAIN);
            SAR temp;
            sym m = st->fetchSymbol(st->containsLexeme("main", scope));
            __func(m.symid, temp, GLOBAL);
            calcObjSize(scope);
        }
        pop_scope(scope);
    }
    void class_declaration(token&c, token&n){
        //********************** "class" class_name #dup "{" {class_member_declaration} "}"
        if(c.lexeme != "class")
            genSynError(c, "class");
        getNextToken();
        if(syntax){
            addClass(c);
        }
        if(c.type != id)
            genSynError(c, "class_name identifier");
        if(semantic)
            dup(c, scope);
        push_scope(scope,c.lexeme);
        getNextToken();
        if(c.type != blockb)
            genSynError(c, "{");
        getNextToken();
        while(c.type != blocke)
            class_member_declaration(c, n);
        if(c.type != blocke)
            genSynError(c, "}");
        getNextToken();
        //calculate class size
        if(semantic){
            calcObjSize(scope);
        }
        pop_scope(scope);
    }
    void class_member_declaration(token& c, token& n){
        //************** modifier type #tExist identifier #dup field_declaration | constructor declaration
        if(c.lexeme == PRIVATE || c.lexeme == PUBLIC){
            if(syntax)
                s.data.accessMod = c.lexeme;
            getNextToken();
            type(c,n);
            if(syntax)
                s.data.type = c.lexeme;
            if(semantic)
                tExist(c);
            getNextToken();
            if(c.type != id)
                genSynError(c, "identifier");
            if(syntax){
                s.value = c.lexeme;
                s.scope = scope;
            }
            if(semantic){
                dup(c, scope);
                vPush(c);
            }
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
        //************* ["[" "]"] #vPush ["=" #oPush assignment_expression ] ";" #EOE | "(" [parameter_list] ")" method_body
        if(c.type == parentho){
            if(semantic)
                popSAS();//get rid of vPush
            getNextToken();
            if(c.type != parenthc)
                parameter_list(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            getNextToken();
            if(syntax){
                s.kind = METHOD;
                string name = pop_tail_scope(s.scope);
                addThis(scope, name);
                //iterate through param and add to stack.
                addBaseSymbol(s);
            }
            method_body(c, n);
            if(semantic)
                iCodeGen(RTN, "");
            pop_scope(scope);
        }
        else{
            pop_scope(scope);
            if(c.type == arrayb){//*********** ["[" "]"] #vPush ["=" #oPush assignment_expression ] ";" #EOE
                getNextToken();
                if(c.type != arraye)
                    genSynError(c, "]");
                getNextToken();
                if(syntax)
                    s.data.type += ARRAY;
                //#vPush: I did it earlier to get the right token and then popped the sas if it turned out to be a function call
            }
            if(syntax){
                s.kind = IVAR;
                s.scope = scope;
                addBaseSymbol(s);
            }
            if(c.type == assop){
                if(semantic)
                    oPush(c);
                getNextToken();
                assignment_expression(c, n);
            }
            checkSemiColon(c);
            if(semantic)
                EOE();
            getNextToken();
        }
        
    }
    void constructor_declaration(token& c, token& n){
        // *************** class_name #dup #CD "(" [parameter_list] ")" method_body
        if(c.type != id)
            genSynError(c, "class_name identifier");
        if(syntax){
            s.scope = scope;
            s.kind = CONSTR;
            s.value = c.lexeme;
            s.data.type = c.lexeme;
            s.data.accessMod = PUBLIC;
        }
        if(semantic){
            dup(c, scope);
            CD(c);
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
        if(syntax){
            addThis(scope, s.value);
            addBaseSymbol(s);
        }
        method_body(c, n);
        if(semantic)
            iCodeGen(RETURN, THIS);
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
        type(c, n);//***************** type identifier ["[" "]"] #dup #vPush ["=" #oPush assignment_expression ] ";"
        //set s type, value, change to array if need be and push before assignment call
        if(syntax)
            s.data.type = c.lexeme;
        //texist
        if(semantic)
            tExist(c);
        getNextToken();
        if(c.type != id)
            genSynError(c, "identifier");
        if(syntax)
            s.value = c.lexeme;
        if(semantic){
            dup(c,scope);
            vPush(c);
        }
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
            addBaseSymbol(s);
        }
        if(c.type == assop){
            if(semantic)
                oPush(c);
            getNextToken();
            assignment_expression(c, n);
        }
        checkSemiColon(c);
        getNextToken();
        if(semantic)
            EOE();
    }
    void numeric_literal(token& c){
        //************* ["+" | "-"]number #lpush ;
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
        if(semantic)
            lPush(c);
        getNextToken();
    }
    void character_literal(token&c){
        //*************** character #lpush
        if(c.type != charact)
            genSynError(c, "char literal");
        if(semantic)
            lPush(c);
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
        //************** type #tExist identifier ["[" "]"] #dup;
        sym temp;//add all info and add to st
        //take symid and add to s.param
        type(c,n);
        if(syntax)
            temp.data.type = c.lexeme;
        if(semantic)
            tExist(c);
        getNextToken();
        if(c.type != id)
            genSynError(c, "identifier");
        if(syntax)
            temp.value = c.lexeme;
        if(semantic)
            dup(c, scope);
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
            addSymbol(temp);
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
            getNextToken();//************** "if" "(" #oPush expression ")" #) #if $if statement $skip [ "else" statement $else ]
            if(c.type != parentho)
                genSynError(c, "(");
            if(semantic)
                oPush(c);
            getNextToken();
            expression(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            if(semantic){
                pparenc();
                _if();
            }
            getNextToken();
            statement(c, n);
            if(semantic)
                __skip();
            if(c.lexeme == "else"){
                getNextToken();
                statement(c, n);
                if(semantic)
                    __else();
            }
            
        }
        else if(c.lexeme == "while"){
            getNextToken();//***************** "while" $begin "(" #oPush expression ")" #) #while $while statement $end
            if(semantic)
                __begin();
            if(c.type != parentho)
                genSynError(c, "(");
            if(semantic)
                oPush(c);
            getNextToken();
            expression(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            if(semantic){
                pparenc();
                _while();
            }
            getNextToken();
            statement(c, n);
            if(semantic)
                __end();
        }
        else if (c.lexeme == "return"){//************* "return" [ expression ] ";" #return
            getNextToken();
            if(c.lexeme != ";"){
                expression(c, n);
            }
            checkSemiColon(c);
            if(semantic)
                _return();
            getNextToken();
        }
        else if (c.lexeme == "cout"){
            getNextToken();//****************** "cout" "<<" expression ";" #cout
            if(c.lexeme != "<<")
                genSynError(c, "<<");
            getNextToken();
            expression(c, n);
            checkSemiColon(c);
            if(semantic)
                _cout();
            getNextToken();
        }
        else if(c.lexeme == "cin"){
            getNextToken();//****************** "cin" ">>" expression ";" #cin
            if(c.lexeme != ">>")
                genSynError(c, ">>");
            getNextToken();
            expression(c, n);
            checkSemiColon(c);
            if(semantic)
                _cin();
            getNextToken();
        }
        else if(c.lexeme == "switch"){
            getNextToken();//*********************"switch" "(" #oPush expression ")" #)#switch case_block
            if(c.type != parentho)
                genSynError(c, "(");
            if(semantic)
                oPush(c);
            getNextToken();
            expression(c, n);
            if(c.type != parenthc)
                genSynError(c, ")");
            if(semantic){
                pparenc();
                //_switch();
            }
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
        if(c.type == parentho){//************** "(" #oPush expression ")" #) [ expressionz ]
            if(semantic)
                oPush(c);
            getNextToken();
            expression(c, n);
            if(c.type != parenthc){
                genSynError(c, ")");
            }
            if(semantic)
                pparenc();
            getNextToken();
            if(c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop )
                expressionz(c,n);
        }
        else if(c.lexeme == "true" || c.lexeme == "false" || c.lexeme == "null"){//**************| "true" #lPush [ expressionz ] | "false" #lpush [expressionz] | "null" #lpush [expressionz] |
            if(syntax)
                addLit(c);
            if(semantic)
                lPush(c);
            getNextToken();
            if (c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop)
                expressionz(c, n);
        }
        else if(c.lexeme == "this"){
            if(semantic){
                iPush(c);
                iExist(); 
            }
            getNextToken();
            if(c.lexeme == ".")//************ [member_refz]
                member_refz(c,n);
            if(c.type == mathop || c.type == relop ||c.type == assop || c.type == logicop )//************** [expressionz]
                expressionz(c,n);
        }
        else if(c.type == id){//************* | identifier #iPush [fn_arr_member] #iExist [member_refz] [expressionz]
            if(semantic)
                iPush(c);
            getNextToken();
            if(c.type == parentho || c.type == arrayb)
                fn_arr_member(c, n);
            if(semantic)
                iExist();
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
        else if(c.type == charact){
            //*************** character literal [expressionz]
            character_literal(c);
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
            type(c, n);
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
        if(c.type == parentho){//************* "(" #oPush #BAL [ argument_list ] ")" #) #EAL  #newObj
            if(semantic){
                oPush(c);
                BAL();
            }
            getNextToken();
            if(c.type != parenthc)
                argument_list(c,n);
            if(c.type != parenthc)
                genSynError(c, ")");
            if(semantic){
                pparenc();
                EAL();
                newObj();
            }
            getNextToken();
        }
        else if (c.type == arrayb){//************| "[" #oPush expression "]" #] #new[]
            if(semantic)
                oPush(c);
            getNextToken();
            expression(c, n);
            if(c.type != arraye)
                genSynError(c, "]");
            if(semantic){
                parraye();
                newArray();
            }
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
            //#)
            if(semantic){
                pparenc();
                EAL();
                func();
            }
            getNextToken();
        }
        else if (c.type == arrayb){//************| "[" #oPush expression "]" #] #arr
            if(semantic)
                oPush(c);
            getNextToken();
            expression(c, n);
            if(c.type != arraye)
                genSynError(c, "]");
            if(semantic){
                //#]
                parraye();
                //#arr
                arr();
            }
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
            if(semantic)
                pcomma();
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
            character_literal(c);
        }
        else if(c.type == numb || c.lexeme == "+" || c.lexeme == "-")
            numeric_literal(c);
    }
    //checks only type keywords, not class_names
    void type(token&c,token&n){
        //"int" #tPush | "char" #tPush | "bool" #tPush | "void" #tPush | "sym" #tPush | class_name #tPush
        if (c.type == id ||c.lexeme == "int" || c.lexeme == "char" || c.lexeme == "void" || c.lexeme == "bool" || c.lexeme == "sym" ){
            if(semantic)
                tPush(c);
        }
        else
            genSynError(c, "valid type or class name");
    }
    bool class_name(string id){
        if(id != "int" && id != "char" && id != "void" && id != "bool" && id != "sym")
            return true;
        else
            return false;
    }
    //tCode ****************************************************************************************************************************************
    void tCodeDeclare(string id, string type){
        if(type == INT || type == BOOL){
            tcode << id + " " << xINT + " " << 0 << '\n';
        }
        else if(type == CHAR){
            int c = int('a');
            tcode << id + " " << xBYT + " " << c << '\n';
        }
    }
    void tCodeDeclare(string id, string type, string value){
        if(type == INT){
            tcode << id + " " << xINT + " " << value << '\n';
        }
        else if(type == CHAR){
            tcode << id + " " << xBYT + " " << value << '\n';
        }
        else if (type == BOOL){
            if(value == "false")
                value = "0";
            else
                value = "1";
            tcode << id + " " << xINT << " " << value << '\n';
        }
    }
    void tCodeGen(string operation, string a_symid, string b_symid, string c_symid){
        tcode << operation + " " << a_symid << COMMA + " " << b_symid << COMMA + " "<< c_symid << "\n";
    }
    void tCodeGen(string operation, string a_symid, string b_symid){
        tcode << operation + " " << a_symid << COMMA + " " << b_symid << "\n";
    }
    void tCodeGen(string operation, string label){
        tcode << operation + " " << label << "\n";
    }
    void tCodeGen(string label){
        tcode << label << "    ";
    }
    int getParamsize(vector<string> params){
        int sum = 0;
        for(auto p: params){
            sum+=SIZEINT;
        }
        return sum;
    }
    string getOP(string op){
        if(op == EQ)
            op = BRZ;
        else if (op == LT || op == LE)
            op = BLT;
        else if (op == GT || op == GE)
            op = BGT;
        else if (op == NE)
            op = BNZ;
        return op;
    }
    int getIndex(string reg){
        size_t pos = 1;
        reg = reg.erase(0,pos);
        int index = stoi(reg);
        return index;
    }
    int getTypeSize(string type){
        int size = size_types[type];
        return size;
    }
    int getSize(string symid){
        try{
            sym s = st->fetchSymbol(symid);
            return s.size;
        }
        catch(out_of_range e){
            return 0;
        }
    }
    string getRegister(){
        string reg = "R";
        for(int i = 2; i < REG_SIZE; i++){
            if(i == 3)
                continue;
            if(registers[i].empty()){
                reg += to_string(i);
                return reg;
            }
        }
        return reg;
    }
    void setRegister(string reg,string symid){
        int index = getIndex(reg);
        registers[index].push_back(symid);
    }
    void setStack(sym s){
        //assign right offsets to each symbol that comes in
        stack[s.scope].push_back(s.symid);
    }
    pair<string,int> getStack(sym s){
        vector<string> temp = stack[s.scope];
        int offset = DEFAULT_FUNC_SIZE;
        pair<string,int> rv;
        rv.first = "";
        rv.second = -1;
        if(!temp.empty()){
            for(auto t:temp){
                if(t == s.symid){
                    rv.first = STACK;
                    rv.second = offset;
                    return rv;
                }
                else
                    offset += SIZEINT;
            }
        }
        return rv;
    }
    void clearStack(){
        stack.clear();
    }
    void setHeap(sym s){
        heap[s.scope].push_back(s.symid);
    }
    pair<string,int> getHeap(sym s){
        vector<string> temp = heap[s.scope];
        int offset = 0;
        pair<string,int> rv;
        rv.first = "";
        rv.second = -1;
        if(!temp.empty()){
            for(auto t:temp){
                if(t == s.symid){
                    rv.first = HEAP;
                    rv.second = offset;
                    return rv;
                }
                else{
                    offset += SIZEINT;
                }
            }
        }
        return rv;
    }
    void clearHeap(){
        heap.clear();
    }
    pair<string, int> getLocation(string symid){
        pair<string,int> rv;
        try{
            sym s = st->fetchSymbol(symid);
            rv = getStack(s);
            if(rv.second != -1)
                return rv;
        }
        catch(out_of_range e){
            rv.second = -1;
        }
        //check heap
        try{
            sym s = st->fetchSymbol(symid);
            rv = getHeap(s);
            if(rv.second != -1)
                return rv;
        }
        catch(out_of_range e){
            rv.second = -1;
        }
        //check to see if in types
        if(size_types.find(symid)!= size_types.end()){
            rv.first = TYPE;
            rv.second = 0;
        }
        return rv;
    }
    void setPointer(string symid){
        try{
            sym s = st->fetchSymbol(symid);
            s.data.pointer = true;
            st->removeSymbol(s);
            st->addSymbol(s);
        }
        catch(out_of_range e){
            return;
        }
    }
    void clearRegister(string reg){
        int index = getIndex(reg);
        registers[index].clear();
    }
    //finds location of symid and places its address into the register it returns.
    string getOperand(string symid){
        string reg = getRegister();
        if(symid == THIS){
            setRegister(reg, THIS);
            tCodeGen(MOV, reg, FP);
            tCodeGen(ADI, reg, "-8");//this is always stored here on the stack
        }
        else{
            pair<string,int> rv = getLocation(symid);
            setRegister(reg, symid);
            if(rv.second == -1){//in memory
                    tCodeGen(LDA, reg, symid);
            }//if on stack, get a from on stack
            else if(rv.first == TYPE){
                tCodeGen(LDA, reg, symid);
            }
            else if(rv.first == HEAP){
                tCodeGen(MOV, reg, FP);
                tCodeGen(ADI, reg, "-8");
                tCodeGen(LDR, reg, reg);
                tCodeGen(ADI, reg, to_string(rv.second));
            }
            else{
                tCodeGen(MOV, reg, FP);
                tCodeGen(ADI, reg, "-"+to_string(rv.second));
                sym temp = st->fetchSymbol(symid);
                if(temp.data.pointer)
                    tCodeGen(LDR, reg, reg);
            }
        }
        return reg;
    }
    void declareVar(){
        //goes through symbol table and declares all the variables
        vector<string> pointers;
        for(auto s: st->symtab){
            if(s.second.data.pointer){
                pointers.push_back(s.second.symid);
            }
            if(s.second.kind == IVAR ){
                setHeap(s.second);
            }
            else if(s.second.kind == TEMP || s.second.kind == LVAR ){
                setStack(s.second);
            }
            else if(s.second.kind == LITERAL){
                if(s.second.data.type == CHAR){
                    string temp = s.second.value;
                    size_t pos = 0;
                    pos = temp.find_last_of('\'');
                    temp.erase(pos,temp.length());
                    temp.erase(0,1);
                    char t;
                    if(temp == "\\n")
                        t ='\n';
                    else
                        t = temp.at(0);
                    int c = int(t);
                    temp = to_string(c);
                    tCodeDeclare(s.second.symid,s.second.data.type,temp);
                }
                else
                    tCodeDeclare(s.second.symid,s.second.data.type,s.second.value);
            }
        }
        tCodeDeclare(T, INT, "1");
        tCodeDeclare(F, INT, "0");
        for(auto p: pointers){
            sym s = st->fetchSymbol(p);
            st->removeSymbol(s);
            s.data.pointer = false;
            st->addSymbol(s);
        }
        for(auto t: size_types){
            tCodeDeclare(t.first, INT, to_string(t.second));
        }
    }
    
    void tcode_unit(){
        string rega;
        string regb;
        string regc;
        string regd;
        tCodeGen(LDR, REG_0, F);
        tCodeGen(LDR, REG_1, T);
        tCodeGen(JMP, MAIN);
        while(curr.type != eof){
            if(curr.lexeme == MOV){
                getNextToken();//MOV a , b
                rega = getOperand(curr.lexeme);
                tCodeGen(LDR, rega, rega);
                getNextToken();//skip comma
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(STR, rega, regb);
                clearRegister(rega);
                clearRegister(regb);
            }
            else if (curr.lexeme == ADD || curr.lexeme == SUB || curr.lexeme == MUL || curr.lexeme == DIV){
                string op = curr.lexeme;
                getNextToken();//ADD a , b , c
                rega = getOperand(curr.lexeme);
                tCodeGen(LDR, rega, rega);
                getNextToken();
                getNextToken();
                regb=getOperand(curr.lexeme);
                tCodeGen(LDR, regb, regb);
                tCodeGen(op, rega, regb);
                getNextToken();
                getNextToken();
                regc = getOperand(curr.lexeme);
                tCodeGen(STR, rega, regc);
                clearRegister(regb);
                clearRegister(rega);
                clearRegister(regc);
            }
            else if (curr.lexeme == EQ || curr.lexeme == NE || curr.lexeme == LT || curr.lexeme == GT || curr.lexeme == GE || curr.lexeme == LE){
                string operation = curr.lexeme;
                getNextToken();//eq a , b , c
                rega = getOperand(curr.lexeme);
                string a = curr.lexeme;
                tCodeGen(LDR, rega, rega);
                getNextToken();
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(LDR, regb, regb);
                tCodeGen(CMP, rega, regb);
                string l1 = genLabel("l");
                string l2 = genLabel("l");
                string op = getOP(operation);
                tCodeGen(op, rega, l1);
                if(operation == GE || operation == LE){
                    clearRegister(rega);
                    rega = getOperand(a);
                    tCodeGen(LDR, rega, rega);
                    tCodeGen(CMP, rega, regb);
                    tCodeGen(BRZ, rega, l1);
                }
                tCodeGen(MOV, rega, REG_0);
                tCodeGen(JMP, l2);
                tCodeGen(l1);
                tCodeGen(MOV, rega, REG_1);
                tCodeGen(l2);
                getNextToken();
                getNextToken();
                clearRegister(regb);
                regb=getOperand(curr.lexeme);
                tCodeGen(STR, rega, regb);
                clearRegister(rega);
                clearRegister(regb);
            }
            else if (curr.lexeme == AND || curr.lexeme == OR){
                string op = curr.lexeme;
                getNextToken();
                rega = getOperand(curr.lexeme);
                tCodeGen(LDR, rega, rega);
                getNextToken();
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(LDR, regb, regb);
                tCodeGen(op, rega, regb);
                getNextToken();
                getNextToken();
                regc = getOperand(curr.lexeme);
                tCodeGen(STR, rega, regc);
                clearRegister(rega);
                clearRegister(regb);
                clearRegister(regc);
            }
            else if (curr.lexeme == BF || curr.lexeme == BT){
                string op = curr.lexeme;
                getNextToken();//bf a , label
                rega = getOperand(curr.lexeme);
                tCodeGen(LDR, rega, rega);
                getNextToken();
                getNextToken();
                if(op == BF)
                    op = BRZ;
                else
                    op = BNZ;
                tCodeGen(op, rega, curr.lexeme);
                clearRegister(rega);
            }
            else if (curr.lexeme == JMP){
                getNextToken();
                tCodeGen(JMP, curr.lexeme);
            }
            else if (curr.lexeme == WRITE || curr.lexeme == READ){
                string op = curr.lexeme;
                getNextToken();//WRITE i, a
                string i = curr.lexeme;
                getNextToken();
                getNextToken();
                string trp;
                rega = getOperand(curr.lexeme);
                if(i == IO_ONE){
                    tCodeGen(LDR, OUT_REG, rega);
                    if(op == WRITE)
                        trp = TRP_INT;
                    else
                        trp = "2";
                    tCodeGen(TRP, trp);
                    if(op == READ)
                        tCodeGen(STR, OUT_REG, rega);
                }
                else{
                    tCodeGen(LDB, OUT_REG, rega);
                    if(op == WRITE)
                        trp = TRP_BYT;
                    else
                        trp = "4";
                    tCodeGen(TRP, trp);
                    if(op == READ)
                        tCodeGen(STB, OUT_REG, rega);
                }
                clearRegister(rega);
            }
            else if (curr.lexeme == FRAME){
                //FRAME F, X
                getNextToken();
                //Test for overflow (SP < SL) using the space needed for the Frame
                rega = getRegister();
                setRegister(rega, SP);
                tCodeGen(MOV, rega, SP);
                sym s = st->fetchSymbol(curr.lexeme);
                tCodeGen(ADI, rega, "-"+to_string(s.size));
                tCodeGen(CMP, rega, SL);
                tCodeGen(BLT, rega, OVERFLOW);
                clearRegister(rega);
                //SaveoffcurrentFPinaRegister,thiswillbe the PFP
                rega = getRegister();
                setRegister(rega, FP);
                tCodeGen(MOV, rega, FP);
                //PointatCurrentActivationRecord(FP=SP)
                tCodeGen(MOV, FP, SP);
                //AdjustStackPointerforReturnAddress
                tCodeGen(ADI, SP, "-"+to_string(SIZEINT));
                    //Not Stored Yet (See CALL F)
                    //StorePFPtoTopofStack
                tCodeGen(STR, rega, SP);
                //AdjustStackPointerforPFP
                tCodeGen(ADI, SP, "-"+to_string(SIZEINT));
                //StorethispointertoTopofStack
                getNextToken();
                getNextToken();
                //thispointer storage code goes here ************
                pair<string,int> rv = getLocation(curr.lexeme);
                if(rv.second!= -1){
                    regb = getRegister();
                    setRegister(regb, curr.lexeme);
                    tCodeGen(MOV, regb, rega);
                    tCodeGen(ADI, regb, "-"+to_string(rv.second));
                    tCodeGen(LDR, regb, regb);
                    tCodeGen(STR, regb, SP);
                    clearRegister(regb);
                //AdjustStackPointerforthis
                }
                tCodeGen(ADI, SP, "-"+to_string(SIZEINT));
                clearRegister(rega);
            }
            else if (curr.lexeme == iFUNC){
                getNextToken();
                sym s = st->fetchSymbol(curr.lexeme);
                int param_size = getParamsize(s.data.param);
                tCodeGen(ADI, SP, "-"+to_string(s.size-DEFAULT_FUNC_SIZE-param_size));
            }
            else if (curr.lexeme == CALL){
                //CALL F
                getNextToken();
                rega = getRegister();
                tCodeGen(MOV, rega, PC);
                tCodeGen(ADI, rega, "36");
                tCodeGen(STR, rega, FP);
                tCodeGen(JMP, curr.lexeme);
            }
            else if (curr.lexeme == RETURN || curr.lexeme == RTN){
                //RETURN A
                string op = curr.lexeme;
                regc =getRegister();
                setRegister(regc, FP);
                tCodeGen(LDR, regc, FP);
                if(op == RETURN){
                    getNextToken();
                    regd = getOperand(curr.lexeme);
                    tCodeGen(LDR, regd, regd);
                }
                rega = getRegister();
                setRegister(rega, SP);
                regb = getRegister();
                setRegister(regb, SB);
                tCodeGen(MOV, SP, FP);
                tCodeGen(MOV, rega, SP);
                tCodeGen(MOV, regb, SB);
                tCodeGen(CMP, regb, rega);
                tCodeGen(BLT, regb, UNDERFLOW);
                tCodeGen(MOV, rega, FP);
                tCodeGen(ADI, rega, "-"+to_string(SIZEINT));
                tCodeGen(LDR, rega, rega);
                tCodeGen(MOV, FP, rega);
                if(op == RETURN){
                    tCodeGen(STR, regd, SP);
                    tCodeGen(ADI, SP, "-"+to_string(SIZEINT));//move sp to top of stack
                    clearRegister(regd);
                }
                tCodeGen(JMR, regc);
                clearRegister(rega);
                clearRegister(regb);
                clearRegister(regc);
            }
            else if (curr.lexeme == PEEK){
                getNextToken();
                rega = getRegister();
                setRegister(rega, SP);
                regb = getOperand(curr.lexeme);
                tCodeGen(MOV, rega, SP);
                tCodeGen(ADI, rega, to_string(SIZEINT));
                tCodeGen(LDR, rega, rega);
                tCodeGen(STR, rega, regb);
                clearRegister(rega);
                clearRegister(regb);
            }
            else if (curr.lexeme == PUSH){
                getNextToken();
                pair<string,int> rv = getLocation(curr.lexeme);
                if(rv.second == -1){
                    rega = getOperand(curr.lexeme);
                }
                else{
                    sym s = st->fetchSymbol(curr.lexeme);
                    rega = getRegister();
                    setRegister(rega, FP);
                    tCodeGen(MOV, rega, FP);
                    tCodeGen(ADI, rega, "-"+to_string(SIZEINT));
                    tCodeGen(LDR, rega, rega);
                    tCodeGen(ADI, rega, "-"+to_string(rv.second));
                    if(s.data.pointer)
                        tCodeGen(LDR, rega, rega);
                    
                }
                tCodeGen(LDR, rega, rega);
                tCodeGen(STR,rega,SP);
                tCodeGen(ADI,SP, "-"+to_string(SIZEINT));
                clearRegister(rega);
            }
            else if(curr.lexeme == NEWI){
                int size = 0;
                rega = getRegister();
                setRegister(rega, SL);
                tCodeGen(MOV, rega, SL);
                getNextToken();
                size = getSize(curr.lexeme);
                tCodeGen(ADI, SL, to_string(size));
                getNextToken();
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(STR, rega, regb);
                clearRegister(rega);
                clearRegister(regb);
            }
            else if(curr.lexeme == NEW){
                rega = getRegister();
                setRegister(rega,SL);
                tCodeGen(MOV, rega, SL);
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(LDR, regb, regb);
                tCodeGen(ADD, SL, regb);
                clearRegister(regb);
                getNextToken();
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(STR, rega, regb);
                clearRegister(rega);
                clearRegister(regb);
            }
            else if (curr.lexeme == iREF){
                getNextToken();
                rega = getOperand(curr.lexeme);
                tCodeGen(LDR, rega, rega);
                getNextToken();
                getNextToken();
                pair<string,int> offset = getLocation(curr.lexeme);
                tCodeGen(ADI, rega, to_string(offset.second));
                getNextToken();
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(STR, rega, regb);
                clearRegister(rega);
                clearRegister(regb);
                setPointer(curr.lexeme);
            }
            else if(curr.lexeme == AEF){
                getNextToken();
                sym array = st->fetchSymbol(curr.lexeme);
                rega=getOperand(curr.lexeme);
                tCodeGen(LDR, rega, rega);
                getNextToken();
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(LDR, regb, regb);
                string type = array.data.type;
                size_t pos = type.find(":");
                if(pos != string::npos){
                    type = type.erase(pos,type.back());
                }
                regd=getOperand(type);
                tCodeGen(LDR, regd, regd);
                tCodeGen(MUL, regb, regd);
                tCodeGen(ADD, rega, regb);
                clearRegister(regd);
                clearRegister(regb);
                getNextToken();
                getNextToken();
                regb = getOperand(curr.lexeme);
                tCodeGen(STR, rega, regb);
                setPointer(curr.lexeme);
                clearRegister(rega);
                clearRegister(regb);
            }
            else{
                tCodeGen(curr.lexeme);//label
                getNextToken();
            }
            getNextToken();
            if(curr.type == eof)//double check that it is the end of the file. 
                getNextToken();
        }
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
            //st->printST();
            in.close();
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
    //Semantic Pass,iCode, and tCode 
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
            icode.open(icodeFile,ios::in|ios::out|ios::trunc);
            if(icode.is_open()){
                compilation_unit(curr, next);
                icode.close();
            }
            else
                cout << "Error writing to iCode." << endl;
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
    
    //iCode and tCode pass
    string passThree(string filename){
        in.close();
        in.open(filename, ios::in);
        if(in.is_open()){
            std::getline(in,buffer);//read in first line
            line_number = 1;
            updateNext(one,two);//sets the first token read in to token "two"
            nextToken(one, two);//gets the next token and puts it in "two", sets one to two
            lexicalAnalysis(one, two);//repeats process to get the first whole token
            next = one;//saves first whole token to next
            getNextToken();//sets curr to next, gets next whole token
            //set all declared to zero
            size_types.insert(pair<string,int>(INT,4));
            size_types.insert(pair<string,int>(CHAR,1));
            size_types.insert(pair<string,int>(BOOL,4));
            tcode.open(tcodeFile,ios::in|ios::out|ios::trunc);
            declareVar();
            tcode_unit();
            tcode.close();
            in.close();get the message class working!! need allocate space for an array pointer in message the points to the space on the heap
        }
        else
            cout << "ICODE read error." << endl;
        return tcodeFile;
    }
};
