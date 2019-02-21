import javafx.application.Application;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.Label;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;
import java.lang.Runnable;
import java.lang.Thread;
import java.net.UnknownHostException;


public class ChatClient extends Application {
    //Thread Class
    Thread thread;
    //Username and Port
    static String username = "Anonymous";//default username
    static int port_num = 4688;//default port number
    //Network Variables
    static OutputStream outStream;
    static Socket s;
    static PrintWriter out;
    static InputStream inStream;
    static Scanner in;
    //buttons
    Button sendmsg;
    Button disconnect;
    //text boxes
    TextArea chat;
    TextArea msg;
    //Scroll pane for chat
    ScrollPane sp;
    //Labels
    Label dir;

    //update chat function
    public synchronized void updateChat(String msg){//update chat field by appending message to end
        chat.appendText(msg + "\n\n");
    }

    //Thread and Task Classes
    public class Recv implements Runnable {
        @Override
        public void run() {
            //custom thread execution
            try {
                inStream = s.getInputStream();
                in = new Scanner(inStream);
                for(;;) {
                    String reply = in.nextLine();
                    updateChat(reply);
                }
            }
            catch (IOException e){
                System.err.println("Error connecting with server");
            }

        }
    }



    @Override
    public void start(Stage primaryStage) throws Exception{
        //Initialize Buttons
        sendmsg = new Button("Send");
        disconnect = new Button("Disconnect from Chat");
        //Initialize Labels
        dir = new Label("Hello, " + username + ". Start chatting below.");
        //Initialize text fields
        msg = new TextArea();
        msg.setWrapText(true);
        chat = new TextArea();
        chat.setWrapText(true);
        msg.setWrapText(true);
        chat.setEditable(false);
        //Initialize Scroll pane
        sp = new ScrollPane();
        sp.setContent(chat);
        sp.setVbarPolicy(ScrollPane.ScrollBarPolicy.AS_NEEDED);
        sp.setHbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        sp.setFitToHeight(true);
        sp.setFitToWidth(true);
        //Event Handlers
        //send msg
        sendmsg.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                //send message to server
                String message = msg.getText();
                out.println(message);
                //clear msg field
                msg.clear();
                //update chat
                updateChat(username + ": " + message);
            }
        });
        //Disconnect from server
        disconnect.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                out.println("disconnect " + username);
            }
        });
        //Display settings *************************
        GridPane grid = new GridPane();
        grid.add(dir,3,0,3,1);
        grid.add(msg,3,1, 3,3);
        grid.add(sendmsg,3,4);
        grid.add(disconnect,4,4);
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);

        BorderPane bp = new BorderPane();

        bp.setLeft(grid);
        bp.setCenter(sp);

        //Set margins
        BorderPane.setMargin(grid,new Insets(10,10,10,10));
        BorderPane.setMargin(sp,new Insets(10,10,10,10));

        Scene scene = new Scene(bp, 1000, 1000);

        primaryStage.setScene(scene);
        primaryStage.setTitle(username + "'s Chat Room");
        primaryStage.show();

        //connect to server
        try{
            //connect to server with port_num
            s = new Socket("localhost",port_num);
            outStream = s.getOutputStream();
            out = new PrintWriter(outStream,true);
            //connect username to tell server which name to add
            out.println("connect " + username);
            //start inner thread that waits for messages from server to post to chat
            Recv listen = new Recv();
            thread = new Thread(listen);
            thread.start();

        }
        catch (UnknownHostException e){
            System.err.println("Error connecting to chat server.");
            primaryStage.close();
        }
        catch (IOException e){
            System.err.println("Error connecting to chat server.");
            primaryStage.close();
        }

    }

    public static void main(String[] args) {
        if (args.length == 1) {
            try {
                username = args[0];
            }
            catch (RuntimeException e){
                System.err.println("Invalid arguments.");
            }

        }
        else if (args.length == 2) {
            try {
                username = args[0];
                port_num = Integer.parseInt(args[1]);
            }
            catch (RuntimeException e){
                System.err.println("Invalid arguments.");
            }
        }
        launch(args);
    }
}

