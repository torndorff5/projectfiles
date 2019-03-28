package com.company;

public class Shape {
    String name = "shape";
    void setLocation(){
        System.out.println("Location is set.");
    }
    void getLocation(){ System.out.println("Location is retrieved.");}
    void display(){System.out.println("Displaying shape.");}
    void fill(){System.out.println("Filling shape.");}
    void setColor(){System.out.println("Setting shape color.");}
    void undisplay(){System.out.println("Terminating shape display");}

}
