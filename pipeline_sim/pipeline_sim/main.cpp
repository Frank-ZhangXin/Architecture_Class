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
    stg_stk->push("IF");
    stg_stk->push("ID");
    stg_stk->push("EX");
    stg_stk->push("MEM");
    stg_stk->push("WB");
}


void transfer( inst &i1, inst &i2, inst &i3, inst &i4, inst &i5)
{
    // don't actually take the locks yet
    unique_lock<mutex> lock1( i1.mMutex, defer_lock );
    unique_lock<mutex> lock2( i2.mMutex, defer_lock );
    unique_lock<mutex> lock3( i3.mMutex, defer_lock );
    unique_lock<mutex> lock4( i4.mMutex, defer_lock );
    unique_lock<mutex> lock5( i5.mMutex, defer_lock );
    
    // lock both unique_locks without deadlock
    lock( lock1, lock2, lock3, lock4, lock5 );
    
    stack<string> *ptr = &stg_stk;
    i1.iStage = ptr->top();
    ptr->pop();
    i2.iStage = ptr->top();
    ptr->pop();
    i3.iStage = ptr->top();
    ptr->pop();
    i4.iStage = ptr->top();
    ptr->pop();
    i5.iStage = ptr->top();
    ptr->pop();
    
    // output log
    cout << i1.iName << "'s stage is " << i1.iStage << endl;
    cout << i2.iName << "'s stage is " << i2.iStage << endl;
    cout << i3.iName << "'s stage is " << i3.iStage << endl;
    cout << i4.iName << "'s stage is " << i4.iStage << endl;
    cout << i5.iName << "'s stage is " << i5.iStage << endl;
    cout << "\n";
}

int main(int argc, const char * argv[])
{
    inst Instruction1( "Instruction_1", "$" );
    inst Instruction2( "Instruction_2", "$" );
    inst Instruction3( "Instruction_3", "$" );
    inst Instruction4( "Instruction_4", "$" );
    inst Instruction5( "Instruction_5", "$" );
    
    // Initialize stack that is storing stages.
    stg_init(&stg_stk);
    
    
    thread t1( [&](){ transfer( Instruction1, Instruction2, Instruction3, Instruction4, Instruction5 ); } );
    //thread t2( [&](){ transfer( Instruction1, Instruction2); } );
    
    t1.join();
    //t2.join();
    
    return 0;
    
}












