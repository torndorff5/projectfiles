package com.company;

public class Point extends Shape {
    Point(){
        this.name = "point";
    }
    @Override
    void undisplay() {
        System.out.println("Terminating point display.");
    }

    @Override
    void display() {
        System.out.println("Displaying point.");
    }

    @Override
    void fill() {
        System.out.println("Filling point.");
    }

    @Override
    void setColor() {
        System.out.println("Setting point color.");
    }
}
