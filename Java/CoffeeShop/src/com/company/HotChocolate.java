package com.company;

public class HotChocolate extends Beverage {
    HotChocolate(){
        description = "House made creamy hot chocolate";
    }
    @Override
    double cost() {
        return 1.99;
    }
}
