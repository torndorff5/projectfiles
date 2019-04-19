//
//  main.cpp
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include "tCompiler.cpp"
#include "vm.h"

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
        /*filename = c.passThree(ICODE_FILENAME);
        string buf = "";
        fstream in;
        in.open(filename);
        while(!in.eof()){
            buf += in.get();
        }
        in.close();
        assembler::passOne(buf);
        tokens.clear();
        assembler::passTwo(buf);
        p_end = pc;
        vm::execute(machinecode, p_start);*/
    }
    return 0;
}



