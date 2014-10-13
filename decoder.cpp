
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

//DISCUSS? decode_zero_op -> NULL
instr_t tab[]={
    {0000000,   "halt", decode_zero_op, op_halt},
    {0000001,   "wait", decode_zero_op, op_wait},
    {0000002,   "rti",  decode_zero_op, op_rti},
    {0000003,   "bpt",  decode_zero_op, op_bpt},
    {0000004,   "iot",  decode_zero_op, op_iot},
    {0000005,   "reset",decode_zero_op, op_reset},
    {0000006,   "rtt",  decode_zero_op, op_rtt},
    {0000100,   "jmp",  decode_one_op,  op_jmp},
    {0000200,   "rts",  decode_half_op, op_rts},
    {0000230,   "spl",  decode_half_op, op_spl},
    {0000240,   "nop",  decode_zero_op, op_nop},
    {0000241,   "clc",  decode_zero_op, op_clc},
    {0000242,   "clv",  decode_zero_op, op_clv},
    {0000244,   "clz",  decode_zero_op, op_clz},
    {0000250,   "cln",  decode_zero_op, op_cln},
    {0000257,   "ccc",  decode_zero_op, op_ccc},
    {0000261,   "sec",  decode_zero_op, op_sec},
    {0000262,   "sev",  decode_zero_op, op_sev},
    {0000264,   "sez",  decode_zero_op, op_sez},
    {0000270,   "sen",  decode_zero_op, op_sen},
    {0000277,   "scc",  decode_zero_op, op_scc},
    {0000300,   "swab", decode_one_op,  op_swab},
    {0x0100,    "br",   decode_branch,  op_br},
    {0x0200,    "bne",  decode_branch,  op_bne},
    {0x0300,    "beq",  decode_branch,  op_beq},
    {0x0400,    "bge",  decode_branch,  op_bge},
    {0x0500,    "blt",  decode_branch,  op_blt},
    {0x0600,    "bgt",  decode_branch,  op_bgt},
    {0x0700,    "ble",  decode_branch,  op_ble},
    {0004000,   "jsr",  decode_oNh_op,  op_jsr},
    {0005000,   "clr",  decode_one_op,  op_clr},
    {0005100,   "com",  decode_one_op,  op_com},
    {0005200,   "inc",  decode_one_op,  op_inc},
    {0005300,   "dec",  decode_one_op,  op_dec},
    {0005400,   "neg",  decode_one_op,  op_neg},
    {0005500,   "adc",  decode_one_op,  op_adc},
    {0005600,   "sbc",  decode_one_op,  op_sbc},
    {0005700,   "tst",  decode_one_op,  op_tst},
    {0006000,   "ror",  decode_one_op,  op_ror},
    {0006100,   "rol",  decode_one_op,  op_rol},
    {0006200,   "asr",  decode_one_op,  op_asr},
    {0006300,   "asl",  decode_one_op,  op_asl},
    {0006400,   "mark", decode_one_pl,  op_mark},
    {0006500,   "mfpi", decode_one_pl,  op_mfpi},
    {0006600,   "mtpi", decode_one_pl,  op_mtpi},
    {0006700,   "sxt",  decode_one_op,  op_sxt},
    {0010000,   "mov",  decode_two_op,  op_mov},
    {0020000,   "cmp",  decode_two_op,  op_cmp},
    {0030000,   "bit",  decode_two_op,  op_bit},
    {0040000,   "bic",  decode_two_op,  op_bic},
    {0050000,   "bis",  decode_two_op,  op_bis},
    {0060000,   "add",  decode_two_op,  op_add},
    {0070000,   "mul",  decode_oNh_op,  op_mul},
    {0071000,   "div",  decode_oNh_op,  op_div},
    {0072000,   "ash",  decode_oNh_op,  op_ash},
    {0073000,   "ashc", decode_oNh_op,  op_ashc},
    {0074000,   "xor",  decode_xor,     op_xor},
    {0077000,   "sob",  decode_sob,     op_sob},    //077Rnn R - register nn - uint6
    {0x8000,    "bpl",  decode_branch,  op_bpl},
    {0x8100,    "bmi",  decode_branch,  op_bmi},
    {0x8200,    "bhi",  decode_branch,  op_bhi},
    {0x8300,    "blos", decode_branch,  op_blos},
    {0x8400,    "bvc",  decode_branch,  op_bvc},
    {0x8500,    "bvs",  decode_branch,  op_bvs},
    {0x8600,    "bcc",  decode_branch,  op_bcc},
    {0x8700,    "bcs",  decode_branch,  op_bcs},
    {0x8800,    "emt",  decode_traps,   op_emt},
    {0x8900,    "sys",  decode_traps,   op_sys},
    {0105000,   "clrb", decode_one_op,  op_clrb},
    {0105100,   "comb", decode_one_op,  op_comb},
    {0105200,   "incb", decode_one_op,  op_incb},
    {0105300,   "decb", decode_one_op,  op_decb},
    {0105400,   "negb", decode_one_op,  op_negb},
    {0105500,   "adcb", decode_one_op,  op_adcb},
    {0105600,   "sbcb", decode_one_op,  op_sbcb},
    {0105700,   "tstb", decode_one_op,  op_tstb},
    {0106000,   "rorb", decode_one_op,  op_rorb},
    {0106100,   "rolb", decode_one_op,  op_rolb},
    {0106200,   "asrb", decode_one_op,  op_asrb},
    {0106300,   "aslb", decode_one_op,  op_aslb},
    //{0106400,   "mtps", decode_one_op,  op_mtps},
    //{0106500,   "mfpd", decode_one_op,  op_mfpd},
    //{0106600,   "mtpd", decode_one_op,  op_mtpd},
    //{0106700,   "mfps", decode_one_op,  op_mfpd},
    {0110000,   "movb", decode_two_op,  op_movb},
    {0120000,   "cmpb", decode_two_op,  op_cmpb},
    {0130000,   "bitb", decode_two_op,  op_bitb},
    {0140000,   "bicb", decode_two_op,  op_bicb},
    {0150000,   "bisb", decode_two_op,  op_bisb},
    {0160000,   "sub",  decode_two_op,  op_sub}
};//86 lines

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
