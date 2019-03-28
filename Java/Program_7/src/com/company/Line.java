package com.company;

public class Line extends Shape {
    Line(){
        this.name = "line";
    }
    @Override
    void undisplay() {
        System.out.println("Terminating line display.");
    }

    @Override
    void fill() {
        System.out.println("Filling line.");
    }

    @Override
    void display() {
        System.out.println("Displaying line.");
    }

    @Override
    void setColor() {
        System.out.println("Setting line color.");
    }
}
