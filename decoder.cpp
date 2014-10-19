
#include <cstdint>
#include <unordered_map>
#include "EmulatorPDP11.h"
#include "decoder.h"
#include "operations.h"
#define RANGES 15

#pragma GCC diagnostic ignored "-Wunused-parameter"


char* mode_temp[64]={
    "R0",   "[R0]", "[R0++]",   "@[R0++]",   "[--R0]",    "@[--R0]",   "[[PC]+R0]", "@[[PC]+R0]",
    "R1",   "[R1]", "[R1++]",   "@[R1++]",   "[--R1]",    "@[--R1]",   "[[PC]+R1]", "@[[PC]+R1]",
    "R2",   "[R2]", "[R2++]",   "@[R2++]",   "[--R2]",    "@[--R2]",   "[[PC]+R2]", "@[[PC]+R2]",
    "R3",   "[R3]", "[R3++]",   "@[R3++]",   "[--R3]",    "@[--R3]",   "[[PC]+R3]", "@[[PC]+R3]",
    "R4",   "[R4]", "[R4++]",   "@[R4++]",   "[--R4]",    "@[--R4]",   "[[PC]+R4]", "@[[PC]+R4]",
    "R5",   "[R5]", "[R5++]",   "@[R5++]",   "[--R5]",    "@[--R5]",   "[[PC]+R5]", "@[[PC]+R5]",
    "SP",   "[SP]", "[SP++]",   "@[R6++]",   "[--R6]",    "@[--R6]",   "[[PC]+R6]", "@[[PC]+R6]",
    "PC",   "[PC]", "[R++]",    "@[R++]",   "[--R]",    "@[--R]",       "[PC++]",    "@[PC++]",
};
//FIXME handle odd ref on words
inline u_int16_t deref_PDP11(char* mem, u_int16_t ref){
    return *(u_int16_t*)(mem+ref);
}
inline u_int8_t deref_PDP11b(char* mem, u_int16_t ref){
    return *(u_int8_t*)(mem+ref);
}

std::string EmulatorPDP11::decode_zero_op(void** a, void** b){
    return std::string();
}
std::string EmulatorPDP11::decode_traps(void** a, void** b){
    std::string opcode("TrapOperandCode");
    return opcode;
}
std::string EmulatorPDP11::decode_half_op(void** a, void** b){
    std::string opcode("R");
    uint16_t *reg = &regs_[pc_&(07)];
    *a = (void*)reg;
    return opcode+std::to_string(*reg);
}
std::string EmulatorPDP11::decode_one_op(void** a, void** b){
    *b = NULL;
    std::string operand("R");
    uint16_t *reg = &regs_[pc_&(07)];
    operand = operand + std::to_string(*reg);
    switch((pc_&(060))>>4){
    case 0:
        *a = (void*)reg;
        break;
    case 1:
        operand+="++";
        break;
    case 2:
        operand = std::string("--")+operand;
        break;
    case 3:
        operand = std::string("[[PC] + ")+operand+"]";
        break;
    }

    if(pc_&(010)){
        operand="@"+operand;
    }
    return operand;
}
std::string EmulatorPDP11::decode_oNh_op(void** a, void** b){
    pc_++;
    return std::string("1");
}
std::string EmulatorPDP11::decode_one_pl(void** a, void** b){
    pc_++;
    return std::string("1");
}
std::string EmulatorPDP11::decode_sob(void** a, void** b){
    pc_++;
    return std::string("1");
}
std::string EmulatorPDP11::decode_xor(void** a, void** b){
    pc_++;
    return std::string("1");
}
std::string EmulatorPDP11::decode_mark(void** a, void** b){
    pc_++;
    return std::string("1");
}
std::string EmulatorPDP11::decode_branch(void** a, void** b){
    pc_++;
    return std::string("1");
}
std::string EmulatorPDP11::decode_two_op_no_check(void** a, void** b){
    pc_++;
    return std::string("1");
}
std::string EmulatorPDP11::decode_two_op(void** a, void** b){
    pc_++;
    return std::string("1");
}


u_int16_t ranges_[]={
    0000000,    0000100,    0000200,   0000240,
    0000300,    0000400,    0004000,   0005000,
    0010000,    0070000,    0100000,   0104000,
    0104400,    0105000,    0110000,   0177777
};

u_int16_t masks_[]= {
    0177777,    0177700,    0177770,    0177777,
    0177770,    0xff00,     0177000,    0177700,
    0170000,    0177000,    0xff00,     0xff00,
    0xff00,     0177700,    0170000,    0177777
};

std::string EmulatorPDP11::step_and_list(){
    int i = RANGES/2;
    int left = 0;
    int right = RANGES-1;
    while (true){
        if(ranges_[i]>pc_){
            right = i;
            i = (right+left)/2;
            continue;
        }
        if(ranges_[i+1]<=pc_){
            left = i;
            i = (right+left)/2;
            continue;
        }
        break;
    }
    u_int16_t masked_pc = pc_&(masks_[i]);
    i = 46;
    left = 0;
    right = 86;
    while (true){
        if(tab[i].opcode>masked_pc){
            right = i;
            i = (right+left)/2;
            continue;
        }
        if(tab[i+1].opcode<=masked_pc){
            left = i;
            i = (right+left)/2;
            continue;
        }
        break;
    }
    instr_t instr = tab[i];
    void* arg_a,* arg_b;
    std::string string_arg = (this->*instr.decoder)(&arg_a, &arg_b);

    //TODO what comes first incrementing pc or calling callback function??
    pc_++;
    (this->*instr.callback)(arg_a,arg_b);

    return std::string(instr.instr) + string_arg;
}
