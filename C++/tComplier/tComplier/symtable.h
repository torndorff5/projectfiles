//
//  symtable.h
//  tComplier
//
//  Created by codeslinger on 1/16/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#ifndef symtable_h
#define symtable_h
#include <map>
#include <iterator>
#include <string>

using namespace std;

class symboltable {
    //know
    //sym struct to place in map
    struct sym{
        string scope;
        string symid;
        string kind;
        string data;
    };
    //symbol counter
    int count;
    //key - > values table
    map<string, sym> symtab;
    //do
    //construct itself
    symboltable(){
        count = 1;
    };
    //generate symid
        //takes a char and adds the symbol counter to it to create a unique symbol id
    string genSymID(char c){
        string s = "";
        s+=c;
        s+=(to_string(count));
        return s;
    }
    //add symbol to table
    //
    
};

#endif /* symtable_h */
