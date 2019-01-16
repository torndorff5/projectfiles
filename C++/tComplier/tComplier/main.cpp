//
//  main.cpp
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include "vm.h"
#include "tCompiler.cpp"

int main(int argc, const char * argv[]) {
    if (argc < 2){//open and read file
        cout << "No file argument passed" << endl;
    }
    else{
        string filename = argv[1];
        //Call Lexical analysis on file read in.
        compiler c;
        c.passOne(filename);
        //pass one
        //assembler::passOne(input);
        //pass two
        //tokens.clear();//clear token vector
        //assembler::passTwo(input);
        //execute
        //p_end = pc;
        //vm::execute(machinecode, p_start);
        }
    return 0;
}



