import std.stdio;
import std.algorithm;
import std.functional;
import std.array;
import std.range;


struct Deque(T){
    //properties
    T[] front_, back_;//left half of deque
   	//right half of deque
   	size_t front_count;
    size_t back_count;
    size_t d_size = 10;
    //functions
    void push_front(T x){
        //add to front array
        front_ ~= x;
        front_count++;
    }
    void push_back(T x){
        //add to front array
        back_ ~= x;
        back_count++;
    }
    ref T at(size_t pos){
        size_t n = (back_count + front_count)-1;
        size_t m = front_count-1;
        if (pos <= m){
            return (front_[m-pos]);
        }
        else{
            return (back_[(pos-front_count)]); 
        }                 
    }
    ref T back(){
        //back of the back array
        return back_[(back_count-1)];
    }
    ref T front(){
        //back of the front array 
        return front_[(front_count-1)];
    }
    T pop_front(){
        if(front_count>0)
        	return front_[--front_count];
        else{
            front_count = 0;
            T n = back_[0];
            back_ = back_.remove(0);
            back_count--;
            return n;
        }
    }
    T pop_back(){
        if(back_count>0)
        	return back_[--back_count];
        else{
            back_count = 0;
            T n = front_[0];
            front_ = front_.remove(0);
            front_count--;
            return n;
        }
    }
    auto size(){
        return back_count + front_count;
    }
}

