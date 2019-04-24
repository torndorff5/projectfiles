//
//  main.cpp
//  Program_6
//
//  Created by codeslinger on 3/25/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include <iostream>
#include <map>
#include <fstream>
#include "Parser.h"

using namespace std;




class Database {
    map<string, string> data;
    string id;
public:
    Database(){
        id = "";
    }
    Database(const string& id){
        this->id = id;
    }
    string getID() const{
        return id;
    }
    void add(const string& key, const string& value){
        if(data.end() != data.find(key))
            cout << "Already exists" << endl;
        else
            data.insert(pair<string, string>(key,value));
    }
    string get(const string& key) const{
        return data.at(key);
    }
    void update(const string& key, const string& value){
        if(data.end() == data.find(key))
            cout << "Key doesnt exist" << endl;
        else{
            data.erase(key);
            data.insert(pair<string,string>(key,value));
        }
    }
    void remove(const string& key){
        if(data.end() == data.find(key))
            cout << "Key doesnt exist" << endl;
        else
            data.erase(key);
    }
    void display(ostream& dest) const{  // Writes key|value lines
        for(auto v: data){
            dest << v.first << "| " << v.second << endl;
        }
    }
};

class Command{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};


class addCommand : public Command{
public:
    Database* db;
    string key;
    string value;
    addCommand(Database* db, string key, string value){
        this->db = db;
        this->key = key;
        this->value = value;
    }
    void execute(){
        //add to map
        db->add(key, value);
    }
    void undo(){
        db->remove(key);
        cout << "Undid Add Command" << endl;
        db->display(cout);
        cout << endl;
    }
};

class removeCommand : public Command{
public:
    Database* db;
    string key;
    string value;
    removeCommand(Database* db, string key){
        this->db = db;
        this->key = key;
    }
    void execute(){
        value = db->get(key);
        db->remove(key);
    }
    void undo(){
        db->add(key, value);
        cout << "Undid Remove Command" << endl;
        db->display(cout);
        cout << endl;
    }
};

class updateCommand : public Command {
public:
    Database* db;
    string key;
    string value;
    string prevvalue;
    updateCommand(Database* db, string key, string value){
        this->db = db;
        this->key = key;
        this->value = value;
    }
    void execute(){
        prevvalue = db->get(key);
        db->update(key, value);
    }
    void undo(){
        db->update(key, prevvalue);
        cout << "Undid Update Command" << endl;
        db->display(cout);
        cout << endl;
    }
};

void printdb(map<string,Database*> dbs){
    cout << "\nContents of Databases:\n" << endl;
    for(auto m: dbs){
        cout << "Database "<< m.first + ":" << endl;
        m.second->display(cout);
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 0){//open and read file
        cout << "No file argument passed" << endl;
        exit(1);
    }
    string filename = "/Users/codeslinger/Desktop/C++/Program_6/Program_6/test.txt";
    lexical parser(filename);
    map<string,Database*> dbs;
    string dbid;
    string key;
    string value;
    vector<Command*> commands;
    while(parser.curr.type != parser.eof){
        //B | E | <command>....
        if(parser.curr.lexeme == "B"){
            //begin of command
            cout << "Beginning a macro..." << endl;
            parser.getNextToken();
        }
        else if (parser.curr.lexeme == "E"){
            //end of command
            cout << "Ending a macro..." << endl;
            parser.getNextToken();
        }
        else {
            ///<command> <database id> <key> <value>
            if(parser.curr.lexeme == "A"){
                //add
                parser.getNextToken();
                dbid = parser.curr.lexeme;
                parser.getNextToken();
                key = parser.curr.lexeme;
                parser.getNextToken();
                value = "";
                while(parser.curr.lexeme != "A" && parser.curr.lexeme != "R" && parser.curr.lexeme != "U" && parser.curr.lexeme != "B" && parser.curr.lexeme != "E"  && parser.curr.type != parser.eof){
                    value += parser.curr.lexeme;
                    parser.getNextToken();
                }
                if(dbs.end() == dbs.find(dbid)){
                    //db does not exist in dbs
                    Database* db = new Database(dbid);
                    dbs.insert(pair<string,Database*>(dbid,db));
                    addCommand* ad = new addCommand(dbs.at(dbid),key,value);
                    commands.push_back(ad);//add to commands
                    ad->execute();
                }
                else{
                    //db does exist in dbs
                    addCommand* ad = new addCommand(dbs.at(dbid),key,value);
                    commands.push_back(ad);
                    ad->execute();
                }
            }
            else if(parser.curr.lexeme == "R"){
                //add
                parser.getNextToken();
                dbid = parser.curr.lexeme;
                parser.getNextToken();
                key = parser.curr.lexeme;
                parser.getNextToken();
                while(parser.curr.lexeme != "A" && parser.curr.lexeme != "R" && parser.curr.lexeme != "U" && parser.curr.lexeme != "B" && parser.curr.lexeme != "E"  && parser.curr.type != parser.eof){
                    parser.getNextToken();
                }
                if(dbs.end() == dbs.find(dbid)){
                    //db does not exist in dbs
                    Database* db = new Database(dbid);
                    dbs.insert(pair<string,Database*>(dbid,db));
                    removeCommand* rd = new removeCommand(dbs.at(dbid),key);
                    commands.push_back(rd);//add to commands
                    rd->execute();
                }
                else{
                    //db does exist in dbs
                    removeCommand* rd = new removeCommand(dbs.at(dbid),key);
                    commands.push_back(rd);
                    rd->execute();
                }
            }
            else if(parser.curr.lexeme == "U"){
                //update
                parser.getNextToken();
                dbid = parser.curr.lexeme;
                parser.getNextToken();
                key = parser.curr.lexeme;
                parser.getNextToken();
                value = "";
                while(parser.curr.lexeme != "A" && parser.curr.lexeme != "R" && parser.curr.lexeme != "U" && parser.curr.lexeme != "B" && parser.curr.lexeme != "E" && parser.curr.type != parser.eof){
                    value += parser.curr.lexeme;
                    parser.getNextToken();
                }
                if(dbs.end() == dbs.find(dbid)){
                    //db does not exist in dbs
                    Database* db = new Database(dbid);
                    dbs.insert(pair<string,Database*>(dbid,db));
                    updateCommand* ud = new updateCommand(dbs.at(dbid),key,value);
                    commands.push_back(ud);//add to commands
                    ud->execute();
                }
                else{
                    //db does exist in dbs
                    updateCommand* ud = new updateCommand(dbs.at(dbid),key,value);
                    commands.push_back(ud);
                    ud->execute();
                }
            }
        }
    }
    printdb(dbs);
    for (size_t i = (commands.size()-1); i != -1; i--) {
        commands[i]->undo();
    }
    printdb(dbs);
    return 0;
}
