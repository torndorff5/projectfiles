package com.company;

import java.util.ArrayList;

public class LocalStocks implements Subject {
    private ArrayList<Observer> observers = new ArrayList<>();
    private Snapshot ss = new Snapshot();
    @Override
    public void notifyObservers() {
        for(Observer o : observers)
            o.update(ss);
    }

    @Override
    public void registerObserver(Observer o) {
        observers.add(o);
    }

    @Override
    public void removeObserver(Observer o) {
        int i =observers.indexOf(0);
        if(i>= 0) {
            o.close();
            observers.remove(i);
        }
    }

    public void setSnapShot(Snapshot ss){
        this.ss.time = ss.time;
        this.ss.sv = ss.sv;
        notifyObservers();
    }
    public void close(){
        for(Observer o : observers)
            o.close();
    }
}
