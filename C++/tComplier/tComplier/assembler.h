//
//  assembler.h
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#ifndef assembler_h
#define assembler_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <map>
#include <regex>

using namespace std;

//GLOBAL VARIABLES AND CONSTANTS
const vector<string> OPS = {"JMP","JMR","BNZ","BGT","BLT","BRZ","MOV","LDA","STR","LDR","STB","LDB","ADD","ADI","SUB","MUL","DIV","CMP","TRP","STR1","LDR1","STB1","LDB1"};
const vector<int> OPS_VALUE = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,20,21,22,23,24,25};//corresponds with OPS
const vector<string> DIR = {".INT",".BYT"};
const int JMP = 1;
const int JMR = 2;
const int BNZ = 3;
const int BGT = 4;
const int BLT = 5;
const int BRZ = 6;
const int MOV = 7;
const int LDA = 8;
const int STR = 9;
const int LDR = 10;
const int STB = 11;
const int LDB = 12;
const int ADD = 13;
const int ADI = 14;
const int SUB = 15;
const int MUL = 16;
const int DIV = 17;
const int CMP = 20;
const int TRP = 21;
const int STR1 = 22;
const int LDR1 = 23;
const int STB1 = 24;
const int LDB1 = 25;
const int LABEL = 30; // LABEL CODE
const int APO = 39;//apostraphe char
const int SL = 9;
const int SP = 10;
const int FP = 11;
const int SB = 12;
const int PC = 13;
const int ASCII_OFFSET = 48;
const int STACK_SIZE = 1200;
vector<string> tokens;
int reg[14];
const int INT_SIZE = 4;
const int BYT_SIZE = 1;
const int INSTRUCT_SIZE = 12;
static int p_start = -1;
static int p_end = -1;
static int sl = 0;
static int sp = 0;
static int fp = 0;
static int sb = 0;
static int pfp = 0;
map<string,int> symboltable;
static int pc = 0;
char* machinecode;

//increments the PC for a program size
static void increment(){
    pc += INT_SIZE;
    reg[PC] = pc;
}

struct assembler {
    //REGANDDIRECTIe
    static int regAndDirData(int i, int op){//takes an opp code and stores op code, reg, and data dir into machinecode
        int address = 0;
        int reg = 0;
        int* ii;
        //register
        //get second char of R
        reg = getReg(i, op);
        i++;
        //followed by directive
        address = symboltable.find(tokens[i])->second;
        //place operator, register, and label address in machine code
        ii = (int*)(machinecode + pc);
        *ii = op;
        increment();//size of instruction operator
        ii = (int*)(machinecode + pc);
        *ii = reg;
        increment();//size of instruction operand
        ii = (int*)(machinecode + pc);
        *ii = address;
        increment();//size of instruction operand
        //operator
        return i;
    }
    static int getReg(int i, int op){///get register in R# format or FP, SB, SL, SP
        //if
        int r = 0;
        if(tokens[i].at(0) == 'R'){//R#{
            return r = (int)tokens[i].at(1)-ASCII_OFFSET;
        }
        else if (tokens[i].find("SL") != string::npos){
            return r = SL;
        }
        else if (tokens[i].find("SP") != string::npos){
            return r = SP;
        }
        else if (tokens[i].find("FP") != string::npos){
            return r = FP;
        }
        else if (tokens[i].find("SB") != string::npos){
            return r = SB;
        }
        else
            return r = PC;
    }
    static int regAndReg(int i, int op){
        int r = 0;
        int* ii;
        //store op
        ii = (int*)(machinecode + pc);
        *ii = op;
        increment();
        //get dst reg
        r = getReg(i, op);
        ii = (int*)(machinecode + pc);
        *ii = r;
        increment();
        //get src reg
        i++;
        r = getReg(i,op);
        ii = (int*)(machinecode + pc);
        *ii = r;
        increment();
        return i;
    }
    
    
    //REGANDREG
    //PASS ONE FUNCTION
    static void passOne (string input){
        stringstream check(input);
        stringstream iss;
        string line;
        string temp;
        string temp2;
        char c;
        
        while(getline(check,line)){
            iss << line;
            while(getline(iss,temp, ' ')){
                    if (temp == "")
                        continue;
                    c = temp.at(0);
                    if (c != '#' && c != ';')
                        tokens.push_back(temp);
                    else
                        break;//discard whole line
            }
            iss.str(std::string());
            iss.clear();
        }
        int i = 0;
        while(i<tokens.size()){
            //parse each one
            //find out if its a directive or a operator
            if(find(OPS.begin(), OPS.end(), tokens[i]) != OPS.end()){
                //is operator
                //get label,increment pc 12
                if (p_start == -1){
                    p_start = pc;
                }
                pc += INSTRUCT_SIZE;
                if(tokens[i] == "TRP" || tokens[i] == "JMP" || tokens[i] == "JMR")//check to see if it is TRP
                    i+=2;
                else
                    i+=3;
            }
            else {//must be a label
                symboltable.insert(std::pair<string,int>(tokens[i],pc));
                i++;
                //int or byte to increment pc
                if(!(tokens[i].compare(DIR[0]))){
                    //int
                    i++;
                    while(tokens[i].back() == ','){//says there are more values to be stored.
                        i++;
                        increment();
                    }
                    
                    i++;//skip to beginning of next line
                    //increase pc by 4
                    increment();
                }
                else if(!(tokens[i].compare(DIR[1]))){ //byte
                    i+=2;//skip the value and go to the next line
                    pc += BYT_SIZE;
                    while(!(tokens[i].compare(DIR[1]))){
                        i+=2;
                        pc+= BYT_SIZE;
                    }
                    
                }
                else{
                }
            }
        }
    }
    //PASS TWO FUNCTION
    static void passTwo(string input){
        stringstream check(input);
        stringstream iss;
        string line;
        string temp;
        char c;
        
        while(getline(check,line)){
            iss << line;
            while(getline(iss,temp, ' ')){
                if (temp == "")
                    continue;
                c = temp.at(0);
                if (c != '#' && c != ';')
                    tokens.push_back(temp);
                else
                    break;//discard whole line
            }
            iss.str(std::string());
            iss.clear();
        }
        int i = 0;
        machinecode = new char[pc];
        int op = 0;
        int address = 0;
        int reg = 0;
        int val = 0;
        char byt;
        char* bb;
        int* ii;
        pc = 0;
        while (i<tokens.size()){//go until all of tokens has been read
            if (find(OPS.begin(), OPS.end(), tokens[i]) != OPS.end()){//is operator?
                //get operator
                
                for(int j = 0; j < OPS.size(); j++){
                    if (!tokens[i].compare(OPS[j])){
                        op = OPS_VALUE[j];//store value as instruction value
                        break;
                    }
                }
                i++;
                if (op == TRP){//trp instruction
                    //get operand
                    reg = (int)tokens[i].at(0)-ASCII_OFFSET;//cast from char to int
                    //store op value, code value, and code value again to take up 12 bytes
                    ii = (int*)(machinecode + pc);
                    *ii = op;
                    increment();//size of operator
                    ii = (int*)(machinecode + pc);
                    *ii = reg;
                    int temp;
                    temp = *ii;
                    increment();//size of operand
                    increment();//size of other operand
                    //look up values
                }
                else if (op == JMP){
                    //get label address
                    address = symboltable.find(tokens[i])->second;
                    //store op code, address, and then increment for padding
                    ii = (int*)(machinecode + pc);
                    *ii = op;
                    increment();//size of operator
                    ii = (int*)(machinecode + pc);
                    *ii = address;
                    increment();
                    increment();
                }
                else if (op == JMR){
                    //get reg argument
                    reg = getReg(i, op);
                    //store op code, reg, and padding
                    ii = (int*)(machinecode + pc);
                    *ii = op;
                    increment();//size of operator
                    ii = (int*)(machinecode + pc);
                    *ii = reg;
                    increment();
                    increment();
                }
                else if (op == LDA || op == BNZ || op == BLT || op == BRZ || op == BGT){//takes a register and a directive
                    i = regAndDirData(i, op);
                }
                else if (op == LDR || op == LDB){//could be indirect or directive
                    int temp = i;
                    temp++;
                    //move directly to second parameter
                    std::regex re("[R][0-9]|SP|SL|FP|SB");
                    std::smatch match;
                    if (std::regex_search(tokens[temp], match, re)){//contains register?
                        //REGISTER INDIRECT
                        //Get new op code
                        if (op == LDR)
                            op = LDR1;
                        if (op == LDB)
                            op = LDB1;
                        regAndReg(i, op);
                    }
                    else
                        i = regAndDirData(i, op);
                }
                else if (op == STR || op == STB){
                    int temp = i;
                    temp++;
                    //move directly second parameter
                    std::regex re("[R][0-9]|SP|SL|FP|SB");
                    std::smatch match;
                    if (std::regex_search(tokens[temp], match, re)){//contains register?
                        //REGISTER INDIRECT store
                        //Get new op code
                        if (op == STR)
                            op = STR1;
                        if (op == STB)
                            op = STB1;
                        regAndReg(i, op);
                    }
                    else
                        i = regAndDirData(i, op);
                }
                else if (op == ADI){
                    //get register
                    reg = getReg(i, op);
                    i++;
                    //get imediate value
                    val = stoi(tokens[i]);
                    //store op code, reg, and immediate
                    ii = (int*)(machinecode + pc);
                    *ii = op;
                    increment();
                    ii = (int*)(machinecode + pc);
                    *ii = reg;
                    increment();
                    ii = (int*)(machinecode + pc);
                    *ii = val;
                    increment();
                }
                else {//takes two registers
                    i = regAndReg(i, op);
                }
                i++;
            }
            else {//is directive?
                i++;
                if(!(tokens[i].compare(DIR[0]))){//is int?
                    i++;
                    //store value of int in memory
                    if (tokens[i].back() == ',')//says there are more values to be stored.
                        while(tokens[i].back() == ','){
                            val = stoi(tokens[i]);
                            ii = (int*)(machinecode + pc);
                            *ii = val;
                            i++;
                            increment();
                        }
                    val = stoi(tokens[i]);
                    ii = (int*)(machinecode + pc);
                    *ii = val;
                    //increase pc by int size
                    i++;
                    increment();
                    
                }
                else if (!(tokens[i].compare(DIR[1]))){ //is byte
                    while(!(tokens[i].compare(DIR[1]))){
                        i++;
                        //store value of .byt char in memory
                        if(tokens[i].at(0) == APO){//if not a ' to start char, must be ascii code version
                            byt = tokens[i].at(1);
                            bb = (machinecode + pc);
                            *bb = byt;
                            //increase pc by byt size
                            pc += BYT_SIZE;
                        }
                        else {
                            val = stoi(tokens[i]);
                            byt = val;
                            bb = (machinecode + pc);
                            *bb = byt;
                            //increase pc by byt size
                            pc += BYT_SIZE;
                        }
                        i++;
                    }
                }
                else{
                    //is label, do nothing
                }
                
            }
        }
    }
};

#endif /* assembler_h */

