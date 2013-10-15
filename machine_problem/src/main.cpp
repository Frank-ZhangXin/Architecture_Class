//
//  UTSA CS Department
//  CS 5513 FALL 2013
//  Machine Problem
//  Pipeline simulator
//
//  Created by Xin Zhang on 10/4/13.
//  Copyright (c) 2013 Xin Zhang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <boost/regex.hpp>
#include "Operation.h"

using namespace std;
using namespace boost;

string Parser(string);
void Stall_check(string, string);
void output(int, int, int);


int main(int argc, const char * argv[])
{
    vector<string> inst_V;
    int ecpt_code = 0;
    string file_name = "5.in";
    string line;
    int cycle = 0;
    int loop = 0;
    
    
    ifstream in;
    in.open(file_name, ios::in);
    
    if(in.fail()){
        cout << "\n" << " >>>  Error  >>>  File read error.  >>>  File: " << file_name << "\n" << endl;
        exit(1);
    }
    
    while (getline(in, line)) {
        inst_V.push_back(line);
    }
    
    int inst_num = int(inst_V.size()); // Instruction quantity
    

    for (vector<string>::iterator i = inst_V.begin(); i != inst_V.end(); i++){
        
        cout << "\n" << *i << "\n" << endl;
        
        loop++;
        cycle = loop*5;
        if ((cycle + stalls) > 1000) {
            output(inst_num, cycle, loop);
            exit(1);
        }
        
        vector<string>::iterator j = i - 1;
        if (i != inst_V.begin()) {
            Stall_check(*i, *j);
        }
        
        
        if (Parser(*i) == "invalid") {
            cout << "\n" << " >>>  Error  >>>  Grammar error.  >>>  Instruction: " << *i << "\n" << endl;
        }
        
        ecpt_code = Operation(*i);
        
        switch (ecpt_code) {
            case 100000000:  // successfully complete one instruction
                break;
            case 100100100: // terminate execution
                cout << "\n" << " >>>  Notice  >>>  File execution complete.  >>>  File: " << file_name << "\n" << endl;
                output(inst_num, cycle, loop);
                exit(1);
                break;
            case 100000011: // length error
                break;
            case 100000001:  // operands error
                break;
            default:
                i += ecpt_code;
                break;
        }
        
        cout << "\n" << "\n" << "\n";
    }
    
    
    
    
    
    
    //cout << Operation(inst1) << " jumps" << endl;
    cout << "# of stalls is " << stalls << endl;
    
    output(inst_num, cycle, loop);
    
    
    return 0;
    
}


string Parser(string inst){
    // Instructions pattern
    regex reg_add("^ADD\\s*R[0-7]\\s*R[0-7]\\s*R[0-7]\\s*");
    regex reg_sub("^SUB\\s*R[0-7]\\s*R[0-7]\\s*R[0-7]\\s*");
    regex reg_mul("^MUL\\s*R[0-7]\\s*R[0-7]\\s*R[0-7]\\s*");
    regex reg_div("^DIV\\s*R[0-7]\\s*R[0-7]\\s*R[0-7]\\s*");
    regex reg_xor("^XOR\\s*R[0-7]\\s*R[0-7]\\s*R[0-7]\\s*");
    regex reg_and("^AND\\s*R[0-7]\\s*R[0-7]\\s*R[0-7]\\s*");
    regex reg_or("^OR\\s*R[0-7]\\s*R[0-7]\\s*R[0-7]\\s*");
    regex reg_addi("^ADDI\\s*R[0-7]\\s*R[0-7]\\s*([1-9][0-9]*|0)\\s*");
    regex reg_subi("^SUBI\\s*R[0-7]\\s*R[0-7]\\s*([1-9][0-9]*|0)\\s*");
    regex reg_mem("^(LD|ST)\\s*R[0-7]\\s*R[0-7]\\s*([1-9][0-9]*|0)\\s*");
    regex reg_brch("^(BEQZ|BNEQZ)\\s*R[0-7]\\s*([1-9][0-9]*|0)\\s*");
    regex reg_hlt("^HLT\\s*");
    regex reg_nop("^NOP\\s*");
    
    bool add_assrt = regex_match(inst, reg_add);
    bool sub_assrt = regex_match(inst, reg_sub);
    bool mul_assrt = regex_match(inst, reg_mul);
    bool div_assrt = regex_match(inst, reg_div);
    bool xor_assrt = regex_match(inst, reg_xor);
    bool and_assrt = regex_match(inst, reg_and);
    bool or_assrt = regex_match(inst, reg_or);
    bool addi_assrt = regex_match(inst, reg_addi);
    bool subi_assrt = regex_match(inst, reg_subi);
    bool mem_assrt = regex_match(inst, reg_mem);
    bool brch_assrt = regex_match(inst, reg_brch);
    bool hlt_assrt = regex_match(inst, reg_hlt);
    bool nop_assrt = regex_match(inst, reg_nop);
    
    
    if (add_assrt == true) return "add";
    else if (sub_assrt == true) return "sub";
    else if (mul_assrt == true) return "mul";
    else if (div_assrt == true) return "div";
    else if (xor_assrt == true) return "xor";
    else if (and_assrt == true) return "and";
    else if (or_assrt == true) return "or";
    else if (addi_assrt == true) return "addi";
    else if (subi_assrt == true) return "subi";
    else if (mem_assrt == true) return "mem";
    else if (brch_assrt == true) return "brch";
    else if (hlt_assrt == true) return "hlt";
    else if (nop_assrt == true) return "nop";
    else return "invalid";
}

void Stall_check(string a, string b){
    regex space("\\s");
    vector<string> a_v;
    vector<string> b_v;
    string op1;
    string op2;
    string op3;
    
    
    sregex_token_iterator it(a.begin(), a.end(), space, -1);
    sregex_token_iterator end;
    while (it != end) {
        a_v.push_back(*it++);
    }
    sregex_token_iterator it2(b.begin(), b.end(), space, -1);
    while (it2 != end) {
        b_v.push_back(*it2++);
    }
    
    op1 = a_v.back();
    if (op1 != "HLT") {
        a_v.pop_back();
        op2 = a_v.back();
        
        
        b_v.pop_back();
        b_v.pop_back();
        op3 = b_v.back();
        
        
        cout << "op1 " << op1 << " op2 " << op2 << " op3 " << op3 << endl;
        
        
        if ((op3 == op1) || (op3 == op2) ){
            stalls+=3;
        }

    }
}

void output(int a, int b, int c){
    ofstream ofs;
    ofs.open("5.out", ofstream::out);
    
    ofs << "[total instructions fetched]: " << a << "\n";
    ofs << "[total instructions finished]: " << c << "\n";
    ofs << "[total cycles]: " << b << "\n";
    ofs << "[total stall cycles]: " << stalls << "\n";
    ofs << "[R1]: " << Reg[1] << "\n";
    ofs << "[R2]: " << Reg[2] << "\n";
    ofs << "[R3]: " << Reg[3] << "\n";
    ofs << "[R4]: " << Reg[4] << "\n";
    ofs << "[R5]: " << Reg[5] << "\n";
    ofs << "[R6]: " << Reg[6] << "\n";
    ofs << "[R7]: " << Reg[7] << "\n";
    ofs << "==================================" << "\n";
    ofs << "Name: Xin Zhang     BannerID: @01371443" << "\n";
    
}



















