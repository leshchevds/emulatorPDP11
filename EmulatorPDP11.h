#ifndef EMULATORPDP11_H
#define EMULATORPDP11_H

#include <stdint.h>
#include <string>
#include <functional>

class EmulatorPDP11;

typedef std::string (EmulatorPDP11::*d_func)(u_int16_t*&);
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


    std::string Decode(u_int16_t* &pc); // could require up to 3 words allocated NOT CONST!!! DECODER CHANGING PC!!!

private:

    char mem_[64*1024];
    u_int16_t regs_[8];
    u_int16_t psw_; // processor status word
    bool running_; // TODO: delete it!
    u_int16_t& fp_ = regs_[5];
    u_int16_t& sp_ = regs_[6];
    u_int16_t& pc_ = regs_[7];

    std::string decode_zero_op(u_int16_t* &pc);

    static void op_halt(void* a, void* b);
    static void op_wait(void* a, void* b);
    /*
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
    */

    //DISCUSS? decode_zero_op -> NULL
    instr_t tab[] = {
        {0000000,   "halt", &decode_zero_op, &op_halt},
        {0000001,   "wait", &decode_zero_op, &op_wait}
        };

    /*,
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
        {0000257,   "ccc",  dec-+ode_zero_op, op_ccc},
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
*/
};

#endif // EMULATORPDP11_H
