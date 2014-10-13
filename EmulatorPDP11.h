#ifndef EMULATORPDP11_H
#define EMULATORPDP11_H

#include <stdint.h>
#include <string>

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


    std::string Decode(const u_int16_t* &pc); // could require up to 3 words allocated

private:

    char mem_[64*1024];
    u_int16_t regs_[8];
    u_int16_t psw_; // processor status word
    bool running_; // TODO: delete it!
    u_int16_t& fp_ = regs_[5];
    u_int16_t& sp_ = regs_[6];
    u_int16_t& pc_ = regs_[7];
    void op_halt(void* a, void*b);
    void op_wait(void* a, void*b);
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

};

#endif // EMULATORPDP11_H
