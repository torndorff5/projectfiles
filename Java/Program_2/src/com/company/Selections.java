package com.company;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Vector;

public class Selections implements Observer {
    private PrintWriter pw;
    private FileWriter fw;
    Vector<StockData> selections = new Vector<>();
    Selections(){
        try {
            fw = new FileWriter("Selections.dat");
            pw = new PrintWriter(fw);
        }
        catch (IOException e){
            System.err.println("Error writing to file 'Selections.dat");
        }
    }
    @Override
    public void close() {
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
        selections.clear();
    }
    private void output(){
        select();
        pw.println("Last updated " + ss.time);
        for(StockData sd:selections){
            pw.println(sd.company + " " + sd.ticker + " " + sd.currprice + " " + sd.moneydelta + " " + sd.percentdelta +" " + sd.ytdpercentdelta + " " + sd.fiftytwohigh + " "+ sd.fiftytwolow + sd.peratio);
        }
        pw.println();
    }
    private void select(){
        //ALL, BA, BC, GBEL, KFT, MCD, TR, WAG
        for(StockData sd: ss.sv){
            if(sd.ticker.equals("ALL")||sd.ticker.equals("BA")||sd.ticker.equals("BC")||sd.ticker.equals("GBEL")||sd.ticker.equals("KFT")||sd.ticker.equals("MCD")||sd.ticker.equals("TR")||sd.ticker.equals("WAG")){
                selections.add(sd);
            }
        }
    }

}
