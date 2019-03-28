package com.company;

public class Rectangle extends Shape {
    Rectangle(){
        this.name = "rectangle";
    }
    @Override
    void display() {
        System.out.println("Displaying rectangle.");
    }

    @Override
    void undisplay() {
        System.out.println("Terminating rectangle display.");
    }

    @Override
    void fill() {
        System.out.println("Filling rectangle.");
    }

    @Override
    void setColor() {
        System.out.println("Setting rectangle color.");
    }
}
