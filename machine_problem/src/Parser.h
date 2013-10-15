//
//  Parser.h
//  pipeline_sim
//
//  Created by Xin Zhang on 10/6/13.
//  Copyright (c) 2013 Xin Zhang. All rights reserved.
//

#include <string>
#include <vector>

using namespace boost;
using namespace std;


int stalls2 = 0;

string Parser(string inst, string inst_pre, string inst_pre2){
    
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










