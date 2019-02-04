package com.company;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Vector;

public class Change10 implements Observer {
    private FileWriter fw;
    private PrintWriter pw;
    private Vector<StockData> changelist = new Vector<>();

    Change10(){
        try {
            fw = new FileWriter("Change10.dat");
            pw = new PrintWriter(fw);
        }
        catch (IOException e){
            System.err.println("Error writing to file 'Change10.dat");
        }
    }


    public void close(){
        try{
            pw.close();
            fw.close();
        }
        catch (IOException e){
            System.err.println("Error writing to file 'Average.dat");
        }
    }

    @Override
    public void update(Snapshot s) {
        this.ss.sv = s.sv;
        this.ss.time = s.time;
        output();
        changelist.clear();
    }

    private void output(){
        find10();
        pw.println(ss.time + ":");
        for (StockData sd: changelist) {
            pw.print(sd.ticker + " " + sd.currprice + " " + sd.percentdelta + "\n");
        }
        pw.println();
    }

    private void find10(){
        final int CHANGE = 10;
        for(StockData sd : ss.sv){
            if(Math.abs(sd.percentdelta) > CHANGE)
                changelist.add(sd);
        }
    }
}
