package com.company;

public class Milk extends CondimentDecorator {
    Beverage b;
    Milk(Beverage b){
        this.b = b;
    }
    @Override
    double cost() {
        double c = b.cost();
        return c + .2;
    }
}
