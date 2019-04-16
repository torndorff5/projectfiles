package com.company;

public abstract class Component {
    String name;
    int value;
    abstract String getName();
    void add(Component c){
        throw new UnsupportedOperationException();
    }
    void remove(Component c){
        throw new UnsupportedOperationException();
    }
    void list(){
        throw new UnsupportedOperationException();
    }
    void listall(int i){
        print();
    }
    void chdir(String s){
        throw new UnsupportedOperationException();
    }
    void up(){
        throw new UnsupportedOperationException();
    }
    int count(){
        throw new UnsupportedOperationException();
    }
    int countall(){
        return 1;
    }

    abstract void print();
}
