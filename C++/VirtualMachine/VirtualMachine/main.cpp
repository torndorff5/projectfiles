//
//  main.cpp
//  VirtualMachine
//
//  Created by codeslinger on 4/23/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include <iostream>
#include "vm.h"



int main(int argc, const char * argv[]) {
    if (argc < 2){//open and read file
        cout << "No file argument passed" << endl;
    }
    else{
        string filename = argv[1];
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
        vm::execute(machinecode, p_start);
    }
}
