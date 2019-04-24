//
//  VirtualMachine.h
//  tComplier
//
//  Created by codeslinger on 4/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#ifndef VirtualMachine_h
#define VirtualMachine_h


#include "vm.h"

class VirtualMachine {
    string buf;
    fstream in;
public:
    VirtualMachine(string filename){
        buf = "";
        in.open(filename);
        while(!in.eof()){
            buf += in.get();
        }
    }
    
    void run(){
        assembler::passOne(buf);
        assembler::passTwo(buf);
        p_end = pc;
        vm::execute(machinecode, p_start);
    }
};

#endif /* VirtualMachine_h */
