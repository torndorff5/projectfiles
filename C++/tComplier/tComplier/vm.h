//
//  vm.h
//  tComplier
//
//  Created by codeslinger on 1/9/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//


#ifndef vm_h
#define vm_h

#include "assembler.h"

struct vm {
    static void vincrement(){
        increment();
        sl = reg[SL];
        sp = reg[SP];
        fp = reg[FP];
        sb = reg[SB];
    }
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
    static void storeChar(int address, char byt){
        char* cc;
        cc = (char*)(machinecode + address);
        *cc = byt;
    }
    //execute function
    static void execute(char* machinecode, int start){//takes pointer to front of dynamic char array
        pc = start;
        reg[PC] = pc;
        sl = p_end;
        sb = sl + STACK_SIZE;
        fp = sb;
        sp = sb;//initialize runtime stack of size stack size
        reg[SL] = sl;
        reg[SP] = sp;
        reg[FP] = fp;
        reg[SB] = sb;
        int data = 0;
        int ri = 0;
        char byt;
        while (pc < p_end){
            //fetch
            data = fetch(pc);
            //decode
            switch (data){
                case TRP://TRP
                    vincrement();
                    //get trap code
                    data = fetch(pc);
                    switch (data){
                        case 4:
                            char input;
                            cin.get(input);
                            reg[3] = (int)input;
                            vincrement();
                            vincrement();
                            break;
                        case 3://TRP 3
                            //print byte from contents of r3
                            byt = reg[3];
                            cout << byt;
                            vincrement();
                            vincrement();
                            break;
                        case 2:
                            int inp;
                            cin >> inp;
                            reg[3] = inp;
                            vincrement();
                            vincrement();
                            break;
                        case 1://TRP 1
                            cout << reg[3];
                            vincrement();
                            vincrement();
                            break;
                        case 0:
                            for(;;){};
                    }
                    break;
                case LDA:
                    vincrement();
                    //get reg number
                    ri = fetch(pc);
                    vincrement();
                    //get address
                    data = fetch(pc);//address of directive
                    vincrement();
                    reg[ri] = data;
                    
                    break;
                case LDB:
                    vincrement();//instruction over
                    ri = fetch(pc);//data is wanted register
                    vincrement();
                    data = fetch(pc);//get label address
                    vincrement();
                    byt = fetchChar(data);
                    reg[ri] = (int)byt;
                    break;
                case LDB1:
                    vincrement();
                    ri = fetch(pc);//get dst reg
                    vincrement();
                    data = fetch(pc);//get src reg
                    vincrement();
                    data = reg[data];//get address in src reg
                    byt = fetchChar(data);//get byte at address in src reg
                    reg[ri] = (int)byt;
                    break;
                case LDR://
                    vincrement();//instruction over
                    ri = fetch(pc);//fetch desired register
                    vincrement();
                    data = fetch(pc);//get address of int
                    vincrement();
                    data = fetch(data);//get content at address
                    reg[ri] = data;//put content in register
                    break;
                case LDR1:
                    vincrement();
                    ri = fetch(pc);
                    vincrement();
                    data = fetch(pc);
                    vincrement();
                    data = reg[data];
                    data = fetch(data);
                    reg[ri] = data;
                    break;
                case ADD:
                    vincrement();
                    ri = fetch(pc);//get dst reg
                    vincrement();
                    data = fetch(pc);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] + reg[data];//execute addition and store in dst
                    break;
                case ADI:
                    vincrement();
                    ri = fetch(pc);//get dst reg
                    vincrement();
                    data = fetch(pc);//get literal
                    vincrement();
                    reg[ri] = reg[ri] + data;
                    break;
                case MOV:
                    vincrement();
                    ri = fetch(pc);//get dst reg
                    vincrement();
                    data = fetch(pc);//get src reg
                    vincrement();
                    reg[ri] = reg[data];
                    break;
                case STB:
                    vincrement();
                    ri = fetch(pc);//get src reg
                    vincrement();
                    data = fetch(pc);//get address of label
                    vincrement();
                    storeChar(data, reg[ri]);
                    break;
                case STB1:
                    vincrement();
                    ri = fetch(pc);//get src reg
                    vincrement();
                    data = fetch(pc);//get dst reg
                    vincrement();
                    data = reg[data];//get address in dst reg
                    storeChar(data, reg[ri]);//store byte at address
                    break;
                case STR:
                    vincrement();
                    ri = fetch(pc);//get src reg
                    vincrement();
                    data = fetch(pc);//get address of label
                    vincrement();
                    store(data, reg[ri]);
                    break;
                case STR1:
                    vincrement();
                    ri = fetch(pc);//get src reg
                    vincrement();
                    data = fetch(pc);//get dst reg
                    vincrement();
                    data = reg[data];//get address in dst reg
                    store(data, reg[ri]);//store 4 bytes at address
                    
                    break;
                case MUL:
                    vincrement();
                    ri = fetch(pc);//get dst reg
                    vincrement();
                    data = fetch(pc);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] * reg[data];//execute multiplication and store in dst
                    break;
                case DIV:
                    vincrement();
                    ri = fetch(pc);//get dst reg
                    vincrement();
                    data = fetch(pc);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] / reg[data];//execute division and store in dst
                    break;
                case SUB:
                    vincrement();
                    ri = fetch(pc);//get dst reg
                    vincrement();
                    data = fetch(pc);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] - reg[data];//execute subtraction and store in dst
                    break;
                case JMP:
                    vincrement();
                    //get address
                    data = fetch(pc);
                    pc = data;
                    break;
                case JMR:
                    vincrement();
                    ri = fetch(pc);
                    pc = reg[ri];
                    break;
                case CMP:
                    vincrement();
                    //fetch two values
                    data = fetch(pc);
                    vincrement();
                    ri = fetch(pc);
                    vincrement();
                    if(reg[data] == reg[ri])
                        reg[data] = 0;
                    else if(reg[data] < reg[ri])
                        reg[data] = -1;
                    else
                        reg[data] = 1;
                    break;
                case BLT:
                    vincrement();
                    //get register
                    ri = fetch(pc);
                    vincrement();
                    //get address
                    data = fetch(pc);
                    //if register value is less than 0, branch to address
                    if (reg[ri] < 0)
                        pc = data;
                    else
                        vincrement();
                    break;
                case BRZ:
                    vincrement();
                    //get register
                    ri = fetch(pc);
                    vincrement();
                    //get address
                    data = fetch(pc);
                    //if register value is 0, branch to address
                    if (reg[ri] == 0)
                        pc = data;
                    else
                        vincrement();
                    break;
                case BNZ:
                    vincrement();
                    //get register
                    ri = fetch(pc);
                    vincrement();
                    //get address
                    data = fetch(pc);
                    //if register value is not 0, branch to address
                    if (reg[ri] != 0)
                        pc = data;
                    else
                        vincrement();
                    break;
                case BGT:
                    vincrement();
                    //get register
                    ri = fetch(pc);
                    vincrement();
                    //get address
                    data = fetch(pc);
                    //if register value is greater than 0, branch to address
                    if (reg[ri] > 0)
                        pc = data;
                    else
                        vincrement();
                    break;
                case AND:
                    vincrement();
                        //fetch two values
                    data = fetch(pc);
                    vincrement();
                    ri = fetch(pc);
                    vincrement();
                    if(reg[ri] == 1 && reg[data] == 1){
                        reg[data] = 1;
                    }
                    else
                        reg[data] = 0;
                    break;
                case OR:
                    vincrement();
                        //fetch two values
                    data = fetch(pc);
                    vincrement();
                    ri = fetch(pc);
                    vincrement();
                    if(reg[ri] == 1 || reg[data] == 1){
                        reg[data] = 1;
                    }
                    else
                        reg[data] = 0;
                    break;
            }
            //execute
        }
        cout << "END" << endl;
    }
    
};

#endif /* vm_h */

