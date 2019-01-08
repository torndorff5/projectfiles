//
//  vm.h
//  proj4
//
//  Created by codeslinger on 12/4/18.
//  Copyright © 2018 codeslinger. All rights reserved.
//

#ifndef vm_h
#define vm_h

#include "assembler.h"

struct vm {
    static void increment(){
        reg[PC] += INT_SIZE;
    }
    static void vincrement(){
        updateReg();
        increment();
    }
    static void updateReg(){
        pc = reg[PC];
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
    static void loadThread(int thread_id){
        //fetch and update pc, sl, sp, fp, sb, and all registers off of current thread stack
        int ts_address = 0;
        if(thread_id == MAIN)
            ts_address = p_end + STACK_SIZE;
        else if(thread_id == t1)
            ts_address = t1;
        else if (thread_id == t2)
            ts_address = t2;
        int j = 0;
        for(int i =0; i<=THREAD_STATE_SIZE;i+=INT_SIZE){
            reg[j] = fetch(ts_address-i);
            j++;
        }
        
    }
    static void saveThread(){
        //save current pc, sl, sp, fp, sb, and all registers to thread stack of thread_id
        int j = 0;
        for(int i =0; i<=THREAD_STATE_SIZE;i+=INT_SIZE){
            store(reg[SB]-i,reg[j]);
            j++;
        }
        
        
    }
    //execute function
    static void execute(char* machinecode, int start){//takes pointer to front of dynamic char array
        int data = 0;
        int ri = 0;
        char byt;
        //fire up main thread
        //initialize runtime stack of size stack size
        reg[PC] = start;
        reg[SL] = p_end;
        reg[SB] = reg[SL] + STACK_SIZE;
        reg[FP] = reg[SB] - THREAD_STATE_SIZE-INT_SIZE;
        reg[SP] = reg[FP];
        reg[SL] = reg[SB] - TS;
        t1 = reg[SB] - TS;
        t2 = reg[SB] - (TS * 2);
        thre[t1] = false;
        thre[t2] = false;
        threads.push(MAIN);//0 = main id
        saveThread();
        int current_thread;
        while (reg[PC] < p_end){
            current_thread = threads.front();
            loadThread(current_thread);
            //fetch
            data = fetch(reg[PC]);
            //decode
            updateReg();
            switch (data){
                case TRP://TRP
                    vincrement();
                    //get trap code
                    data = fetch(reg[PC]);
                    switch (data){
                        case 5:
                            int inp;
                            cin >> inp;
                            reg[3] = inp;
                            vincrement();
                            vincrement();
                            break;
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
                    ri = fetch(reg[PC]);
                    vincrement();
                    //get address
                    data = fetch(reg[PC]);//address of directive
                    vincrement();
                    reg[ri] = data;
                    
                    break;
                case LDB:
                    vincrement();//instruction over
                    ri = fetch(reg[PC]);//data is wanted register
                    vincrement();
                    data = fetch(reg[PC]);//get label address
                    vincrement();
                    byt = fetchChar(data);
                    reg[ri] = (int)byt;
                    break;
                case LDB1:
                    vincrement();
                    ri = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = fetch(reg[PC]);//get src reg
                    vincrement();
                    data = reg[data];//get address in src reg
                    byt = fetchChar(data);//get byte at address in src reg
                    reg[ri] = (int)byt;
                    break;
                case LDR://
                    vincrement();//instruction over
                    ri = fetch(reg[PC]);//fetch desired register
                    vincrement();
                    data = fetch(reg[PC]);//get address of int
                    vincrement();
                    data = fetch(data);//get content at address
                    reg[ri] = data;//put content in register
                    break;
                case LDR1:
                    vincrement();
                    ri = fetch(reg[PC]);
                    vincrement();
                    data = fetch(reg[PC]);
                    vincrement();
                    data = reg[data];
                    data = fetch(data);
                    reg[ri] = data;
                    break;
                case ADD:
                    vincrement();
                    ri = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = fetch(reg[PC]);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] + reg[data];//execute addition and store in dst
                    break;
                case ADI:
                    vincrement();
                    ri = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = fetch(reg[PC]);//get literal
                    vincrement();
                    reg[ri] = reg[ri] + data;
                    break;
                case MOV:
                    vincrement();
                    ri = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = fetch(reg[PC]);//get src reg
                    vincrement();
                    reg[ri] = reg[data];
                    break;
                case STB:
                    vincrement();
                    ri = fetch(reg[PC]);//get src reg
                    vincrement();
                    data = fetch(reg[PC]);//get address of label
                    vincrement();
                    storeChar(data, reg[ri]);
                    
                    break;
                case STB1:
                    vincrement();
                    ri = fetch(reg[PC]);//get src reg
                    vincrement();
                    data = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = reg[data];//get address in dst reg
                    storeChar(data, reg[ri]);//store byte at address
                    
                    break;
                case STR:
                    vincrement();
                    ri = fetch(reg[PC]);//get src reg
                    vincrement();
                    data = fetch(reg[PC]);//get address of label
                    vincrement();
                    store(data, reg[ri]);
                    break;
                case STR1:
                    vincrement();
                    ri = fetch(reg[PC]);//get src reg
                    vincrement();
                    data = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = reg[data];//get address in dst reg
                    store(data, reg[ri]);//store 4 bytes at address
                    
                    break;
                case MUL:
                    vincrement();
                    ri = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = fetch(reg[PC]);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] * reg[data];//execute multiplication and store in dst
                    break;
                case DIV:
                    vincrement();
                    ri = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = fetch(reg[PC]);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] / reg[data];//execute division and store in dst
                    break;
                case SUB:
                    vincrement();
                    ri = fetch(reg[PC]);//get dst reg
                    vincrement();
                    data = fetch(reg[PC]);//get src reg
                    vincrement();
                    reg[ri] = reg[ri] - reg[data];//execute subtraction and store in dst
                    break;
                case JMP:
                    vincrement();
                    //get address
                    data = fetch(reg[PC]);
                    reg[PC] = data;
                    break;
                case JMR:
                    vincrement();
                    ri = fetch(reg[PC]);
                    reg[PC] = reg[ri];
                    break;
                case CMP:
                    vincrement();
                    //fetch two values
                    data = fetch(reg[PC]);
                    vincrement();
                    ri = fetch(reg[PC]);
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
                    ri = fetch(reg[PC]);
                    vincrement();
                    //get address
                    data = fetch(reg[PC]);
                    //if register value is less than 0, branch to address
                    if (reg[ri] < 0)
                        reg[PC] = data;
                    else
                        vincrement();
                    break;
                case BRZ:
                    vincrement();
                    //get register
                    ri = fetch(reg[PC]);
                    vincrement();
                    //get address
                    data = fetch(reg[PC]);
                    //if register value is 0, branch to address
                    if (reg[ri] == 0)
                        reg[PC] = data;
                    else
                        vincrement();
                    break;
                case BNZ:
                    vincrement();
                    //get register
                    ri = fetch(reg[PC]);
                    vincrement();
                    //get address
                    data = fetch(reg[PC]);
                    //if register value is not 0, branch to address
                    if (reg[ri] != 0)
                        reg[PC] = data;
                    else
                        vincrement();
                    break;
                case BGT:
                    vincrement();
                    //get register
                    ri = fetch(reg[PC]);
                    vincrement();
                    //get address
                    data = fetch(reg[PC]);
                    //if register value is greater than 0, branch to address
                    if (reg[ri] > 0)
                        reg[PC] = data;
                    else
                        vincrement();
                    break;
                case LCK:
                {
                    vincrement();
                    //get label
                    data = fetch(reg[PC]);
                    int state = fetch(data);
                    if(state == -1){//unlocked
                        //lock it
                        store(data,current_thread);
                        vincrement();
                        vincrement();
                    }
                    else
                        reg[PC] -=INT_SIZE;
                    break;
                }
                case ULK:
                    vincrement();
                    data = fetch(reg[PC]);
                    store(data,-1);
                    vincrement();
                    vincrement();
                    break;
                case END:
                    if(current_thread != MAIN){
                        //terminate thread
                        threads.pop();
                        vincrement();
                        thre[reg[SB]] = false;
                    }
                    continue;
                case BLK:
                    if(current_thread == MAIN){
                        bool single = true;
                        for(auto &b: thre)
                            if(b.second)//only move on if there are no other threads besides main
                                single = false;
                        if(single){
                            vincrement();
                            vincrement();
                            vincrement();
                        }
                    }
                    else{
                        vincrement();
                        vincrement();
                        vincrement();
                    }
                    break;
                case RUN:
                    vincrement();
                    //get register
                    ri = fetch(reg[PC]);
                    vincrement();
                    //get address to start thread at
                    data = fetch(reg[PC]);
                    vincrement();
                    //if not one available,
                    bool available = false;
                    int ts_loc = t1;
                    for(auto &b : thre){
                        if(b.second)
                            available = false;
                        else{
                            b.second = true;
                            ts_loc = b.first;
                            available = true;
                            break;
                        }
                        
                    }
                    if(!available)
                        reg[ri] = -1;//exception location.
                    //initialize new thread if available on its stack
                    int temp[14];//get temp array ready.
                    for(int i = 0; i<SL;i++)
                        temp[i]=0;
                    temp[SL] = ts_loc - TS;
                    temp[SP] = ts_loc - THREAD_STATE_SIZE-INT_SIZE;
                    temp[FP] = temp[SP];
                    temp[SB] = ts_loc;
                    temp[PC] = data;
                    int j = 0;
                    for(int i =0; i<=THREAD_STATE_SIZE;i+=INT_SIZE){
                        store(temp[SB]-i,temp[j]);
                        j++;
                    }
                    //push thread onto queue
                    threads.push(ts_loc);
                    reg[ri] = ts_loc;
                    break;
                    
            }
            //save thread state
            updateReg();
            saveThread();
            //pop thread
            threads.pop();
            //push thread
            threads.push(current_thread);
        }
        cout << "END" << endl;
    }
    
};

#endif /* vm_h */


