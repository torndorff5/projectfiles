import std.stdio;
import std.typecons;
import std.array;
import std.conv;

struct Semimap(K,V) {
    private Nullable!(V)[K] stuff;
    auto pairCount(){
        int icount = 0; 
        foreach(i;stuff){
         	//if is is not null, count++
            if(!(i.isNull))
                icount++;
        }
        return icount;
    }
    auto singCount(){
        int icount = 0;
        foreach(i;stuff){
            //if i is null, count++
            if(i.isNull)
                icount++;
        }
        return icount;
    }
    auto count(){
        return tuple( singCount, pairCount);
    }
    auto hasKey(K key) const {
        return cast(bool)(key in stuff); 
    }
    auto keys() const {
        return stuff.keys;
    }
    auto values() const {
        string[] vals;
    	foreach(key,val; stuff)
      		if(!val.isNull)
        		vals~=val;
    	return vals;
    }
    auto get(K key) const{
        return stuff[key];
    }
    auto byKey() const {
        return stuff.byKey;
    }
    auto byValue() const {
        return stuff.byValue;
    }
    void set(K key) {
        stuff[key] = Nullable!(V).init;
    }
    void set(K key, V val) {
        stuff[key] = val;
    }
    auto reset(K key) {
        stuff[key].nullify;
    }
    auto remove(K key) {
        stuff.remove(key);
    }
    //to string 
    string toString() const{
        string output = "[";
        bool start = true;
        foreach(i ; stuff.keys){
            if (!start)
                output ~= ",";
            else
                start = false;
            if(stuff[i].isNull){
                output ~= to!string(i);
            }
            else{
                output ~= to!string(i);
                output ~= ":";
                output ~= to!string(stuff[i]);
            }
        }
        output ~= "]";
        return output;
   	}
}

void main() { 
    Semimap!(int,string) sm; 
    writeln(sm); 			// [] 
    sm.set(2); 
    sm.set(1,"one");
    sm.set(3); 
    writeln(sm.count); 
    writeln(sm.pairCount); 
    writeln(sm.singCount); 
    writeln(sm);
    writeln(sm.hasKey(1)); 
    writeln(sm.get(1)); 
    writeln(sm.hasKey(10)); 
    auto val = sm.get(2); 
    assert(val.isNull); 
    writeln(sm.keys); 
    writeln(sm.values); 
    foreach(k; sm.byKey) 
    	writeln("key = ",k); 
    foreach(v; sm.byValue) 
    	if (!v.isNull) 
    		writeln("value = ",v); 
    sm.set(3,"three"); 
    writeln(sm); 
    sm.reset(3); 
    writeln(sm); 
    sm.remove(3); 
    writeln(sm); 
}