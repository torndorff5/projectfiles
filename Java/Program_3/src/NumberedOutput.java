public class NumberedOutput implements Output{
    Output op;
    int count;
    NumberedOutput(Output op){
        this.op = op;
        count = 0;
    }
    @Override
    public void write(Object o) {
        String temp = getLineNum();
        op.writeString(temp);
        op.write(o);
        op.writeString("/n");
    }

    @Override
    public void writeString(String s) {
        String temp = getLineNum();
        op.writeString(temp);
        op.writeString(s);
        op.writeString("\n");
    }
    private String getLineNum(){
        String s = String.format("%05d: ",count++);
        return s;
    }

    @Override
    public void close() {
        op.close();
    }
}
