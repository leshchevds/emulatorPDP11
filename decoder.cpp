
#include <cstdint>
#include <unordered_map>
#include "EmulatorPDP11.h"
#include "decoder.h"
#include "operations.h"
#define RANGES 15


std::unordered_map<u_int16_t,instr_t> optable_;

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


std::string decode_zero_op(u_int16_t* &pc){
    std::string opcode("ZeroOperandCode");
    return opcode;
}
std::string decode_traps(u_int16_t* &pc){
    std::string opcode("TrapOperandCode");
    return opcode;
}
std::string decode_half_op(u_int16_t* &pc){
    std::string opcode("HalfOperandCode R");
    std::string reg=std::to_string((*pc)&(07));
    return opcode+reg;
}
std::string decode_one_op(u_int16_t* &pc){
    std::string opcode("OneOperandCode ");
    std::string operand("R");
    operand = operand + std::to_string((*pc)&(07));
    switch(((*pc)&(060))>>4){
    case 0:
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

    if((*pc)&(010)){
        operand="@"+operand;
    }
    return opcode+operand;
}
std::string decode_oNh_op(u_int16_t* &pc){
    pc++;
    return std::string("1");
}
std::string decode_one_pl(u_int16_t* &pc){
    pc++;
    return std::string("1");
}
std::string decode_sob(u_int16_t* &pc){
    pc++;
    return std::string("1");
}
std::string decode_xor(u_int16_t* &pc){
    pc++;
    return std::string("1");
}
std::string decode_mark(u_int16_t* &pc){
    pc++;
    return std::string("1");
}
std::string decode_branch(u_int16_t* &pc){
    pc++;
    return std::string("1");
}
std::string decode_two_op(u_int16_t* &pc){
    pc++;
    return std::string("1");
}

/*void init(){
    for(int i=0; i<86;i++){
        optable_.
    }
}*/

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

std::string EmulatorPDP11::Decode(u_int16_t* &pc){
    int i = RANGES/2;
    int left = 0;
    int right = RANGES-1;
    while (true){
        if(ranges_[i]>*pc){
            right = i;
            i = (right+left)/2;
            continue;
        }
        if(ranges_[i+1]<=*pc){
            left = i;
            i = (right+left)/2;
            continue;
        }
        break;
    }
    u_int16_t masked_pc = (*pc)&(masks_[i]);
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
    pc++;
    return std::string(instr.instr);
}
