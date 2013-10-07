//
//  main.cpp
//  pipeline_sim
//
//  Created by Veroinica Kirin on 10/6/13.
//  Copyright (c) 2013 Xin Zhang. All rights reserved.
//



#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <stack>
#include <chrono>


using namespace std;

struct inst
{
    explicit inst(string name, string stage)
    {
        iName = name;
        iStage = stage;
    }
    
    string iName;
    string iStage;
    mutex mMutex;
};

stack<string> stg_stk;

void stg_init(stack<string> *stg_stk){
    stg_stk->push("$");
    stg_stk->push("$");
    stg_stk->push("$");
    stg_stk->push("$");
    stg_stk->push("IF");
}


void transfer( inst &i1, inst &i2, inst &i3, inst &i4, inst &i5){
    
    // don't actually take the locks yet
    unique_lock<mutex> lock1( i1.mMutex, defer_lock );
    unique_lock<mutex> lock2( i2.mMutex, defer_lock );
    unique_lock<mutex> lock3( i3.mMutex, defer_lock );
    unique_lock<mutex> lock4( i4.mMutex, defer_lock );
    unique_lock<mutex> lock5( i5.mMutex, defer_lock );
    
    // lock both unique_locks without deadlock
    lock( lock1, lock2, lock3, lock4, lock5 );
    
    stack<string> *ptr = &stg_stk;
    
    if (ptr->top() != "$") {
        i1.iStage = ptr->top();
        ptr->pop();
        if (ptr->top() != "$") {
            i2.iStage = ptr->top();
            ptr->pop();
            if (ptr->top() != "$") {
                i3.iStage = ptr->top();
                ptr->pop();
                if (ptr->top() != "$") {
                    i4.iStage = ptr->top();
                    ptr->pop();
                    if (ptr->top() != "$") {
                        i5.iStage = ptr->top();
                        ptr->pop();
                        ptr->push("IF");
                        ptr->push("ID");
                        ptr->push("EX");
                        ptr->push("MEM");
                        ptr->push("WB");
                        
                        // from here we should increase instruction queue index.
                        
                    }
                    else{
                        ptr->push("IF");
                        ptr->push("ID");
                        ptr->push("EX");
                        ptr->push("MEM");
                        ptr->push("WB");
                    }
                }
                else{
                    ptr->push("IF");
                    ptr->push("ID");
                    ptr->push("EX");
                    ptr->push("MEM");
                }
            }
            else{
                ptr->push("IF");
                ptr->push("ID");
                ptr->push("EX");
            }
        }
        else{
            ptr->push("IF");
            ptr->push("ID");
        }
        
    }
    else ptr->push("IF");;

    
    // output log
    cout << i1.iName << "'s stage is " << i1.iStage << endl;
    cout << i2.iName << "'s stage is " << i2.iStage << endl;
    cout << i3.iName << "'s stage is " << i3.iStage << endl;
    cout << i4.iName << "'s stage is " << i4.iStage << endl;
    cout << i5.iName << "'s stage is " << i5.iStage << endl;
    cout << "\n";
    
    i1.iStage = "$";
}


int main(int argc, const char * argv[])
{
    inst Instruction1( "Instruction_1", "$" );
    inst Instruction2( "Instruction_2", "$" );
    inst Instruction3( "Instruction_3", "$" );
    inst Instruction4( "Instruction_4", "$" );
    inst Instruction5( "Instruction_5", "$" );
    inst Instruction6( "Instruction_6", "$" );
    inst Instruction7( "Instruction_6", "$" );
    
    
    // Initialize stack that is storing stages.
    stg_init(&stg_stk);
    
    
    thread t1( [&](){ transfer( Instruction1, Instruction2, Instruction3, Instruction4, Instruction5 ); } );
    thread t2( [&](){ transfer( Instruction1, Instruction2, Instruction3, Instruction4, Instruction5 ); } );
    thread t3( [&](){ transfer( Instruction1, Instruction2, Instruction3, Instruction4, Instruction5 ); } );
    
    /*
    thread t4( [&](){ transfer( Instruction1, Instruction2, Instruction3, Instruction4, Instruction5 ); } );
    thread t5( [&](){ transfer( Instruction1, Instruction2, Instruction3, Instruction4, Instruction5 ); } );
    thread t6( [&](){ transfer( Instruction2, Instruction3, Instruction4, Instruction5, Instruction6 ); } );
    thread t7( [&](){ transfer( Instruction2, Instruction3, Instruction4, Instruction5, Instruction6 ); } );
    thread t8( [&](){ transfer( Instruction2, Instruction3, Instruction4, Instruction5, Instruction6 ); } );
    thread t9( [&](){ transfer( Instruction2, Instruction3, Instruction4, Instruction5, Instruction6 ); } );
    thread t10( [&](){ transfer( Instruction2, Instruction3, Instruction4, Instruction5, Instruction6 ); } );
    thread t11( [&](){ transfer( Instruction3, Instruction4, Instruction5, Instruction6, Instruction7 ); } );
    thread t12( [&](){ transfer( Instruction3, Instruction4, Instruction5, Instruction6, Instruction7 ); } );
    */
    
    
    t1.join();
    t2.join();
    t3.join();
    /*
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    */
    
    return 0;
    
}












