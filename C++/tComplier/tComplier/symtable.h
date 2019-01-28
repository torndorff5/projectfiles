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
public:
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
    void addSymbol(const sym s){
        symtab.insert(std::pair<string,sym>(s.symid,s));
    }
    //fecth symbol
    sym fetchSymbol(string s){
        try{
            sym r = symtab.at(s);
            return r;
        }
        catch (std::out_of_range e){
            throw e;
        }
    }
};

#endif /* symtable_h */
