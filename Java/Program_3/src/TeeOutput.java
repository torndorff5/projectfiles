import java.io.IOException;
import java.io.Writer;

public class TeeOutput implements Output{
    Output op;
    private Writer sink;

    public TeeOutput(Output op, Writer stream){
        this.op = op;
        sink = stream;
    }

    @Override
    public void writeString(String s) {
        op.writeString(s);
        try {
            sink.write(s);
        }
        catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    @Override
    public void write(Object o) {
        op.write(o);
        writeString(o.toString());
    }

    public void close(){
        try {
            sink.close();
            op.close();
        }
        catch(IOException ex){
            throw new RuntimeException(ex);
        }

    }
}
