//
//  main.cpp
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include "vm.h"
#include "lexical.cpp"

int main(int argc, const char * argv[]) {
    if (argc < 2){//open and read file
        cout << "No file argument passed" << endl;
    }
    else{
        string filename = "/Users/codeslinger/Desktop/C++/tComplier/tComplier/test.kxi";
        //Call Lexical analysis on file read in.
        lexical l;
        l.execute(filename);
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



