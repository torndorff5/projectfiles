
//
//  main.cpp
//  Program 7
//
//  Created by Tanner Orndorff on 4/25/18.
//  Copyright © 2018 Monocle Heads. All rights reserved.
//


// Note: Uses an atomic to decrement nprod and nfilt
#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <future>

using namespace std;
//benchmarks
//produce 1000 random integers and store in queue************
//search through those produced and put multiples of 3 in a different queue************
//group the multiples of 3 into 10 different queues based on their remainder*************
class PipelineTask {
public:
    static queue<int> q;
    static queue<int> mult3;
    static condition_variable q_cond, mult3_cond;
    static mutex q_sync, mult3_sync, print;
    static atomic_size_t nprod, nfilt;
    static ofstream output;
    static ofstream output0;
    static ofstream output1;
    static ofstream output2;
    static ofstream output3;
    static ofstream output4;
    static ofstream output5;
    static ofstream output6;
    static ofstream output7;
    static ofstream output8;
    static ofstream output9;
public:
    static const size_t nprods = 4, nfilts = 3, ngroup = 10;;
    static void filter() {
        for (;;) {
            // Get lock for sync mutex
            unique_lock<mutex> qlck(q_sync);
            // Wait for queue to have something to process
            q_cond.wait(qlck,[](){return !q.empty() || !nprod;});
            if (q.empty()) {
                if (!nprod)     // nprod could have changed already
                    break;
                else
                    continue;   // All done
                
            }
            auto x = q.front();
            if (x % 3 == 0)
            {
                q.pop();
                qlck.unlock();
                // Print trace of consumption
                lock_guard<mutex> multlck(mult3_sync);
                mult3.push(x);
                mult3_cond.notify_one();
                lock_guard<mutex> plck(print);
                output << x << " filtered" << endl;
            }
            else
            {
                q.pop();
                qlck.unlock();
                lock_guard<mutex> plck(print);
                output << x << " consumed" << endl;
            }
            
        }
        //notify all that it is empty
        --nfilt;
        mult3_cond.notify_all();
    }
    static int group(int mod) {
        int count = 0;
        for(;;) {
            //get lock for sync mutex
            unique_lock<mutex> flck(mult3_sync);
            //wait for queue to have something to process
            mult3_cond.wait(flck,[](){return !mult3.empty() || !nfilt;});
            if(mult3.empty()){
                if (nprod == 0)     // nprod could have changed already
                    break;
                else
                    continue;   // All done
            }
            auto x = mult3.front();
            if (x % 10 == mod) {
                mult3.pop();
                //print to correct file
                switch(mod){
                    case 0:
                        output0 << x << endl;
                        count++;
                        break;
                    case 1:
                        output1 << x << endl;
                        count++;
                        break;
                    case 2:
                        output2 << x << endl;
                        count++;
                        break;
                    case 3:
                        output3 << x << endl;
                        count++;
                        break;
                    case 4:
                        output4 << x << endl;
                        count++;
                        break;
                    case 5:
                        output5 << x << endl;
                        count++;
                        break;
                    case 6:
                        output6 << x << endl;
                        count++;
                        break;
                    case 7:
                        output7 << x << endl;
                        count++;
                        break;
                    case 8:
                        output8 << x << endl;
                        count++;
                        break;
                    case 9:
                        output9 << x << endl;
                        count++;
                        break;
                }
                flck.unlock();
            }
            else {
                flck.unlock();
            }
        }
        lock_guard<mutex> plck(print);
        cout << "Group " << mod << " has " << count << " numbers." << endl;
        return count;
    }
    static void produce(int i) {
        // Generate 10000 random ints
        srand(time(nullptr)+i);
        for (int i = 0; i < 10000; ++i) {
            int n = rand();     // Get random int
            // Get lock for queue; push int
            unique_lock<mutex> slck(q_sync);
            q.push(n);
            slck.unlock();
            q_cond.notify_one();//wakes one waiting thread
            // Get lock for print mutex
            lock_guard<mutex> plck(print);
            output << n << " produced" << endl;
            
        }
        // Notify consumers that a producer has shut down
        --nprod;
        q_cond.notify_all();//wake all waiting threads d
    }
};

queue<int> PipelineTask::q;
queue<int> PipelineTask::mult3;
condition_variable PipelineTask::q_cond, PipelineTask::mult3_cond;
mutex PipelineTask::q_sync, PipelineTask::mult3_sync, PipelineTask::print;
ofstream PipelineTask::output("output.out");
ofstream PipelineTask::output0("output0.out");
ofstream PipelineTask::output1("output1.out");
ofstream PipelineTask::output2("output2.out");
ofstream PipelineTask::output3("output3.out");
ofstream PipelineTask::output4("output4.out");
ofstream PipelineTask::output5("output5.out");
ofstream PipelineTask::output6("output6.out");
ofstream PipelineTask::output7("output7.out");
ofstream PipelineTask::output8("output8.out");
ofstream PipelineTask::output9("output9.out");
atomic_size_t PipelineTask::nprod(nprods), PipelineTask::nfilt(nfilts);

int main() {
    vector<thread> prods, cons, groups;
    for (size_t i = 0; i < PipelineTask::nfilt;++i)
        cons.push_back(thread(&PipelineTask::filter));
    for (size_t i = 0; i < PipelineTask::nprods; ++i)
        prods.push_back(thread(&PipelineTask::produce,i));
    for (size_t i = 0; i < PipelineTask::ngroup; ++i)
        groups.push_back(thread(&PipelineTask::group,i));
    
    // Join all threads
    for (auto &p: prods)
        p.join();
    for (auto &c: cons)
        c.join();
    for (auto &g: groups)
        g.join();
    
    return 0;
}


//I liked this assignment. It was pretty easy and went smoothly until the end when my group threads werent exiting at all. It took a while to figure out what the problem was, but then I realized that my wait condition was only returning if mult 3 was not empty. once i fixed this, eveyrthing worked great.
