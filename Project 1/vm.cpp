//
//  main.cpp
//  proj1
//
//  Created by codeslinger on 10/4/18.
//  Copyright © 2018 codeslinger. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <map>

using namespace std;

//GLOBAL VARIABLES AND CONSTANTS
const vector<string> OPS = {"ADD","SUB","MUL","DIV","TRP","MOV","LDR","LDB","STR"};
const vector<int> OPS_VALUE = {13,15,16,17,21,7,10,12,9};//corresponds with OPS
const vector<string> DIR = {".INT",".BYT"};
const int LDB = 12;
const int STR = 9;
const int LDR = 10;
const int MOV = 7;
const int TRP = 21;
const int DIV = 17;
const int MUL = 16;
const int SUB = 15;
const int ADD = 13;
const int APO = 39;//apostraphe char
const int ASCII_OFFSET = 48;
vector<string> tokens;
int reg[9];
const int INT_SIZE = 4;
const int BYT_SIZE = 1;
const int OP_SIZE = 12;
static int p_start = -1;
static int p_end = -1;
map<string,int> symboltable;
static int pc = 0;
char* machinecode;



//PASS ONE FUNCTION
void passOne (string input){
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
    while(i<tokens.size()){
        //parse each one
        //find out if its a directive or a operator
        if(find(OPS.begin(), OPS.end(), tokens[i]) != OPS.end()){
            //is operator
            //get label,increment pc 12
            if (p_start == -1){
                p_start = pc;
            }
            pc += OP_SIZE;
            if(tokens[i] == OPS[4])//check to see if it is TRP
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
                i+=2;//dont care about the value right now
                //increase pc by 4
                pc += INT_SIZE;
            }
            else if (!(tokens[i].compare(DIR[1]))){ //byte
                i+=2;//skip the value and go to the next line
                pc += BYT_SIZE;
            }
        }
    }
}
//PASS TWO FUNCTION
void passTwo(string input){
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
            if (op == LDB || op == LDR || op == STR){//if operator is ldb or ldr or str
                //register
                //get second char of R
                reg = (int)tokens[i].at(1) - ASCII_OFFSET;
                i++;
                //followed by directive
                address = symboltable.find(tokens[i])->second;
                //place operator, register, and label address in machine code
                ii = (int*)(machinecode + pc);
                *ii = op;
                pc+=INT_SIZE;//size of instruction operator
                ii = (int*)(machinecode + pc);
                *ii = reg;
                pc+=INT_SIZE;//size of instruction operand
                ii = (int*)(machinecode + pc);
                *ii = address;
                pc+=INT_SIZE;//size of instruction operand
                //operator
            }
            else if (op == TRP){//trp instruction
                //get operand
                reg = (int)tokens[i].at(0)-ASCII_OFFSET;//cast from char to int
                //store op value, code value, and code value again to take up 12 bytes
                ii = (int*)(machinecode + pc);
                *ii = op;
                pc += INT_SIZE;//size of operator
                ii = (int*)(machinecode + pc);
                *ii = reg;
                int temp;
                temp = *ii;
                pc += INT_SIZE;//size of operand
                pc += INT_SIZE;//size of other operand
                //look up values
            }
            else {
                //store op
                ii = (int*)(machinecode + pc);
                *ii = op;
                pc += INT_SIZE;
                //get dst reg
                reg = (int)tokens[i].at(1)-ASCII_OFFSET;
                ii = (int*)(machinecode + pc);
                *ii = reg;
                pc += INT_SIZE;
                //get src reg
                i++;
                reg = (int)tokens[i].at(1)-ASCII_OFFSET;
                ii = (int*)(machinecode + pc);
                *ii = reg;
                pc += INT_SIZE;
            }
            i++;
        }
        else {//is directive?
            i++;
            if(!(tokens[i].compare(DIR[0]))){//is int?
                i++;
                //store value of int in memory
                val = stoi(tokens[i]);
                ii = (int*)(machinecode + pc);
                *ii = val;
                //increase pc by int size
                pc += INT_SIZE;
                i++;
            }
            else if (!(tokens[i].compare(DIR[1]))){ //is byte
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
    }
    
}


struct vm {
    static int fetch(int curr){
        int* ii;
        int val;
        ii = (int*)(machinecode + curr);
        val = *ii;
        return val;
    }
    static char fetchChar (int address){
        char* cc;
        char val;
        cc = (machinecode + address);
        val = *cc;
        return val;
    }
    static void store(int address, int data){
        int* ii;
        ii = (int*)(machinecode + address);
        *ii = data;
    }
    //execute function
    static void execute(char* machinecode, int start){//takes pointer to front of dynamic char array
        pc = start;
        int data = 0;
        int ri = 0;
        char byt;
        while (pc < p_end){
            //fetch
            data = fetch(pc);
            //decode
            switch (data){
                case LDB:
                    pc += INT_SIZE;//instruction over
                    ri = fetch(pc);//data is wanted register
                    pc += INT_SIZE;
                    data = fetch(pc);//get label address
                    byt = fetchChar(data);
                    reg[ri] = (int)byt;
                    pc += INT_SIZE;
                    break;
                case TRP://TRP
                    pc += INT_SIZE;
                    //get trap code
                    data = fetch(pc);
                    switch (data){
                        case 3://TRP 3
                            //print byte from contents of r3
                            byt = reg[data];
                            cout << byt;
                            pc += INT_SIZE;
                            pc += INT_SIZE;
                            break;
                        case 1://TRP 1
                            cout << reg[data];
                            pc += INT_SIZE;
                            pc += INT_SIZE;
                    }
                    break;
                case LDR://
                    pc += INT_SIZE;//instruction over
                    ri = fetch(pc);//fetch desired register
                    pc += INT_SIZE;
                    data = fetch(pc);//get address of int
                    data = fetch(data);//get content at address
                    reg[ri] = data;//put content in register
                    pc += INT_SIZE;
                    break;
                case ADD:
                    pc += INT_SIZE;
                    ri = fetch(pc);//get dst reg
                    pc += INT_SIZE;
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] + reg[data];//execute addition and store in dst
                    pc += INT_SIZE;
                    break;
                case MOV:
                    pc += INT_SIZE;
                    ri = fetch(pc);//get dst reg
                    pc += INT_SIZE;
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[data];
                    pc += INT_SIZE;
                    break;
                case STR:
                    pc += INT_SIZE;
                    ri = fetch(pc);//get src reg
                    pc += INT_SIZE;
                    data = fetch(pc);//get address
                    store(data, reg[ri]);
                    pc += INT_SIZE;
                    break;
                case MUL:
                    pc += INT_SIZE;
                    ri = fetch(pc);//get dst reg
                    pc += INT_SIZE;
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] * reg[data];//execute multiplication and store in dst
                    pc += INT_SIZE;
                    break;
                case DIV:
                    pc += INT_SIZE;
                    ri = fetch(pc);//get dst reg
                    pc += INT_SIZE;
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] / reg[data];//execute division and store in dst
                    pc += INT_SIZE;
                    break;
                case SUB:
                    pc += INT_SIZE;
                    ri = fetch(pc);//get dst reg
                    pc += INT_SIZE;
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] - reg[data];//execute subtraction and store in dst
                    pc += INT_SIZE;
            }
            
            //execute
            }
    }
};

int main(int argc, const char * argv[]) {
    if (argc < 2){//open and read file
        cout << "No file argument passed" << endl;
    }
    else{
        string filename = argv[1];
        fstream in;
        in.open(filename, ios::in);
        string input;
        char c;
        if (in.is_open()){
            while(!in.eof()){
                in.get(c);
                input += c;
            }
            //pass one
            passOne(input);
            //pass two
            tokens.clear();//clear token vector
            passTwo(input);
            //execute
            p_end = pc;
            vm v;
            v.execute(machinecode, p_start);
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
    return 0;
}


