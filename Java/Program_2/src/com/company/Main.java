package com.company;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;
import java.util.Vector;
import java.util.stream.Stream;

public class Main {

    public static void main(String[] args) {
	    //Read ticker.dat into buffer
        File f = new File(args[0]);
        try{
            LocalStocks ls = new LocalStocks();
            Average a = new Average();
            Change10 ct = new Change10();
            Selections sel = new Selections();

            ls.registerObserver(a);
            ls.registerObserver(ct);
            ls.registerObserver(sel);

            Scanner input = new Scanner(f);
            String buffer;
            Vector<String> stream = new Vector<String>();
            while(input.hasNext("Last")) {
                Snapshot ss = new Snapshot();
                buffer = input.nextLine();
                Scanner parse = new Scanner(buffer);
                //get time out of first line
                parse.next();
                parse.next();
                while(parse.hasNext())
                    ss.time += parse.next() + " ";
                //loop until blank line is found
                buffer = input.nextLine();
                while(!buffer.isEmpty()) {
                    String prev;
                    String curr = "";
                    double c;
                    StockData s = new StockData();
                    //company out of next line
                    parse = new Scanner(buffer);
                    while (!parse.hasNextDouble()) {
                        curr += parse.next() + " ";
                    }
                    curr = curr.substring(0, curr.lastIndexOf(" "));
                    prev = curr.substring(curr.lastIndexOf(" ") + 1);
                    curr = curr.substring(0, curr.lastIndexOf(" "));
                    try {
                        s.company = curr;
                        s.ticker = prev;
                        c = parse.nextDouble();
                        s.currprice = c;
                        c = parse.nextDouble();
                        s.moneydelta = c;
                        c = parse.nextDouble();
                        s.percentdelta = c;
                        c = parse.nextDouble();
                        s.ytdpercentdelta = c;
                        c = parse.nextDouble();
                        s.fiftytwohigh = c;
                        c = parse.nextDouble();
                        s.fiftytwolow = c;
                        c = parse.nextDouble();
                        s.peratio = c;
                    } catch (Exception e) {
                        s.peratio = 0.0;
                    }
                    ss.sv.addElement(s);
                    buffer = input.nextLine();
                }
                ls.setSnapShot(ss);
            }
            ls.close();
        }
        catch(FileNotFoundException e) {
            System.err.println("File not found");
        }

    }
}
