//
//  main.cpp
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include "vm.h"
#include "tCompiler.cpp"

const string ICODE_FILENAME = "icode.txt";

int main(int argc, const char * argv[]) {
    if (argc < 2){//open and read file
        cout << "No file argument passed" << endl;
    }
    else{
        string filename = "test.kxi";
        //Call Lexical analysis on file read in.
        compiler c;
        c.passOne(filename);
        //call pass two for semantic 
        c.passTwo(filename);
        //call pass three for iCode to tCode
        c.passThree(ICODE_FILENAME);
        //pass one
        /*fstream in;
        in.open(filename);
        string buf;
        while(!in.eof()){
            buf += in.get();
        }*/
        //assembler::passOne(buf);
        //pass two
        //tokens.clear();//clear token vector
        //assembler::passTwo(buf);
        //execute
        //p_end = pc;
        //vm::execute(machinecode, p_start);
        }
    return 0;
}



