//
//  Operation.h
//  pipeline_sim
//
//  Created by Xin Zhang on 10/7/13.
//  Copyright (c) 2013 Xin Zhang. All rights reserved.
//

#include <string>

using namespace std;
using namespace boost;

/*--------*/
// Stalls
/*--------*/
int stalls;

/*---------*/
// Register
/*---------*/
vector<int> Reg;



/*------------*/
// Arithemetics
/*------------*/
class Arith{
    
public:
    int ADD(int, int);
    int SUB(int, int);
    int MUL(int, int);
    int DIV(int, int);
    int XOR(int, int);
    int AND(int, int);
    int OR(int, int);
    int ADDI(int, int);
    int SUBI(int, int);
    int ADDR(int, int);
};




/*-------*/
// Memory
/*-------*/
struct Mem{
    explicit Mem(int dmem, int imem){
        dMem.resize(dmem);
        iMem.resize(imem);
    }
    vector<int> dMem;
    vector<int> iMem;
    
};


/*----------*/
// Operation
/*----------*/
int Operation(string i1){
    
    string type1;
    string tran_str;
    string reg_str;
    string inst_type;
    int reg_num;
    int rt;
    int rs;
    int rs_adr; // rs address
    int rd = 0;
    stringstream ss;
    vector<string> instV;
    
    // Memory initial for 256 Byte each.
    Mem Memo(257, 257);
    
    // Register initial
    Reg.resize(8);
    
    
    // Filter useless charactors
    ss << i1;
    while (ss >> tran_str) {
        instV.push_back(tran_str);
    }
    

    
    
    // ALU LD ST instruction
    if (instV.size() == 4) {
        reg_str = instV.back();
        
        // immediate num or register
        if (reg_str.front() != 'R') {
            rt = stoi(reg_str);
        }
        else{
            reg_str.erase(reg_str.begin());
            reg_num = stoi(reg_str);
            rt = Reg[reg_num];
        }
        instV.pop_back();
        
        // rs & rs address
        reg_str = instV.back();
        reg_str.erase(reg_str.begin());
        reg_num = stoi(reg_str);
        rs = Reg[reg_num];
        rs_adr = reg_num;
        instV.pop_back();
        
        // rd
        reg_str = instV.back();
        reg_str.erase(reg_str.begin());
        rd = stoi(reg_str);
        instV.pop_back();
        
        // op
        inst_type = instV.back();
        instV.pop_back();
        
    }
    
    // Branch instruction
    else if (instV.size() == 3){
        // immediate offset
        reg_str = instV.back();
        regex num_reg("^[\\d\\-\\.]+$");
        if (!regex_match(reg_str, num_reg)) {
            cout << "\n" << " >>>  Error  >>>  Instruction operands error.  >>>  Instruction: " << i1 << "\n" << endl;
            return 100000001;
        }
        rt = stoi(instV.back());
        instV.pop_back();
        
        // rs address
        reg_str = instV.back();
        reg_str.erase(reg_str.begin());
        reg_num = stoi(reg_str);
        rs = Reg[reg_num];
        rs_adr = reg_num;
        instV.pop_back();

        // op
        inst_type = instV.back();
        instV.pop_back();
    }
    
    // Void instruction
    else if(instV.size() == 1){
        // op
        inst_type = instV.back();
        instV.pop_back();
    }
    // Error with instruction length.
    else {
        cout << "\n" << " >>>  Error  >>>  Instruction length error. >>>  Instruction: " << i1 << "\n" << endl;
        return 100000011;
    }
    
    Arith Calcu;
    
    // Void op
    if (inst_type == "NOP") {
        stalls++;
    }
    
    // ALU ops
    else if (inst_type == "ADD"){
        Reg[rd] = Calcu.ADD(rs, rt);
        
    }
    else if (inst_type == "SUB"){
        Reg[rd] = Calcu.SUB(rs, rt);
        
    }
    else if (inst_type == "MUL"){
        Reg[rd] = Calcu.MUL(rs, rt);
    }
    else if (inst_type == "DIV"){
        Reg[rd] = Calcu.DIV(rs, rt);
    }
    else if (inst_type == "XOR"){
        Reg[rd] = Calcu.XOR(rs, rt);
    }
    else if (inst_type == "AND"){
        Reg[rd] = Calcu.AND(rs, rt);
    }
    else if (inst_type == "OR"){
        Reg[rd] = Calcu.OR(rs, rt);
    }
    else if (inst_type == "ADDI"){
        Reg[rd] = Calcu.ADDI(rs, rt);
        
    }
    else if (inst_type == "SUBI"){
        Reg[rd] = Calcu.SUBI(rs, rt);
        
    }
    else if (inst_type == "LD"){
        Reg[rd] = Memo.dMem[Calcu.ADDR(rs_adr, rt)];
    }
    else if (inst_type == "ST"){
        Memo.dMem[Calcu.ADDR(rs_adr, rt)] = Reg[rd];
    }
    
    // Branch ops
    else if (inst_type == "BEQZ"){
        
        cout << "rs is " << rs << endl;
        cout << "rs address is" << rs_adr << endl;
        cout << "jump " << rt << " steps" << "\n" << endl;
        
        if (rs == 0) {
            return rt;
        }
        else stalls++;
    }
    else if (inst_type == "BNEQZ"){
        if (rs != 0) {
            cout << "\n" << "JUMP! " << rt << " steps" << "\n" << endl;
            return rt;
        }
        else stalls++;
    }
    
    // Terminate ops
    else if (inst_type == "HLT"){
        return 100100100;
    }
    else cout << "\n" << " >>>  Error  >>>  Instruction type error.  >>>  Instruction: " << i1 << "\n" << endl;
    
    cout << "Result of instruction: " << Reg[rd] << "\n" << endl;
    
    return 100000000;
}







// Arith functions
int Arith::ADD(int a, int b){
    return a+b;
}

int Arith::SUB(int a, int b){
    return a-b;
}

int Arith::MUL(int a, int b){
    return a*b;
}

int Arith::DIV(int a, int b){
    return a/b;
}

int Arith::XOR(int a, int b){
    return a^b;
}

int Arith::OR(int a, int b){
    return a|b;
}

int Arith::AND(int a, int b){
    return a&b;
}

int Arith::ADDI(int a, int b){
    return a+b;
}

int Arith::SUBI(int a, int b){
    return a-b;
}

int Arith::ADDR(int a, int b){
    return (a * 32 + b) / 32;
}


