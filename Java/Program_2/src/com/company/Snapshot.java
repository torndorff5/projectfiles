package com.company;

import java.util.Vector;

public class Snapshot {
    Vector<StockData> sv;
    String time;
    Snapshot(){
        sv = new Vector<>();
        time = "";
    }
}
