
#include <cstdint>
#include <string>
#include <sstream>
#include <unordered_map>
#include "EmulatorPDP11.h"
#include "decoder.h"
#include "operations.h"
#define RANGES 15

#pragma GCC diagnostic ignored "-Wunused-parameter"
char* mode_temp[64]={
    "R0",       "R1",       "R2",       "R3",
    "R4",       "R5",       "SP",       "PC",
    "[R0]",     "[R1]",     "[R2]",     "[R3]",
    "[R4]",     "[R5]",     "[SP]",     "[PC]",
    "[R0++]",   "[R1++]",   "[R2++]",   "[R3++]",
    "[R4++]",   "[R5++]",   "[SP++]",   "",
    "@[R0++]",  "@[R1++]",  "@[R2++]",  "@[R3++]",
    "@[R4++]",  "@[R5++]",  "@[R6++]",  "@",
    "[--R0]",   "[--R1]",   "[--R2]",   "[--R3]",
    "[--R4]",   "[--R5]",   "[--R6]",   "[--R]",
    "@[--R0]",  "@[--R1]",  "@[--R2]",  "@[--R3]",
    "@[--R4]",  "@[--R5]",  "@[--R6]",  "@[--R]",
    "R0[0x",    "R1[0x",    "R2[0x",    "R3[0x",
    "R4[0x",    "R5[0x",    "SP[0x",    "",
    "@R0[0x",   "@R1[0x",   "@R2[0x",   "@R3[0x",
    "@R4[0x",   "@R5[0x",   "@SP[0x",   "@"
};
std::string EmulatorPDP11::decode_zero_op(void** a, void** b){
    return std::string();
}
std::string EmulatorPDP11::decode_traps(void** a, void** b){
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    *(u_int16_t*)b = instr&(0777);
    std::ostringstream opcode;
    opcode << " 0" << std::oct << *(u_int16_t*)b;
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_half_op(void** a, void** b){
    std::ostringstream opcode;
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    opcode <<" "<<mode_temp[instr&(07)];
    *a = &regs_[instr&(07)];
    pc_+=2;
    return opcode.str();
}
//TODO handle SP & PC reg modes
std::string EmulatorPDP11::decode_one_op(void** a, void** b){
    *b = NULL;
    std::ostringstream opcode;
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    pc_ += 2;
    opcode << " " << mode_temp[instr&(077)];
    bool is_byte_instr = instr&0100000;
    u_int16_t *reg = &regs_[instr&(07)];
    switch((instr&(070))>>3){
#define ARG a
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
}
std::string EmulatorPDP11::decode_oNh_op(void** a, void** b){
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    pc_ += 2;
    std::ostringstream opcode;
    bool is_byte_instr = instr&0100000;
    u_int16_t *reg = &regs_[instr&(07)];
    *a = &regs_[(instr&(0700))>>6];
    opcode <<" "<<mode_temp[(instr&(0700))>>6]<<" "<<mode_temp[instr&(077)];
    switch((instr&(070))>>3){
#define ARG b
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
}
std::string EmulatorPDP11::decode_one_pl(void** a, void** b){
    *b = NULL;
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    *(u_int16_t*)a = instr&(077);
    std::ostringstream opcode;
    opcode << " 0" << std::oct << *(u_int16_t*)a;
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_sob(void** a, void** b){      //2Lesh: b is pointer to u_int16_t. It is nn. You need *b for jump! It's not me, it's spec.
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    *(u_int16_t*)b = instr&(077);
    std::ostringstream opcode;
    opcode << " " << mode_temp[(instr&(0700))>>6]
           << " 0" << std::oct << *(u_int16_t*)b;
//Achtung!!!
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_xor(void** a, void** b){
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    pc_ += 2;
    std::ostringstream opcode;
    bool is_byte_instr = instr&0100000;
    u_int16_t *reg = &regs_[instr&(07)];
    *b = &regs_[(instr&(0700))>>6];
    opcode <<" "<<mode_temp[instr&(077)];
    switch((instr&(070))>>3){
#define ARG a
#include "modes_selector.inc"
#undef ARG
    }
    opcode<<" "<<mode_temp[(instr&(0700))>>6];
}
std::string EmulatorPDP11::decode_branch(void** a, void** b){
    *b = NULL;
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    *(u_int16_t*)a = instr&(0xFF);
    std::ostringstream opcode;
    opcode << " 0x" << std::hex << *(u_int16_t*)a;
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_two_op_no_check(void** a, void** b){
    std::ostringstream opcode;
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    pc_ += 2;
    opcode << " " << mode_temp[instr&(077)];
    bool is_byte_instr = instr&0100000;
    u_int16_t *reg = &regs_[instr&(07)];
    switch((instr&(070))>>3){
#define ARG a
#include "modes_selector.inc"
#undef ARG
    }
    opcode << " " << mode_temp[(instr&(07700))>>6];
    reg = &regs_[(instr&(0700))>>6];
    switch((instr&(07000))>>9){
#define ARG b
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
}
//legacy. 2Lesh: check ROM at callback
std::string EmulatorPDP11::decode_two_op(void** a, void** b){
    std::ostringstream opcode;
    u_int16_t instr = *(u_int16_t*)(mem_ + pc_);
    pc_ += 2;
    opcode << " " << mode_temp[instr&(077)];
    bool is_byte_instr = instr&0100000;
    u_int16_t *reg = &regs_[instr&(07)];
    switch((instr&(070))>>3){
#define ARG a
#include "modes_selector.inc"
#undef ARG
    }
    opcode << " " << mode_temp[(instr&(07700))>>6];
    reg = &regs_[instr&(0700)];
    switch((instr&(07000))>>9){
#define ARG b
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
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
    pc_++;
    std::string string_arg = (this->*instr.decoder)(&arg_a, &arg_b);



    (this->*instr.callback)(arg_a,arg_b);

    return std::string(instr.instr) + string_arg;
}
