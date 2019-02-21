//JIMachine benchmarks
//hello world on gui**************
//button hello world ***************
//open image file ************************
//  new Image(file.toURI().toURL().toExternalForm());
//zoom in *************
//display at original size********************
//zoom out********************
//quit the program********************
//name main JIM machine

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.*;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.scene.input.KeyEvent;

public class JIMachine extends Application {
    //buttons
    Button opnimg;
    Button zmin;
    Button orgsz;
    Button zmout;
    Button quit;
    Button prev;
    Button next;
    Button thumb;
    Button caption;

    boolean tnv = false; //thumbnail view

    //FileChooser
    FileChooser fileChooser;

    //File
    File file;
    File directory;
    File[] contents;
    String folder;

    //Desktop
    private Desktop desktop = Desktop.getDesktop();

    //Image
    Image i;
    ImageView iv;
    ImageView[] thumbnail = new ImageView[4];
    TextField cap = new TextField();
    String[] captions;


    //Image index
    static int current = 0;
    static int currentTN = 0;
    static int photocount = 0;

    //Displays
    GridPane tn = new GridPane();
    GridPane bgrid = new GridPane();
    GridPane grid = new GridPane();
    BorderPane bp = new BorderPane();
    Scene scene = new Scene(bp, 1000, 1000);
    VBox center = new VBox();


    @Override
    public void start(Stage primaryStage) throws Exception{
        //set page title
        primaryStage.setTitle("JIMachine");

        //Button functionality *****************************************************
        //open image button
        opnimg  = new Button("Open Image");
        zmin = new Button("Zoom In");
        orgsz = new Button("Original Size");
        zmout = new Button("Zoom Out");
        quit = new Button("Quit");
        prev = new Button("Previous");
        next = new Button("Next");
        thumb = new Button("Thumbnail View");
        caption = new Button("Caption");

        //Initiate File Chooser
        fileChooser = new FileChooser();
        //Set up directory
        contents = getDir();
        captions = new String[photocount];
        //initate captions
        cap.setText("Enter Caption Here");

        next.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                //check for thumbnail view
                if(tnv){
                    if(currentTN + 4 <= photocount - 4){
                        currentTN+=4;
                        displayTN(currentTN);
                    }
                }
                else{
                    //check to see if there is another image file
                    if((current+1) < photocount){
                        current++;
                        //open new current
                        openFile(contents[current]);
                        iv.setImage(i);
                    }
                }

            }
        });

        prev.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                if(tnv){
                    if(currentTN - 4 >= 0){
                        currentTN-=4;
                        displayTN(currentTN);
                    }
                }
                else{
                    //check to see if there is another image file
                    if ((current - 1) >= 0) {
                        current--;
                        //open new current
                        openFile(contents[current]);
                        iv.setImage(i);
                    }
                }
            }
        });

        opnimg.setOnAction(new EventHandler<javafx.event.ActionEvent>() {
            @Override
            public void handle(javafx.event.ActionEvent event) {
                //open image file
                file = fileChooser.showOpenDialog(primaryStage);
                if (file != null) {
                    openFile(file);
                    iv.setImage(i);
                }
            }
        });

        zmin.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                //change view of picture to zoomed in 25% larger
                double scaleX = iv.getScaleX();
                double scaleY = iv.getScaleY();
                iv.setScaleX(scaleX * 1.25);
                iv.setScaleY(scaleY * 1.25);
            }
        });

        orgsz.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                iv.setScaleY(1);
                iv.setScaleX(1);
            }
        });

        zmout.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                //change view of picture to zoomed out 25% larger
                double scaleX = iv.getScaleX();
                double scaleY = iv.getScaleY();
                iv.setScaleX(scaleX *.75);
                iv.setScaleY(scaleY *.75);
            }
        });

        quit.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.exit(0);
            }
        });

        thumb.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                //go into thumbnail view
                tnv = !tnv;
                if(tnv) {
                    displayTN(current-(current%4));
                    bgrid.getChildren().remove(caption);
                }
                else{
                    //go from tnv to regular
                    openFile(contents[current]);
                    iv.setImage(i);
                    iv.fitWidthProperty().bind(bp.widthProperty());
                    iv.fitHeightProperty().bind(bp.heightProperty());
                    bp.setCenter(iv);
                    bp.setLeft(grid);
                    bp.setTop(bgrid);
                    bgrid.add(caption,19,0);
                }
            }
        });
        caption.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                center.getChildren().add(cap);
                center.getChildren().add(iv);
                bp.setCenter(center);
            }
        });

        scene.setOnKeyPressed(new EventHandler<KeyEvent>() {
            @Override
            public void handle(KeyEvent event) {
                switch (event.getCode()) {
                    case LEFT:  prev.fire();
                    case RIGHT: next.fire();
                }
            }
        });

        //Display Settings *****************************************************

        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);

        bgrid.setAlignment(Pos.CENTER);
        bgrid.setHgap(10);
        bgrid.setVgap(10);

        //Image Display
        try{
            openFile(contents[0]);//open up first image in directory
            iv = new ImageView(i);
        }
        catch(Exception e){
            iv = new ImageView();
        }



        grid.add(opnimg,3,1);
        grid.add(zmin,3,2);
        grid.add(orgsz,3,3);
        grid.add(zmout,3,4);
        grid.add(quit,3,5);

        bgrid.add(caption,19,0);
        bgrid.add(next,15,0);
        bgrid.add(prev,14,0);
        bgrid.add(thumb,18,0);

        bp.setLeft(grid);
        bp.setTop(bgrid);
        iv.fitWidthProperty().bind(bp.widthProperty());
        iv.fitHeightProperty().bind(bp.heightProperty());
        bp.setCenter(iv);




        primaryStage.setScene(scene);

        primaryStage.show();
    }

    void openFile(File file){
        //  new Image(file.toURI().toURL().toExternalForm());
        try {
            i = new Image(file.toURI().toURL().toExternalForm());
        }
        catch (IOException ex){
            Logger.getLogger(JIMachine.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    File[] getDir(){
        folder = System.getProperty("user.dir");
        directory = new File(folder);
        contents = directory.listFiles();
        File[] temp = new File[contents.length];
        int i = 0;
        String name;
        for (File c: contents){
            int index = -1;
            name = c.getName();
            name = name.toLowerCase(Locale.US);
            index = name.indexOf(".jpg");
            if (index != -1) {
                temp[i++] = c;
                photocount++;
            }
        }
        return temp;
    }
    void displayTN(int start){
        bp.setCenter(tn);
        tn.setAlignment(Pos.TOP_CENTER);
        tn.setMaxWidth(500);
        tn.setMaxHeight(500);
        for (int j = 0; j < 4; j++) {
            if (contents[start] != null) {
                openFile(contents[start++]);
                thumbnail[j] = new ImageView(i);
                thumbnail[j].setFitWidth(200);
                thumbnail[j].setFitHeight(150);
                tn.add(thumbnail[j], j, 0);
            }
        }
        bp.setLeft(null);
    }

    public static void main(String[] args) {
        launch(args);
    }
}
