
public class LineOutput implements Output {
    Output op;
    public LineOutput(Output op){
        this.op = op;
    }
    @Override
    public void write(Object o) {
        op.write(o);
        op.writeString("\n");
    }

    @Override
    public void writeString(String s) {
        op.writeString(s + "\n");
    }

    @Override
    public void close() {
        op.close();
    }
}
