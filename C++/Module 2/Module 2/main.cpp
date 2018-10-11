//
//  main.cpp
//  Module 2
//
//  Created by codeslinger on 10/5/18.
//  Copyright © 2018 codeslinger. All rights reserved.
//

#include <iostream>
using namespace std;
void readStuff(unsigned long long x);

int main( ) {
    
    unsigned long long x;
    while (cin >> hex >> x) {
        cout << endl << "Instruction: " << hex << x << endl;
        cout << dec;      // Convert back to decimal
       readStuff(x);
        cout << endl;
    }
}

void readStuff(unsigned long long x){
    union Data {
        struct {
            unsigned li: 32;
            unsigned rreg: 6;
            unsigned lreg: 6;
            unsigned si: 7;
            unsigned radrm: 4;
            unsigned ladrm: 4;
            unsigned code: 5;
        };
        unsigned char* p;
    };
    Data data;
    data.p = reinterpret_cast<unsigned char*>(x);//put bits into a
    //read bits and store values into struct
    cout << endl << endl;
    cout << "code: " << data.code << endl;
    cout << "ladrm: " << data.ladrm << endl;
    cout << "radrm: " << data.radrm << endl;
    cout << "si: " << data.si  << endl;
    cout << "lreg: " << data.lreg << endl;
    cout << "rreg: " << data.rreg << endl;
    cout << "li: " << data.li << endl;
    
    
    
}
