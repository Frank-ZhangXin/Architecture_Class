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
#include <queue>
#include <stack>


using namespace std;

struct bank_account
{
    explicit bank_account(string name, string title)
    {
        sName = name;
        mTitle = title;
    }
    
    string sName;
    string mTitle;
    mutex mMutex;
};

void transfer( bank_account &from, bank_account &to)
{
    // don't actually take the locks yet
    unique_lock<mutex> lock1( from.mMutex, defer_lock );
    unique_lock<mutex> lock2( to.mMutex, defer_lock );
    
    // lock both unique_locks without deadlock
    lock( lock1, lock2 );
    
    string title = from.mTitle;
    from.mTitle = to.mTitle;
    to.mTitle = title;
    
    // output log
    cout << from.sName << "'s stage is " << from.mTitle << endl;
    cout << to.sName << "'s stage is " << to.mTitle << endl;
    cout << "\n";
}

int main(int argc, const char * argv[])
{
    bank_account Instruction1( "Instruction_1", "ID" );
    bank_account Instruction2( "Instruction_2", "IF" );
    
    cout << Instruction1.sName << "'s stage is " << Instruction1.mTitle << endl;
    cout << Instruction2.sName << "'s stage is " << Instruction2.mTitle << endl;
    cout << "\n";
    
    thread t1( [&](){ transfer( Instruction1, Instruction2); transfer( Instruction1, Instruction2); } );
    //thread t2( [&](){ transfer( Account1, Account2); } );
    
    t1.join();
    //t2.join();
    
    return 0;
    
}

