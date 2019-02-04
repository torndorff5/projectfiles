package com.company;


public interface Observer {
    void update(Snapshot s);
    void close();
    Snapshot ss = new Snapshot();
}
