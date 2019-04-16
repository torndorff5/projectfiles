package com.company;

import java.util.ArrayList;

public class File extends Component {
    public File(String s){
        name = s;
        value = 1;
    }
    @Override
    public String getName() {
        return name;
    }
    @Override
    void print() {
        System.out.println(name);
    }
}
