import java.io.*;
import java.util.Scanner;
import java.util.function.Predicate;

public class Main {

    public static void main(String[] args) {
        String filename;
        OutputStreamWriter out = new OutputStreamWriter(System.out);
        Output op = new StreamOutput(out);
        Predicate<String> x = (String s)->{
            if (s.matches(".*\\d+.*"))
                return true;
            else
                return false;
        };
        Predicate<String> y = (String s)->{
            if(s.contains("A"))
                return true;
            else
                return false;
        };
        String buffer="";
        Scanner main = new Scanner(System.in);
        System.out.println("Please input file to read from:");
        filename = main.nextLine();
        while(!buffer.equals("d")) {
            System.out.println("Please select which decorations to apply:\n[1]LineOutput\n[2]NumberedOutput\n[3]TeeOutput\n[4]FilterOutput\n[d]Done\n");
            buffer = main.next();
            if(buffer.equals("1")){
                op = new LineOutput(op);
                System.out.println("LineOutput decorated.");
            }
            else if (buffer.equals("2")){
                op = new NumberedOutput(op);
                System.out.println("NumberedOutput decorated.");
            }
            else if (buffer.equals("3")){
                System.out.println("Please enter second filename:");
                buffer = main.next();
                try {
                    op = new TeeOutput(op, new PrintWriter(buffer, "UTF-8"));
                    System.out.println("TeeOutput decorated.");
                }
                catch(FileNotFoundException e){
                    System.err.println("Error reading file.");
                }
                catch(UnsupportedEncodingException e){
                    System.err.println("Unsupported Encoding Exception.");
                }
            }
            else if (buffer.equals("4")){
                System.out.println("Please select predicate:\n[x]ContainsDigit\n[y]Contains'A'\n");
                buffer = main.next();
                if(buffer.equals("x")){
                    op = new FilterOutput(op,x);
                    System.out.println("FilterOutput decorated with predicate ContainsDigit");
                }
                else if(buffer.equals("y")){
                    op = new FilterOutput(op,y);
                    System.out.println("FilterOutput decorated with predicate Contains'A'");
                }

            }
            else
                continue;
        }
        try {
            File f = new File(filename);
            Scanner input = new Scanner(f);
            while(input.hasNextLine()) {
                String s = input.nextLine();
                op.writeString(s);
            }
            op.close();
        }
        catch(FileNotFoundException e ){
            System.err.println("Error reading file.");
        }
    }
}
