package com.company;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Average implements Observer {
    private FileWriter fw;
    private PrintWriter pw;
    @Override
    public void update(Snapshot s) {
         ss.sv = s.sv;
         ss.time = s.time;
         output();
    }
    Average(){
        try {
            fw = new FileWriter("Average.dat");
            pw = new PrintWriter(fw);
        }
        catch (IOException e){
            System.err.println("Error writing to file 'Average.dat");
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


    private void output(){
        try{
            //calc average
            double average = calcAverage();
            pw.printf(ss.time + ", " + "Average price: %f\n", average );
        }
        catch (NullPointerException e){
            System.err.println("Error writing to file 'Average.dat");
        }

    }

    private double calcAverage(){
        double sum = 0.0;
        int num = 0;
        for(StockData sd : ss.sv){
            sum += sd.currprice;
            num++;
        }
        return sum/num;
    }
}
