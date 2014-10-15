#ifndef EMULATORPDP11_H
#define EMULATORPDP11_H

#include <stdint.h>
#include <string>
#include <functional>

class EmulatorPDP11;

typedef std::string (EmulatorPDP11::*d_func)(u_int16_t*);
typedef void (EmulatorPDP11::*e_func)(void* ,void*);

struct instr_t {
    u_int16_t opcode;
    char* instr;
    d_func f;
    e_func e;
    //std::string (EmulatorPDP11::*d_func)(u_int16_t*&);
    //void (EmulatorPDP11::*e_func)(void* ,void*);

};

class EmulatorPDP11 {
public:
    EmulatorPDP11();
    explicit EmulatorPDP11(const char* source, size_t count = 16*1024) ;
    ~EmulatorPDP11();

    const char* videomem();
    size_t WriteROM(const char* source, size_t count = 16*1024);

    u_int16_t reg(u_int8_t num) {
        if (num < 8) {
            return regs_[num];
        } else {
            throw;
        }
    }

    u_int16_t psw() {
        return psw_;
    }

    bool isRunning() {
        return running_;
    }

    void Run();
    void Stop();
    void Step();
    void Reset();


    std::string Decode(u_int16_t* pc); // could require up to 3 words allocated NOT CONST!!! DECODER CHANGING PC!!!

private:

    char mem_[64*1024];
    u_int16_t regs_[8];
    u_int16_t psw_; // processor status word
    bool running_; // TODO: delete it!
    u_int16_t& fp_ = regs_[5];
    u_int16_t& sp_ = regs_[6];
    u_int16_t& pc_ = regs_[7];

    std::string decode_zero_op(u_int16_t* pc);
    std::string decode_one_op(u_int16_t* pc);
    std::string decode_oNh_op(u_int16_t* pc);
    std::string decode_two_op(u_int16_t* pc);
    std::string decode_half_op(u_int16_t* pc);
    std::string decode_branch(u_int16_t* pc);
    std::string decode_traps(u_int16_t* pc);
    std::string decode_one_pl(u_int16_t* pc);
    std::string decode_sob(u_int16_t* pc);
    std::string decode_xor(u_int16_t* pc);
    std::string decode_mark(u_int16_t* pc);
    void op_halt(void* a, void* b);
    void op_wait(void* a, void* b);
    void op_rti(void* a, void*b);
    void op_bpt(void* a, void*b);
    void op_iot(void* a, void*b);
    void op_reset(void* a, void*b);
    void op_rtt(void* a, void*b);
    void op_jmp(void* a, void*b);
    void op_rts(void* a, void*b);
    void op_spl(void* a, void*b);
    void op_nop(void* a, void*b);
    void op_clc(void* a, void*b);
    void op_clv(void* a, void*b);
    void op_clz(void* a, void*b);
    void op_cln(void* a, void*b);
    void op_ccc(void* a, void*b);
    void op_sec(void* a, void*b);
    void op_sev(void* a, void*b);
    void op_sez(void* a, void*b);
    void op_sen(void* a, void*b);
    void op_scc(void* a, void*b);
    void op_swab(void* a, void*b);
    void op_br(void* a, void*b);
    void op_bne(void* a, void*b);
    void op_beq(void* a, void*b);
    void op_bge(void* a, void*b);
    void op_blt(void* a, void*b);
    void op_bgt(void* a, void*b);
    void op_ble(void* a, void*b);
    void op_jsr(void* a, void*b);
    void op_clr(void* a, void*b);
    void op_com(void* a, void*b);
    void op_inc(void* a, void*b);
    void op_dec(void* a, void*b);
    void op_neg(void* a, void*b);
    void op_adc(void* a, void*b);
    void op_sbc(void* a, void*b);
    void op_tst(void* a, void*b);
    void op_ror(void* a, void*b);
    void op_rol(void* a, void*b);
    void op_asr(void* a, void*b);
    void op_asl(void* a, void*b);
    void op_mark(void* a, void*b);
    void op_mfpi(void* a, void*b);
    void op_mtpi(void* a, void*b);
    void op_sxt(void* a, void*b);
    void op_mul(void* a, void*b);
    void op_div(void* a, void*b);
    void op_ash(void* a, void*b);
    void op_ashc(void* a, void*b);
    void op_xor(void* a, void*b);
    void op_sob(void* a, void*b);
    void op_mov(void* a, void*b);
    void op_cmp(void* a, void*b);
    void op_bit(void* a, void*b);
    void op_bic(void* a, void*b);
    void op_bis(void* a, void*b);
    void op_add(void* a, void*b);
    void op_movb(void* a, void*b);
    void op_cmpb(void* a, void*b);
    void op_bitb(void* a, void*b);
    void op_bicb(void* a, void*b);
    void op_bisb(void* a, void*b);
    void op_sub(void* a, void*b);
    void op_bpl(void* a, void*b);
    void op_bmi(void* a, void*b);
    void op_bhi(void* a, void*b);
    void op_blos(void* a, void*b);
    void op_bvc(void* a, void*b);
    void op_bvs(void* a, void*b);
    void op_bcc(void* a, void*b);
    void op_bcs(void* a, void*b);
    void op_emt(void* a, void*b);
    void op_sys(void* a, void*b);
    void op_clrb(void* a, void*b);
    void op_comb(void* a, void*b);
    void op_incb(void* a, void*b);
    void op_decb(void* a, void*b);
    void op_negb(void* a, void*b);
    void op_adcb(void* a, void*b);
    void op_sbcb(void* a, void*b);
    void op_tstb(void* a, void*b);
    void op_rorb(void* a, void*b);
    void op_rolb(void* a, void*b);
    void op_asrb(void* a, void*b);
    void op_aslb(void* a, void*b);


    //DISCUSS? decode_zero_op -> NULL

    instr_t tab[86] = {
        {0000000,   "halt", &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_halt},
        {0000001,   "wait", &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_wait},
        {0000002,   "rti",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_rti},
        {0000003,   "bpt",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_bpt},
        {0000004,   "iot",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_iot},
        {0000005,   "reset",&EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_reset},
        {0000006,   "rtt",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_rtt},
        {0000100,   "jmp",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_jmp},
        {0000200,   "rts",  &EmulatorPDP11::decode_half_op, &EmulatorPDP11::op_rts},
        {0000230,   "spl",  &EmulatorPDP11::decode_half_op, &EmulatorPDP11::op_spl},
        {0000240,   "nop",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_nop},
        {0000241,   "clc",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_clc},
        {0000242,   "clv",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_clv},
        {0000244,   "clz",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_clz},
        {0000250,   "cln",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_cln},
        {0000257,   "ccc",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_ccc},
        {0000261,   "sec",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sec},
        {0000262,   "sev",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sev},
        {0000264,   "sez",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sez},
        {0000270,   "sen",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sen},
        {0000277,   "scc",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_scc},
        {0000300,   "swab", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_swab},
        {0x0100,    "br",   &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_br},
        {0x0200,    "bne",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bne},
        {0x0300,    "beq",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_beq},
        {0x0400,    "bge",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bge},
        {0x0500,    "blt",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_blt},
        {0x0600,    "bgt",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bgt},
        {0x0700,    "ble",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_ble},
        {0004000,   "jsr",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_jsr},
        {0005000,   "clr",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_clr},
        {0005100,   "com",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_com},
        {0005200,   "inc",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_inc},
        {0005300,   "dec",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_dec},
        {0005400,   "neg",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_neg},
        {0005500,   "adc",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_adc},
        {0005600,   "sbc",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_sbc},
        {0005700,   "tst",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_tst},
        {0006000,   "ror",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_ror},
        {0006100,   "rol",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_rol},
        {0006200,   "asr",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_asr},
        {0006300,   "asl",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_asl},
        {0006400,   "mark", &EmulatorPDP11::decode_one_pl,  &EmulatorPDP11::op_mark},
        {0006500,   "mfpi", &EmulatorPDP11::decode_one_pl,  &EmulatorPDP11::op_mfpi},
        {0006600,   "mtpi", &EmulatorPDP11::decode_one_pl,  &EmulatorPDP11::op_mtpi},
        {0006700,   "sxt",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_sxt},
        {0010000,   "mov",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_mov},
        {0020000,   "cmp",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_cmp},
        {0030000,   "bit",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bit},
        {0040000,   "bic",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bic},
        {0050000,   "bis",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bis},
        {0060000,   "add",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_add},
        {0070000,   "mul",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_mul},
        {0071000,   "div",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_div},
        {0072000,   "ash",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_ash},
        {0073000,   "ashc", &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_ashc},
        {0074000,   "xor",  &EmulatorPDP11::decode_xor,     &EmulatorPDP11::op_xor},
        {0077000,   "sob",  &EmulatorPDP11::decode_sob,     &EmulatorPDP11::op_sob},    //077Rnn R - register nn - uint6
        {0x8000,    "bpl",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bpl},
        {0x8100,    "bmi",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bmi},
        {0x8200,    "bhi",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bhi},
        {0x8300,    "blos", &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_blos},
        {0x8400,    "bvc",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bvc},
        {0x8500,    "bvs",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bvs},
        {0x8600,    "bcc",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bcc},
        {0x8700,    "bcs",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bcs},
        {0x8800,    "emt",  &EmulatorPDP11::decode_traps,   &EmulatorPDP11::op_emt},
        {0x8900,    "sys",  &EmulatorPDP11::decode_traps,   &EmulatorPDP11::op_sys},
        {0105000,   "clrb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_clrb},
        {0105100,   "comb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_comb},
        {0105200,   "incb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_incb},
        {0105300,   "decb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_decb},
        {0105400,   "negb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_negb},
        {0105500,   "adcb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_adcb},
        {0105600,   "sbcb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_sbcb},
        {0105700,   "tstb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_tstb},
        {0106000,   "rorb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_rorb},
        {0106100,   "rolb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_rolb},
        {0106200,   "asrb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_asrb},
        {0106300,   "aslb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_aslb},
        //{0106400,   "mtps", decode_one_op,  op_mtps},
        //{0106500,   "mfpd", decode_one_op,  op_mfpd},
        //{0106600,   "mtpd", decode_one_op,  op_mtpd},
        //{0106700,   "mfps", decode_one_op,  op_mfpd},
        {0110000,   "movb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_movb},
        {0120000,   "cmpb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_cmpb},
        {0130000,   "bitb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bitb},
        {0140000,   "bicb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bicb},
        {0150000,   "bisb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bisb},
        {0160000,   "sub",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_sub}
    };//86 lines

};

#endif // EMULATORPDP11_H
