import java.util.function.Predicate;

public class FilterOutput implements Output,Predicate {
    Output op;
    Predicate<String> p;
    FilterOutput(Output op, Predicate<String> p){
        this.op = op;
        this.p = p;
    }
    @Override
    public void writeString(String s) {
        //check predicate, if true then write
        if(test(s))
            op.writeString(s);
    }

    @Override
    public void write(Object o) {
        if(test(o))
            op.write(o);
    }

    @Override
    public boolean test(Object o) {
        String s = o.toString();
        return p.test(s);
    }

    @Override
    public void close() {
        op.close();
    }
}
