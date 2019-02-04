package com.company;

public class StockData {
    public String company;
    public String ticker;
    public double currprice;
    public double moneydelta;
    public double percentdelta;
    public double ytdpercentdelta;
    public double fiftytwohigh;
    public double fiftytwolow;
    public double peratio;
    StockData(){
        company="";
        ticker="";
        currprice=0.0;
        moneydelta=0.0;
        percentdelta=0.0;
        ytdpercentdelta=0.0;
        fiftytwohigh=0.0;
        fiftytwolow=0.0;
        peratio=0.0;
    }
}
