import core.thread;
import std.conv;
import std.stdio;




class StreamFiber(T) : Fiber {
  protected:
    bool term = false;    //  Used to terminate fiber
    T val;                //  The current stream value
    abstract void run();  //  Promise of implementation in children
  public:
    this() {              //  Constructor
      super(&run);
    }
    T get() const {
      return val;
    }
    void stop() {
      term = true;
    }
    bool done() const {
      return term;
    }
}
//select all the tri numbers 
class TrinumStream: StreamFiber!int{
  int i = 1;
  this(){
    this.val = 0;
  }
  override void run(){
    for(;;) {
      val = val+i;
      i= i+1;
      yield();
    }
  }
}

class StringStream(T):StreamFiber!string{
  StreamFiber!T stream;
  this(StreamFiber!T strm){
    this.stream = strm;
  }
  override void run(){
    for(;;){
      stream.call();
      val=to!string(stream.get());
      yield();
    }
  }
}

class FoldStream(alias f, T) : StreamFiber!T{
  StreamFiber!T stream;
  this(StreamFiber!T s, T v){
    this.val = v;
    this.stream = s;
  }
  override void run(){
    for (;;){       //
      stream.call();
      val = f(val, stream.get());
      yield();
    }
  }
}

class NumStream:StreamFiber!int{
  this(){
    this.val=0;
  }
  override void run(){
    for(;;){
      val = val+1;
      yield();
    }
  }
}



//binaray accumulator
int f (int a, int b) {
    return a + b;
}
//binary string concant
string g(string a, string b){
    return a ~ "_" ~ b;
}


void main() {
    auto f1 = new FoldStream!(f,int)(new TrinumStream,0); 
    foreach (i; 0..10) {
        f1.call;
        writeln(f1.get);
    }
    f1.stop;  

    auto f2 = new FoldStream!(g,string)(new StringStream!int(new NumStream),"0");
    foreach (i; 0..10) {
        f2.call;
        writeln(f2.get);
    }
    f2.stop;
}