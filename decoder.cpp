#include "EmulatorPDP11.h"
#include "decoder.h"
#include <cstdint>
#define RANGES

uint16_t ranges_[RANGES]={0,        07,         0100,       0200,       0210,       0230,
                      0240,     0300,       0400,       04000,      05000,      06400,
                      06500,    07000,      010000,     070000,     075000,     077000,
                      0100000,  0104000,    0105000,    0106400,    0110000,    0170000};

std::string decode_illegal(uint16_t* &pc){
//TODO some fancy handling of this exception
    pc++;
    return std::string("Illegal opcode\n");
}
std::string decode_zero_op(uint16_t* &pc){
    std::string opcode("ZeroOperandCode");
    return opcode;
}
std::string decode_traps(uint16_t* &pc){
    std::string opcode("TrapOperandCode");
    return opcode;
}
std::string decode_half_op(uint16_t* &pc){
    std::string opcode("HalfOperandCode R");
    std::string reg=std::to_string((*pc)&(07));
    return opcode+reg;
}
std::string decode_one_op(uint16_t* &pc){
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
std::string decode_oneNhalf_op(uint16_t* &pc){
    pc++;
    return std::string("1");
}





std::string decode_mark(uint16_t* &pc){
    pc++;
    return std::string("1");
}

std::string decode_two_op(uint16_t* &pc){
    pc++;
    return std::string("1");
}



std::string (*decoders[RANGES])(uint16_t* &pc)={decode_traps,     decode_illegal,     decode_one_op,  decode_half_op,     decode_illegal,     decode_half_op,
                          decode_zero_op,   decode_one_op,      decode_zero_op, decode_oneNhalf_op, decode_one_op,      decode_mark,
                          decode_one_op,    decode_illegal,     decode_two_op,  decode_oneNhalf_op, decode_illegal,     decode_oneNhalf_op,
                          decode_zero_op,   decode_traps,       decode_one_op,  decode_illegal,     decode_two_op,      decode_illegal};

std::string decode(uint16_t* &pc){
    int i = RANGES-1;
    while (ranges_[i] > *pc){
        i--;
    }
    return (*decoders[i])(pc);
}
