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

using namespace std;

mutex t_lock;



string stg_IF(){
    //lock_guard<mutex> lk(t_lock);
    string str = "This is IF stage.";
    return str;
}

string stg_ID(){
    //lock_guard<mutex> lk(t_lock);
    string str = "This is ID stage.";
    return str;
}

void inst(){
    lock_guard<mutex> lk(t_lock);
    cout << stg_IF() << endl;
    cout << stg_ID() << endl;
    
}


int main(int argc, const char * argv[])
{
    //thread thrd_1(inst);
    //thread thrd_2(inst);
    //thread thrd_3(inst);
    //thread thrd_4(inst);

    
    //thrd_1.join();
    //thrd_2.join();
    //thrd_3.join();
    //thrd_4.join();
    
    int i = 0;
    while (true) {
        thread n(inst);
        n.join();
        i++;
        if (i == 10) {
            break;
        }
    }
    
    return 0;
    
}

