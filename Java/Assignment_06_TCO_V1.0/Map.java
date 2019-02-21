
//Your Map class should read in a text file that contains the map data.
// The name of the text file will be a command-line parameter.
// The format of the file is:
//        The first line contains two integers, separated by white space, that
//          tell the number of rows (r) and columns (c) in the map.
//        After the first line are r terrain lines, one for each row of the map.
//        Each terrain line contains c characters. The character at terrain line
//           row in position col represents the terrain found at location row, col of the map.

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.awt.*;

public class Map {
    static int vertboundary = 0;
    static int horiboundary = 0;
    static final int LOWBOUNDARY = 0;
    int rows;
    int columns;
    char[][] map;
    FileInputStream f = null;

    Map(String filename){
        try {
            f = new FileInputStream(filename);
            //read in two integers for rows and columns
            Scanner input = new Scanner(f);
            rows = input.nextInt();
            columns = input.nextInt();
            input.nextLine();//move to the next line
            //create map based on rows and columns
            map = new char[rows][columns];
            String line;
            for(int i = 0; i < rows; i++){//put each line into map array
                line = input.nextLine();
                line.getChars(0,line.length(),map[i],0);
            }
            //set bounds
            horiboundary = rows;
            vertboundary = columns;
        }
        catch (FileNotFoundException e){
            System.err.println("File not found.");
        }

    }

    void print(Point p){//prints out 3x3 square around location
        int x = p.x;
        int y = p.y;
        x--;
        y--;
        for(int i = 0; i < 3; i++) {
            System.out.println();
            for (int j = 0; j < 3; j++) {
                if ((x + j) < LOWBOUNDARY || (x + j) >= horiboundary || (y + i) < LOWBOUNDARY || (y + i) >= vertboundary) {
                    System.out.print('X');
                } else
                    System.out.print(map[(x + j)][(y + i)]);
            }
        }
        System.out.println();
    }


}
