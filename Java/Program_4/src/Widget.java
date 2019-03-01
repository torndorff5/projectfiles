public class Widget implements DrawPrint {
    ResDriver d;
    Widget(ResDriver d){
        setResDriver(d);
    }
    @Override
    public void setResDriver(ResDriver d) {
        this.d = d;
    }
    void draw(){
        System.out.println("Drawing a Widget using a "+ d.res() + "DisplayDriver");
    }
}
