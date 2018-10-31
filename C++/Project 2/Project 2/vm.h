//
//  vm.h
//  Project 2
//
//  Created by codeslinger on 10/26/18.
//  Copyright © 2018 codeslinger. All rights reserved.
//

#ifndef vm_h
#define vm_h

#include "assembler.h"

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
    static void storeChar(int address, char byt){
        char* cc;
        cc = (char*)(machinecode + address);
        *cc = byt;
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
                case TRP://TRP
                    increment();
                    //get trap code
                    data = fetch(pc);
                    switch (data){
                        case 3://TRP 3
                            //print byte from contents of r3
                            byt = reg[3];
                            cout << byt;
                            increment();
                            increment();
                            break;
                        case 1://TRP 1
                            cout << reg[3];
                            increment();
                            increment();
                            break;
                        case 0:
                            for(;;){};
                    }
                    break;
                case LDA:
                    increment();
                    //get reg number
                    ri = fetch(pc);
                    increment();
                    //get address
                    data = fetch(pc);//address of directive
                    reg[ri] = data;
                    increment();
                    break;
                case LDB:
                    increment();//instruction over
                    ri = fetch(pc);//data is wanted register
                    increment();
                    data = fetch(pc);//get label address
                    byt = fetchChar(data);
                    reg[ri] = (int)byt;
                    increment();
                    break;
                case LDB1:
                    increment();
                    ri = fetch(pc);//get dst reg
                    increment();
                    data = fetch(pc);//get src reg
                    data = reg[data];//get address in src reg
                    byt = fetchChar(data);//get byte at address in src reg
                    reg[ri] = (int)byt;
                    increment();
                    break;
                case LDR://
                    increment();//instruction over
                    ri = fetch(pc);//fetch desired register
                    increment();
                    data = fetch(pc);//get address of int
                    data = fetch(data);//get content at address
                    reg[ri] = data;//put content in register
                    increment();
                    break;
                case LDR1:
                    increment();
                    ri = fetch(pc);
                    increment();
                    data = fetch(pc);
                    data = reg[data];
                    data = fetch(data);
                    reg[ri] = data;
                    increment();
                    break;
                case ADD:
                    increment();
                    ri = fetch(pc);//get dst reg
                    increment();
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] + reg[data];//execute addition and store in dst
                    increment();
                    break;
                case ADI:
                    increment();
                    ri = fetch(pc);//get dst reg
                    increment();
                    data = fetch(pc);//get literal
                    reg[ri] = reg[ri] + data;
                    increment();
                    break;
                case MOV:
                    increment();
                    ri = fetch(pc);//get dst reg
                    increment();
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[data];
                    increment();
                    break;
                case STB:
                    increment();
                    ri = fetch(pc);//get src reg
                    increment();
                    data = fetch(pc);//get address of label
                    storeChar(data, reg[ri]);
                    increment();
                    break;
                case STB1:
                    increment();
                    ri = fetch(pc);//get src reg
                    increment();
                    data = fetch(pc);//get dst reg
                    data = reg[data];//get address in dst reg
                    storeChar(data, reg[ri]);//store byte at address
                    increment();
                    break;
                case STR:
                    increment();
                    ri = fetch(pc);//get src reg
                    increment();
                    data = fetch(pc);//get address of label
                    store(data, reg[ri]);
                    increment();
                    break;
                case MUL:
                    increment();
                    ri = fetch(pc);//get dst reg
                    increment();
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] * reg[data];//execute multiplication and store in dst
                    increment();
                    break;
                case DIV:
                    increment();
                    ri = fetch(pc);//get dst reg
                    increment();
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] / reg[data];//execute division and store in dst
                    increment();
                    break;
                case SUB:
                    increment();
                    ri = fetch(pc);//get dst reg
                    increment();
                    data = fetch(pc);//get src reg
                    reg[ri] = reg[ri] - reg[data];//execute subtraction and store in dst
                    increment();
                    break;
                case JMP:
                    increment();
                    //get address
                    data = fetch(pc);
                    pc = data;
                    break;
                case JMR:
                    increment();
                    ri = fetch(pc);
                    pc = reg[ri];
                    break;
                case CMP:
                    increment();
                    //fetch two values
                    data = fetch(pc);
                    increment();
                    ri = fetch(pc);
                    if(reg[data] == reg[ri])
                        reg[data] = 0;
                    else if(reg[data] < reg[ri])
                        reg[data] = -1;
                    else
                        reg[data] = 1;
                    increment();
                    break;
                case BLT:
                    increment();
                    //get register
                    ri = fetch(pc);
                    increment();
                    //get address
                    data = fetch(pc);
                    //if register value is less than 0, branch to address
                    if (reg[ri] < 0)
                        pc = data;
                    else
                        increment();
                    break;
                case BRZ:
                    increment();
                    //get register
                    ri = fetch(pc);
                    increment();
                    //get address
                    data = fetch(pc);
                    //if register value is 0, branch to address
                    if (reg[ri] == 0)
                        pc = data;
                    else
                        increment();
                    break;
                case BNZ:
                    increment();
                    //get register
                    ri = fetch(pc);
                    increment();
                    //get address
                    data = fetch(pc);
                    //if register value is not 0, branch to address
                    if (reg[ri] != 0)
                        pc = data;
                    else
                        increment();
                    break;
                case BGT:
                    increment();
                    //get register
                    ri = fetch(pc);
                    increment();
                    //get address
                    data = fetch(pc);
                    //if register value is greater than 0, branch to address
                    if (reg[ri] > 0)
                        pc = data;
                    else
                        increment();
                    break;
            }
            
            //execute
        }
    }
};

#endif /* vm_h */
