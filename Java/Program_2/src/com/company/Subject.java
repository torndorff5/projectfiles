package com.company;

public interface Subject  {
    void registerObserver(Observer o);
    void removeObserver(Observer o);
    void notifyObservers();
}
