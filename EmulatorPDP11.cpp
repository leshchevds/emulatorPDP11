#include "EmulatorPDP11.h"

#include <cstring>
#include <fstream>





EmulatorPDP11::EmulatorPDP11() {

    char* video = mem_ + 32*1024;

    memset(mem_, 0xff, 64*1024);

    std::fstream file;
    file.open("screen.bmp", std::fstream::in | std::fstream::binary);
    file.seekg(62+512/2);
    file.read(mem_ + 48*1024 + 512, 16*1024 - 512);
    file.close();

    for (int i = 4; i < 252; ++i) {
        for (int j = 0; j < 512; ++j) {
            video[i*64 + j/8] &= (255-(1<<(j%8)));
            video[i*64 + j/8] |= (1<<(j%8))* !(bool)(mem_[48*1024 + 512 + i*64 + j/8] & (1<<(8-j%8)));
        }
    }

    for (int i = 0; i < 256; ++i) {
        video[i] = 0;
    }
    for (int i = 16128; i < 16384; ++i) {
        video[i] = 0;
    }
    for (int i = 4; i < 252; ++i) {
        video[i*64 + 0] &= 16*15;
        video[i*64 + 63] &= 15;
    }


}
const char* EmulatorPDP11::videomem() {
    return mem_ + 32 * 1024; // video mem address
}

EmulatorPDP11::EmulatorPDP11(const char* source, size_t count) :
                    EmulatorPDP11() {
    memcpy(mem_, source, count);
}


EmulatorPDP11::~EmulatorPDP11() {
}


size_t EmulatorPDP11::WriteROM(const char* source, size_t count) {
    memcpy(mem_ + 48 * 1024, source, count); // ROM start address
}

void EmulatorPDP11::Run() {

}

void EmulatorPDP11::Stop() {

}

void EmulatorPDP11::Step() {

}

void EmulatorPDP11::Reset() { // TODO: what is reset?
    pc_ = 48 * 1024; // ROM start address
    regs_[0] = regs_[1] = regs_[2] = regs_[3] = 0;
}

void EmulatorPDP11::op_halt(void* a, void* b)
{

}

void EmulatorPDP11::op_wait(void* a, void* b)
{

}


void EmulatorPDP11::op_rti(void* a, void*b){return;}
void EmulatorPDP11::op_bpt(void* a, void*b){return;}
void EmulatorPDP11::op_iot(void* a, void*b){return;}
void EmulatorPDP11::op_reset(void* a, void*b){return;}
void EmulatorPDP11::op_rtt(void* a, void*b){return;}
void EmulatorPDP11::op_jmp(void* a, void*b){return;}
void EmulatorPDP11::op_rts(void* a, void*b){return;}
void EmulatorPDP11::op_spl(void* a, void*b){return;}
void EmulatorPDP11::op_nop(void* a, void*b){return;}
void EmulatorPDP11::op_clc(void* a, void*b){return;}
void EmulatorPDP11::op_clv(void* a, void*b){return;}
void EmulatorPDP11::op_clz(void* a, void*b){return;}
void EmulatorPDP11::op_cln(void* a, void*b){return;}
void EmulatorPDP11::op_ccc(void* a, void*b){return;}
void EmulatorPDP11::op_sec(void* a, void*b){return;}
void EmulatorPDP11::op_sev(void* a, void*b){return;}
void EmulatorPDP11::op_sez(void* a, void*b){return;}
void EmulatorPDP11::op_sen(void* a, void*b){return;}
void EmulatorPDP11::op_scc(void* a, void*b){return;}
void EmulatorPDP11::op_swab(void* a, void*b){return;}
void EmulatorPDP11::op_br(void* a, void*b){return;}
void EmulatorPDP11::op_bne(void* a, void*b){return;}
void EmulatorPDP11::op_beq(void* a, void*b){return;}
void EmulatorPDP11::op_bge(void* a, void*b){return;}
void EmulatorPDP11::op_blt(void* a, void*b){return;}
void EmulatorPDP11::op_bgt(void* a, void*b){return;}
void EmulatorPDP11::op_ble(void* a, void*b){return;}
void EmulatorPDP11::op_jsr(void* a, void*b){return;}
void EmulatorPDP11::op_clr(void* a, void*b){return;}
void EmulatorPDP11::op_com(void* a, void*b){return;}
void EmulatorPDP11::op_inc(void* a, void*b){return;}
void EmulatorPDP11::op_dec(void* a, void*b){return;}
void EmulatorPDP11::op_neg(void* a, void*b){return;}
void EmulatorPDP11::op_adc(void* a, void*b){return;}
void EmulatorPDP11::op_sbc(void* a, void*b){return;}
void EmulatorPDP11::op_tst(void* a, void*b){return;}
void EmulatorPDP11::op_ror(void* a, void*b){return;}
void EmulatorPDP11::op_rol(void* a, void*b){return;}
void EmulatorPDP11::op_asr(void* a, void*b){return;}
void EmulatorPDP11::op_asl(void* a, void*b){return;}
void EmulatorPDP11::op_mark(void* a, void*b){return;}
void EmulatorPDP11::op_mfpi(void* a, void*b){return;}
void EmulatorPDP11::op_mtpi(void* a, void*b){return;}
void EmulatorPDP11::op_sxt(void* a, void*b){return;}
void EmulatorPDP11::op_mul(void* a, void*b){return;}
void EmulatorPDP11::op_div(void* a, void*b){return;}
void EmulatorPDP11::op_ash(void* a, void*b){return;}
void EmulatorPDP11::op_ashc(void* a, void*b){return;}
void EmulatorPDP11::op_xor(void* a, void*b){return;}
void EmulatorPDP11::op_sob(void* a, void*b){return;}
void EmulatorPDP11::op_mov(void* a, void*b){return;}
void EmulatorPDP11::op_cmp(void* a, void*b){return;}
void EmulatorPDP11::op_bit(void* a, void*b){return;}
void EmulatorPDP11::op_bic(void* a, void*b){return;}
void EmulatorPDP11::op_bis(void* a, void*b){return;}
void EmulatorPDP11::op_add(void* a, void*b){return;}
void EmulatorPDP11::op_movb(void* a, void*b){return;}
void EmulatorPDP11::op_cmpb(void* a, void*b){return;}
void EmulatorPDP11::op_bitb(void* a, void*b){return;}
void EmulatorPDP11::op_bicb(void* a, void*b){return;}
void EmulatorPDP11::op_bisb(void* a, void*b){return;}
void EmulatorPDP11::op_sub(void* a, void*b){return;}
void EmulatorPDP11::op_bpl(void* a, void*b){return;}
void EmulatorPDP11::op_bmi(void* a, void*b){return;}
void EmulatorPDP11::op_bhi(void* a, void*b){return;}
void EmulatorPDP11::op_blos(void* a, void*b){return;}
void EmulatorPDP11::op_bvc(void* a, void*b){return;}
void EmulatorPDP11::op_bvs(void* a, void*b){return;}
void EmulatorPDP11::op_bcc(void* a, void*b){return;}
void EmulatorPDP11::op_bcs(void* a, void*b){return;}
void EmulatorPDP11::op_emt(void* a, void*b){return;}
void EmulatorPDP11::op_sys(void* a, void*b){return;}
void EmulatorPDP11::op_clrb(void* a, void*b){return;}
void EmulatorPDP11::op_comb(void* a, void*b){return;}
void EmulatorPDP11::op_incb(void* a, void*b){return;}
void EmulatorPDP11::op_decb(void* a, void*b){return;}
void EmulatorPDP11::op_negb(void* a, void*b){return;}
void EmulatorPDP11::op_adcb(void* a, void*b){return;}
void EmulatorPDP11::op_sbcb(void* a, void*b){return;}
void EmulatorPDP11::op_tstb(void* a, void*b){return;}
void EmulatorPDP11::op_rorb(void* a, void*b){return;}
void EmulatorPDP11::op_rolb(void* a, void*b){return;}
void EmulatorPDP11::op_asrb(void* a, void*b){return;}
void EmulatorPDP11::op_aslb(void* a, void*b){return;}
