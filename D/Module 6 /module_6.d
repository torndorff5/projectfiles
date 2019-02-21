import std.stdio;
import std.algorithm;
import std.functional;
import std.array;

auto inclist(int[] nums, int x) pure {
    return map!(a=>a+x)(nums);
}
auto squarelist (int[] nums) pure{
    return map!(a=>a*a)(nums);
}
auto sqsum (int[] nums) pure {
    return fold!((a,b)=>a + b*b)(nums,0);
}
auto evens (int[] nums) pure {
    return filter!(a=>a%2 == 0)(nums);
}
auto bxor (bool[] list) pure {
    return fold!((a,b)=>a!=b)(list,list[0]);
}
auto duplist(T)(T[] list){
   return fold!((a,b)=>a~b~b)(list,cast(T[])[]);
}
//auto compose_n (T)(T[] flist){    
//    
//}

void main()
{
    int[] nums = [1,2,3,4,5];
    writeln(inclist(nums,1));
    writeln(squarelist(nums));
    writeln(sqsum(nums));
    writeln(evens(nums));
    writeln(bxor([false,true]));
    writeln(duplist(nums));
    writeln(duplist(["a","b"]));
    //auto f = compose_n([(real a)=>a/3.0,(real a)=>a*a,(real a)=>a+1.0]);
    writeln("Hello D");
}