
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
std::string EmulatorPDP11::decode_zero_op(void** null, void** nill){
    *null = NULL;
    *nill = NULL;
    pc_+=2;
    return std::string();
}
std::string EmulatorPDP11::decode_traps(void** dst, void** null){
    *null = NULL;
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    *(uint16_t*)dst = instr&(0777);
    std::ostringstream opcode;
    opcode << " 0" << std::oct << *(uint16_t*)dst;
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_half_op(void** dst, void** null){
    *null = NULL;
    std::ostringstream opcode;
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    opcode <<" "<<mode_temp[instr&(07)];
    *dst = &regs_[instr&(07)];
    pc_+=2;
    return opcode.str();
}
//TODO handle SP & PC reg modes
std::string EmulatorPDP11::decode_one_op(void** dst, void** null){
    *null = NULL;
    std::ostringstream opcode;
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    pc_ += 2;
    opcode << " " << mode_temp[instr&(077)];
    bool is_byte_instr = instr&0100000;
    uint16_t *reg = &regs_[instr&(07)];
    switch((instr&(070))>>3){
#define ARG dst
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
}
std::string EmulatorPDP11::decode_oNh_op(void** dst, void** src){
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    pc_ += 2;
    std::ostringstream opcode;
    bool is_byte_instr = instr&0100000;
    uint16_t *reg = &regs_[instr&(07)];
    *dst = &regs_[(instr&(0700))>>6];
    opcode <<" "<<mode_temp[(instr&(0700))>>6]<<" "<<mode_temp[instr&(077)];
    switch((instr&(070))>>3){
#define ARG src
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
}
std::string EmulatorPDP11::decode_one_pl(void** nn, void** null){
    *null = NULL;
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    *(uint16_t*)nn = instr&(077);
    std::ostringstream opcode;
    opcode << " 0" << std::oct << *(uint16_t*)nn;
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_sob(void** reg, void** nn){      //2Lesh: nn is pointer to uint16_t. It is nn. You need *nn for jump! It's not me, it's spec.
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    *(uint16_t*)nn = instr&(077);
    *(uint16_t**)reg = &regs_[(instr&(0700))>>6];
    std::ostringstream opcode;
    opcode << " " << mode_temp[(instr&(0700))>>6]
           << " 0" << std::oct << *(uint16_t*)nn;
//Achtung!!!
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_xor(void** dst, void** src){
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    pc_ += 2;
    std::ostringstream opcode;
    bool is_byte_instr = instr&0100000;
    uint16_t *reg = &regs_[instr&(07)];
    *src = &regs_[(instr&(0700))>>6];
    opcode <<" "<<mode_temp[instr&(077)];
    switch((instr&(070))>>3){
#define ARG dst
#include "modes_selector.inc"
#undef ARG
    }
    opcode<<" "<<mode_temp[(instr&(0700))>>6];
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_branch(void** dst, void** null){
    *null = NULL;
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    *(uint16_t*)dst = instr&(0xFF);
    std::ostringstream opcode;
    opcode << " 0x" << std::hex << *(uint16_t*)dst;
    pc_+=2;
    return opcode.str();
}
std::string EmulatorPDP11::decode_two_op_no_check(void** src, void** dst){
    std::ostringstream opcode;
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    pc_ += 2;
    opcode << " " << mode_temp[instr&(077)];
    bool is_byte_instr = instr&0100000;
    uint16_t *reg = &regs_[instr&(07)];
    switch((instr&(070))>>3){
#define ARG dst
#include "modes_selector.inc"
#undef ARG
    }
    opcode << " " << mode_temp[(instr&(07700))>>6];
    reg = &regs_[(instr&(0700))>>6];
    switch((instr&(07000))>>9){
#define ARG src
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
}
//legacy. 2Lesh: check ROM at callback
std::string EmulatorPDP11::decode_two_op(void** src, void** dst){
    std::ostringstream opcode;
    uint16_t instr = *(uint16_t*)(mem_ + pc_);
    pc_ += 2;
    opcode << " " << mode_temp[instr&(077)];
    bool is_byte_instr = instr&0100000;
    uint16_t *reg = &regs_[instr&(07)];
    switch((instr&(070))>>3){
#define ARG dst
#include "modes_selector.inc"
#undef ARG
    }
    opcode << " " << mode_temp[(instr&(07700))>>6];
    reg = &regs_[instr&(0700)];
    switch((instr&(07000))>>9){
#define ARG src
#include "modes_selector.inc"
#undef ARG
    }
    return opcode.str();
}


uint16_t ranges_[]={
    0000000,    0000100,    0000200,   0000240,
    0000300,    0000400,    0004000,   0005000,
    0010000,    0070000,    0100000,   0104000,
    0104400,    0105000,    0110000,   0177777
};

uint16_t masks_[]= {
    0177777,    0177700,    0177770,    0177777,
    0177770,    0xff00,     0177000,    0177700,
    0170000,    0177000,    0xff00,     0xff00,
    0xff00,     0177700,    0170000,    0177777
};

void EmulatorPDP11::step_and_list(bool single){
    int i = RANGES/2;
    int left = 0;
    int right = RANGES - 1;
    uint16_t opcode = *(uint16_t*)(mem_+pc_);
    if (opcode == 0177777) { pc_+=2; return; } //nononono David Blain.
    while (true){
        if (ranges_[i] > opcode) {
            right = i;
            i = (right+left)/2;
            continue;
        }
        if (ranges_[i+1] <= opcode) {
            left = i;
            i = (right+left)/2;
            continue;
        }
        break;
    }
    uint16_t masked_opcode = opcode&(masks_[i]);
    i = 46;
    left = 0;
    right = 86;
    while (true){
        if (tab[i].opcode>masked_opcode) {
            right = i;
            i = (right+left)/2;
            continue;
        }
        if (tab[i+1].opcode<=masked_opcode) {
            left = i;
            i = (right+left)/2;
            continue;
        }
        break;
    }
    instr_t instr = tab[i];
    void* arg_a,* arg_b;

    std::string string_arg = (this->*instr.decoder)(&arg_a, &arg_b);

    (this->*instr.callback)(arg_a,arg_b);

    if (single) {
        PushOperation((std::string(instr.instr) + string_arg).c_str());
        run_lock_.store(false);
    }
}
