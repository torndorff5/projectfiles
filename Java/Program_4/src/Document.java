import javax.print.Doc;

public class Document implements DrawPrint {
    ResDriver d;
    Document(ResDriver d){
        setResDriver(d);
    }
    @Override
    public void setResDriver(ResDriver d) {
        this.d = d;
    }

    void print(){
        System.out.println("Printing a Document using a "+ d.res() + "PrintDriver");
    }
}
