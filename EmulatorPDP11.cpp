#include "EmulatorPDP11.h"

#include <cstring>
#include <sstream>
#include <fstream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

EmulatorPDP11::EmulatorPDP11() {
    Reset();
}

char* EmulatorPDP11::videomem() {
    return mem_ + 32 * 1024; // video mem address
}

inline bool EmulatorPDP11::CheckInROM(void* addr) {
    return addr >= rom_ && addr < rom_ + 16*1024;
}

EmulatorPDP11::EmulatorPDP11(const char* source, size_t count) :
                    EmulatorPDP11() {
    memcpy(mem_, source, count);
}

EmulatorPDP11::~EmulatorPDP11() {
}

void EmulatorPDP11::WriteROM(std::string source, size_t count) {
    std::fstream file;
    file.open(source, std::fstream::in | std::fstream::binary);
    file.read(rom_, count);
    file.close();
}

void EmulatorPDP11::Reset() {
    memset(mem_, 0xff, 48*1024);

    pc_ = 48 * 1024; // ROM start address
    regs_[0] = regs_[1] = regs_[2] = regs_[3] = regs_[4] = regs_[5] = 0;
    psw_C_ = psw_N_ = psw_V_ = psw_Z_ = 0;

    WriteROM("rom.row");
}

void EmulatorPDP11::op_halt(void* a, void* b) {
    pc_ -= 2;
}

void EmulatorPDP11::op_wait(void* a, void* b) {}

#define BYTE_MSB(byte) (byte>>7)
#define WORD_MSB(word) (word>>15)

void EmulatorPDP11::op_rti(void* a, void* b) {return;}
void EmulatorPDP11::op_bpt(void* a, void* b) {return;}
void EmulatorPDP11::op_iot(void* a, void* b) {return;}
void EmulatorPDP11::op_reset(void* a, void* b) {return;}
void EmulatorPDP11::op_rtt(void* a, void* b) {return;}
void EmulatorPDP11::op_jmp(void* a, void* b) {return;}
void EmulatorPDP11::op_rts(void* a, void* b) {return;}
void EmulatorPDP11::op_spl(void* a, void* b) {return;}

void EmulatorPDP11::op_nop(void* a, void* b)
{
    return;
}

void EmulatorPDP11::op_clc(void* a, void* b) {return;}
void EmulatorPDP11::op_clv(void* a, void* b) {return;}
void EmulatorPDP11::op_clz(void* a, void* b) {return;}
void EmulatorPDP11::op_cln(void* a, void* b) {return;}
void EmulatorPDP11::op_ccc(void* a, void* b) {return;}
void EmulatorPDP11::op_sec(void* a, void* b) {return;}
void EmulatorPDP11::op_sev(void* a, void* b) {return;}
void EmulatorPDP11::op_sez(void* a, void* b) {return;}
void EmulatorPDP11::op_sen(void* a, void* b) {return;}
void EmulatorPDP11::op_scc(void* a, void* b) {return;}
void EmulatorPDP11::op_swab(void* a, void* b) {return;}

void EmulatorPDP11::op_br(void* a, void*b) {
    return;
}

void EmulatorPDP11::op_bne(void* offset, void* unused) {
    if (psw_Z_ == false) {
        pc_ += (2 * (int8_t) *((uint8_t*)(&offset)));
    }
}

void EmulatorPDP11::op_beq(void* a, void* b) {return;}
void EmulatorPDP11::op_bge(void* a, void* b) {return;}
void EmulatorPDP11::op_blt(void* a, void* b) {return;}
void EmulatorPDP11::op_bgt(void* a, void* b) {return;}
void EmulatorPDP11::op_ble(void* a, void* b) {return;}
void EmulatorPDP11::op_jsr(void* a, void* b) {return;}

void EmulatorPDP11::op_clr(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("clr in rom");
        run_lock_.store(false);
        return;
    }

    psw_Z_ = 1;
    psw_C_ = psw_N_ = psw_V_ = 0;
    *(uint16_t*)addr = 0;
}

void EmulatorPDP11::op_com(void* a, void* b) {return;}

void EmulatorPDP11::op_inc(void* addr, void* unused) {    
    if (CheckInROM(addr)) {
        return;
    }

    psw_N_ = WORD_MSB(*(uint16_t*)addr);
    psw_Z_ = *(uint16_t*)addr;
    psw_V_ = (uint32_t)(*(uint16_t*)addr) + 1 != (uint32_t)(*(uint16_t*)addr + 1);
    (*(uint16_t*)addr)++;
}

void EmulatorPDP11::op_dec(void* addr, void* unused) {
    if (CheckInROM(addr)) {
        return;
    }

    psw_N_ = WORD_MSB(*(uint16_t*)addr);
    psw_Z_ = *(uint16_t*)addr;
    psw_V_ = (uint32_t)(*(uint16_t*)addr) - 1 != (uint32_t)(*(uint16_t*)addr - 1);
    (*(uint16_t*)addr)--;
}

void EmulatorPDP11::op_neg(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("neg to rom");
        return;
    }

    psw_V_ = (*(uint16_t*)addr) & (1<<15);
    psw_N_ = BYTE_MSB(*(uint16_t*)addr);
    psw_C_ = psw_Z_ = *(uint16_t*)addr;
}

void EmulatorPDP11::op_adc(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("adc to rom");
        return;
    }

    psw_V_ = (uint32_t)(*(uint16_t*)addr) + (uint32_t)psw_C_ !=
            (uint32_t)(*(uint16_t*)addr + (uint16_t)psw_C_);
    *(uint16_t*)addr += psw_C_;
    psw_N_ = WORD_MSB(*(uint16_t*)addr);
    psw_Z_ = *(uint16_t*)addr;
}

void EmulatorPDP11::op_sbc(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("sbc to rom");
        return;
    }

    psw_V_ = (uint32_t)(*(uint16_t*)addr) - (uint32_t)psw_C_ !=
            (uint32_t)(*(uint16_t*)addr - (uint16_t)psw_C_);
    *(uint16_t*)addr -= psw_C_;
    psw_N_ = WORD_MSB(*(uint16_t*)addr);
    psw_Z_ = *(uint16_t*)addr;
}


void EmulatorPDP11::op_tst(void* addr, void* b)
{
    psw_V_ = psw_C_ = 0;
    psw_N_ = WORD_MSB(*(uint16_t*)addr);
    psw_Z_ = *(uint16_t*)addr;
}

void EmulatorPDP11::op_ror(void* a, void* b) {return;}
void EmulatorPDP11::op_rol(void* a, void* b) {return;}
void EmulatorPDP11::op_asr(void* a, void* b) {return;}
void EmulatorPDP11::op_asl(void* a, void* b) {return;}
void EmulatorPDP11::op_mark(void* a, void* b) {return;}
void EmulatorPDP11::op_mfpi(void* a, void* b) {return;}
void EmulatorPDP11::op_mtpi(void* a, void* b) {return;}
void EmulatorPDP11::op_sxt(void* a, void* b) {return;}
void EmulatorPDP11::op_mul(void* a, void* b) {return;}
void EmulatorPDP11::op_div(void* a, void* b) {return;}
void EmulatorPDP11::op_ash(void* a, void* b) {return;}
void EmulatorPDP11::op_ashc(void* a, void* b) {return;}
void EmulatorPDP11::op_xor(void* a, void* b) {return;}

void EmulatorPDP11::op_sob(void* reg, void* n) {
    if (--(*(uint16_t*)reg)) {
        pc_ -= *((uint8_t*)(&n)) * 2;
    }
}

void EmulatorPDP11::op_mov(void* src, void* dst) {
    if (CheckInROM(dst)) {
        return;
    }

    *(uint16_t*)dst = *(uint16_t*)src;
    psw_N_ = WORD_MSB(*(uint16_t*)dst);
    psw_Z_ = *(uint16_t*)dst == 0;
    psw_V_ = 0;
}

void EmulatorPDP11::op_cmp(void* src, void* dst) {
    psw_V_ = (uint32_t)(*(uint16_t*)dst) - (uint32_t)(*(uint16_t*)src) !=
            (uint32_t)(*(uint16_t*)dst - *(uint16_t*)src);
    uint16_t val = *(uint16_t*)dst - *(uint16_t*)src;
    psw_N_ &= WORD_MSB(val);
    psw_Z_ = !(bool)val;
}

void EmulatorPDP11::op_bit(void* a, void* b) {return;}
void EmulatorPDP11::op_bic(void* a, void* b) {return;}

void EmulatorPDP11::op_bis(void* src, void* dst){
    if (CheckInROM(dst)) {
        return;
    }

    psw_V_ = (uint32_t)(*(uint16_t*)dst) | (uint32_t)(*(uint16_t*)src) !=
            (uint32_t)(*(uint16_t*)dst | *(uint16_t*)src);
    *(uint16_t*)dst |= *(uint16_t*)src;
    psw_N_ = WORD_MSB(*(uint16_t*)dst);
    psw_Z_ = *(uint16_t*)dst;
}

void EmulatorPDP11::op_add(void* src, void* dst) {
    if (CheckInROM(dst)) {
        return;
    }

    psw_V_ = (uint32_t)(*(uint16_t*)dst) + (uint32_t)(*(uint16_t*)src) !=
            (uint32_t)(*(uint16_t*)dst + *(uint16_t*)src);
    *(uint16_t*)dst += *(uint16_t*)src;
    psw_N_ = WORD_MSB(*(uint16_t*)dst);
    psw_Z_ = *(uint16_t*)dst;
}

void EmulatorPDP11::op_movb(void* src, void* dst) {
    if (CheckInROM(dst)) {
        return;
    }

    *(uint8_t*)dst = *(uint8_t*)src;
    psw_N_ = BYTE_MSB(*(uint8_t*)dst);
    psw_Z_ = *(uint8_t*)dst;
    psw_V_ = 0;
}

void EmulatorPDP11::op_cmpb(void* a, void* b) {return;}
void EmulatorPDP11::op_bitb(void* a, void* b) {return;}
void EmulatorPDP11::op_bicb(void* a, void* b) {return;}
void EmulatorPDP11::op_bisb(void* a, void* b) {return;}

void EmulatorPDP11::op_sub(void* src, void* dst) {
    if (CheckInROM(dst)) {
        return;
    }

    psw_V_ = (uint32_t)(*(uint16_t*)dst) - (uint32_t)(*(uint16_t*)src) !=
            (uint32_t)(*(uint16_t*)dst - *(uint16_t*)src);
    *(uint16_t*)dst -= *(uint16_t*)src;
    psw_N_ &= WORD_MSB(*(uint16_t*)dst);
    psw_Z_ &= *(uint16_t*)dst;
}

void EmulatorPDP11::op_bpl(void* a, void* b) {return;}
void EmulatorPDP11::op_bmi(void* a, void* b) {return;}
void EmulatorPDP11::op_bhi(void* a, void* b) {return;}
void EmulatorPDP11::op_blos(void* a, void* b) {return;}
void EmulatorPDP11::op_bvc(void* a, void* b) {return;}
void EmulatorPDP11::op_bvs(void* a, void* b) {return;}
void EmulatorPDP11::op_bcc(void* a, void* b) {return;}
void EmulatorPDP11::op_bcs(void* a, void* b) {return;}
void EmulatorPDP11::op_emt(void* a, void* b) {return;}
void EmulatorPDP11::op_sys(void* a, void* b) {return;}

void EmulatorPDP11::op_clrb(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("clrb in rom");
        run_lock_.store(false);
        return;
    }

    psw_Z_ = 1;
    psw_C_ = psw_N_ = psw_V_ = 0;
    *(uint8_t*)addr = 0;
}

void EmulatorPDP11::op_comb(void* a, void* b) {return;}

void EmulatorPDP11::op_incb(void* addr, void* unused)
{
    if (CheckInROM(addr)) {
        return;
    }

    psw_V_ = ((uint16_t)(*(uint8_t*)addr) + 1) != (uint16_t)(*(uint8_t*)addr + 1);
    (*(uint8_t*)addr)++;
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_Z_ = *(uint8_t*)addr;
}

void EmulatorPDP11::op_decb(void* addr, void* unused) {
    if (CheckInROM(addr)) {
        return;
    }

    psw_V_ = ((uint16_t)(*(uint8_t*)addr) - 1) != (uint16_t)(*(uint8_t*)addr - 1);
    (*(uint8_t*)addr)--;
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_Z_ = *(uint8_t*)addr;
}

void EmulatorPDP11::op_negb(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("negb to rom");
        return;
    }

    psw_V_ = (*(uint8_t*)addr) & (1<<7);
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_C_ = psw_Z_ = *(uint8_t*)addr;
}

void EmulatorPDP11::op_adcb(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("adcb to rom");
        return;
    }

    psw_V_ = (uint16_t)(*(uint8_t*)addr) + (uint16_t)psw_C_ !=
            (uint16_t)(*(uint8_t*)addr + (uint8_t)psw_C_);
    *(uint8_t*)addr += psw_C_;
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_Z_ = *(uint8_t*)addr;
}

void EmulatorPDP11::op_sbcb(void* addr, void* b)
{
    if (CheckInROM(addr)) {
        PushOperation("sbcb to rom");
        return;
    }

    psw_V_ = (uint16_t)(*(uint8_t*)addr) - (uint16_t)psw_C_ !=
            (uint16_t)(*(uint8_t*)addr - (uint8_t)psw_C_);
    *(uint8_t*)addr -= psw_C_;
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_Z_ = *(uint8_t*)addr;
}


void EmulatorPDP11::op_tstb(void* addr, void* b)
{
    psw_V_ = psw_C_ = 0;
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_Z_ = *(uint8_t*)addr;
}

void EmulatorPDP11::op_rorb(void* a, void* b) {return;}
void EmulatorPDP11::op_rolb(void* a, void* b) {return;}
void EmulatorPDP11::op_asrb(void* a, void* b) {return;}
void EmulatorPDP11::op_aslb(void* a, void* b) {return;}
