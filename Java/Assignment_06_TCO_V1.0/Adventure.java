
import java.awt.Point;
import java.io.FileNotFoundException;
import java.util.Scanner;


//Benchmarks
//hello world***********
//player class************
//go class*************
//inventory class**************
//adventure class*************
//driver********************
//review parameters

public class Adventure {
    //commands
    //go
    //north south east west
    //inventory
    // brass lantern
    // rope
    // rations
    // staff
    //quit

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        //initialize location
        Point loc = new Point(0,0);
        //initialize map
        if (args.length > 0){
            Map m = new Map(args[0]);
            //ask for username
            System.out.println("Please enter username: ");
            String name = input.nextLine();
            //initialize player
            GameChar g = new GameChar(name,loc);
            String command;
            // prints a prompt for a command (loop through until the user types quit)
            // reads a line of input
            System.out.println("Please enter a command with parameters: \n'Go'\n\t'north'\n\t'south'\n\t'east'\n\t'west'\n'Inventory' to see what you have\n'quit' to leave the game.");
            do {
                // parses the input into a command and parameters (same line) (recognize the first letter)
                command = input.nextLine();
                if(command.startsWith("g")||command.startsWith("G")){
                    // executes the command
                    String delims = "[ ]+";
                    String[] tokens = command.split(delims);
                    String parameter;
                    try {
                        parameter = tokens[1];
                    }
                    catch(IndexOutOfBoundsException e) {
                        System.err.println("Invalid command/parameters.");
                        continue;
                    }
                    boolean error;
                    if (parameter.startsWith("n") ||parameter.startsWith("N")) {
                        error = g.go(g.NORTH, true);
                        if(!error)
                            System.out.println("Cannot move north, edge of map.");
                    }
                    else if (parameter.startsWith("S") || parameter.startsWith("s")) {
                        error = g.go(g.SOUTH, true);
                        if(!error)
                            System.out.println("Cannot move south, edge of map.");
                    }
                    else if (parameter.startsWith("E") || parameter.startsWith("e")) {
                        error = g.go(g.EAST, false);
                        if(!error)
                            System.out.println("Cannot move east, edge of map.");
                    }
                    else if (parameter.startsWith("W") || parameter.startsWith("w")){
                        error = g.go(g.WEST, false);
                        if(!error)
                            System.out.println("Cannot move west, edge of map.");
                    }
                    else {
                        System.out.println("Invalid command/parameter.");
                        continue;
                    }
                }
                else if (command.startsWith("i")||command.startsWith("I")){
                    // executes the command
                    for(int index = 0; index < g.items.length; index++){
                        System.out.println(g.items[index]);
                    }
                }
                else if (command.startsWith("q")||command.startsWith("Q")){
                    continue;
                }
                else if (command.startsWith("m")||command.startsWith("M")){
                    System.out.println("Please enter a command with parameters: \n'Go'\n\t'north'\n\t'south'\n\t'east'\n\t'west'\n'Inventory' to see what you have\n'quit' to leave the game.");
                    continue;
                }
                else{
                    System.out.println("Invalid command/parameter.");
                    continue;
                }

                //Print output
                System.out.println("Player: "+g.username);
                System.out.printf("You are at location (%s, %d) in terrain %c", g.location.x, g.location.y,m.map[g.location.x][g.location.y]);
                m.print(g.location);
                System.out.println("type 'menu' to see options");
            }
            while(!(command.startsWith("q"))&&!(command.startsWith("Q")));
            System.out.println("Quitting Game");
        }
        else
            System.out.println("Map not loaded in.");

    }

}
