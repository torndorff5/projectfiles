package com.company;

public class Main {

    public static void main(String[] args) {
	Milk m = new Milk(new HotChocolate());
	double price = m.cost();
	System.out.println(price);
    }
}
