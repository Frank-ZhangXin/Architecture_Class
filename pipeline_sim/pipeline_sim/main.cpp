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

using namespace std;

string Reg = {"R1", "R2"};

string Stg = {"IF", "ID"};

void call(string str){
    cout << str << endl;
}

void t_i(){
    call("inst 1");
}

void t_i1(){
    call("inst 2");
}

int main(int argc, const char * argv[])
{
    string inst1 = &Reg[0];
    thread thrd_1(t_i);
    thrd_1.join();
    thread thrd_2(t_i1);
    thrd_2.join();
    
    return 0;
    
}

