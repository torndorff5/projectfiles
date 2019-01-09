//
//  main.cpp
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include "vm.h"

int main(int argc, const char * argv[]) {
    if (argc < 2){//open and read file
        cout << "No file argument passed" << endl;
    }
    else{
        string filename = "/Users/codeslinger/Desktop/C++/tComplier/tComplier/fib.txt";
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
            assembler::passOne(input);
            //pass two
            tokens.clear();//clear token vector
            assembler::passTwo(input);
            //execute
            p_end = pc;
            vm::execute(machinecode, p_start);
        }
        else{
            cout << "Error opening file." << endl;
        }
    }
    return 0;
}



