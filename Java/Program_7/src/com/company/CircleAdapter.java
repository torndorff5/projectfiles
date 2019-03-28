package com.company;

public class CircleAdapter extends Shape{
    private XXCircle xc;
    CircleAdapter(XXCircle xc){
        this.xc = xc;
        this.name = "circle";
    }

    @Override
    void setLocation() {
        xc.setLocation();
    }

    @Override
    void getLocation() {
        xc.getLocation();
    }

    @Override
    void display() {
        xc.displayIt();
    }

    @Override
    void undisplay() {
        xc.undisplayit();
    }

    @Override
    void setColor() {
        xc.setItsColor();
    }

    @Override
    void fill() {
        xc.fillIt();
    }
}
