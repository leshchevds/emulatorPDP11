#include "EmulatorPDP11.h"

#include <cstring>
#include <fstream>
#include <QtConcurrentRun>
#include <QThread>
#include <QMetaType> // without this line methods from threads emit errors

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define ROM_ADDR (mem_ + 48 * 1024)


EmulatorPDP11::EmulatorPDP11() {
    run_lock_ = false;
    qRegisterMetaType<QVector<int> >("QVector<int>");
    OpListModel_ = new QStringListModel();
    Reset();
}

char* EmulatorPDP11::videomem() {
    return mem_ + 32 * 1024; // video mem address
}

EmulatorPDP11::EmulatorPDP11(const char* source, size_t count) :
                    EmulatorPDP11() {
    memcpy(mem_, source, count);
}

EmulatorPDP11::~EmulatorPDP11() {
    runApproved_ = false;
    bool expected = false;
    while (!run_lock_.compare_exchange_strong(expected, true)) {
        expected = false;
    }
}

size_t EmulatorPDP11::WriteROM(const char* source, size_t count) {
    memcpy(ROM_ADDR, source, count); // ROM start address
    return count;
}

void EmulatorPDP11::Run() {
    bool expected = false;
    if (run_lock_.compare_exchange_strong(expected, true)) {
        runApproved_ = true;
        QtConcurrent::run(this, &EmulatorPDP11::RunWorker);
    }
}

void EmulatorPDP11::Stop() {
    runApproved_ = false;
}


void EmulatorPDP11::Step() {
    bool expected = false;
    if (run_lock_.compare_exchange_strong(expected, true)) {
        QtConcurrent::run(this, &EmulatorPDP11::step_and_list, true);
    }
}

void EmulatorPDP11::Reset() {
    runApproved_ = false;
    bool expected = false;
    while (!run_lock_.compare_exchange_strong(expected, true)) {
        expected = false;
    }

    memset(mem_, 0xff, 48*1024);

    pc_ = 48 * 1024; // ROM start address
    regs_[0] = regs_[1] = regs_[2] = regs_[3] = regs_[4] = regs_[5] = 0;

    OpListModel_->removeRows(0, OpListModel_->rowCount());
// filling in ROM
    // picture
    std::fstream file;
    file.open("screen.bmp", std::fstream::in | std::fstream::binary);
    file.seekg(62 + 256); // 256 - margin from both sides
    file.read(mem_ + 48*1024 + 512, 16*1024 - 512);
    file.close();

    //TODO: op codes are to be written here

    int R0, R1, R2, R3;
    R0 = 4*64;
first:
    R1 = 0;
second:
    R2 = 32*1024 + R0 + R1;
    R3 = 48*1024 + 256 + R0 + R1;
    mem_[R2] = mem_[R3];
    R1 += 1;
    if (R1 < 64) goto second;
    R0 += 64;
    if (R0 < 252*64) goto first;

    R0 = 32*1024;
third:
    mem_[R0] = 0xff;
    R0 += 1;
    if (R0 < 32*1024 + (4*512/8)) goto third;

    R0 = 48*1024 - 4*(512/8);
fourth:
    mem_[R0] = 0xff;
    R0 += 1;
    if (R0 < 48*1024) goto fourth;

    R0 = 32*1024 + 4*(512/8);
fifth:
    mem_[R0] |= 0xf0;
    R1 = R0 + 63;
    mem_[R1] |= 0x0f;
    R0 += 512/8;
    if (R0 < 32*1024 + 252*(512/8)) goto fifth;


    *(uint16_t*)(mem_+48*1024) = 0010071;
    *(uint16_t*)(mem_+2+48*1024) = 0070002;
*(uint16_t*)(mem_+4+48*1024) = 0077000;
*(uint16_t*)(mem_+6+48*1024) = 0005072;
*(uint16_t*)(mem_+8+48*1024) = 0140006;
                        //052000000 is 24 bit number
                                                    //you should not adress memory in such way
                                                    //if you thought that decoder will guess where is opcode - it won't
                                                    //it expects next opcode at mem_+pc_

    run_lock_.store(false);
}

void EmulatorPDP11::RunWorker() {
    while (runApproved_) {
        EmulatorPDP11::step_and_list(false);
    }
    run_lock_.store(false);
    regs_[3] = 1235; // DEBUG
}

void EmulatorPDP11::PushOperation(QString str) {
    OpListModel_->insertRow(0);
    QModelIndex index = OpListModel_->index(0);
    const int MAX_ROWS = 10;
    if (OpListModel_->rowCount() == MAX_ROWS) {
        OpListModel_->removeRow(MAX_ROWS - 1);
    }
    OpListModel_->setData(index, str);
}

void EmulatorPDP11::op_halt(void* a, void* b) {

}

void EmulatorPDP11::op_wait(void* a, void* b) {

}

#define BYTE_MSB(byte) (byte>>7)
#define WORD_MSB(word) (word>>15)

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

void EmulatorPDP11::op_inc(void* addr, void* unused) {
    if (addr > ROM_ADDR)
        throw;

    psw_N_ = WORD_MSB(*(uint16_t*)addr);
    psw_Z_ = *(uint16_t*)addr;
    psw_V_ = (uint32_t)(*(uint16_t*)addr) + 1 != (uint32_t)(*(uint16_t*)addr + 1);
    (*(uint16_t*)addr)++;
}

void EmulatorPDP11::op_dec(void* addr, void* unused) {
    if (addr > ROM_ADDR)
        throw;

    psw_N_ = WORD_MSB(*(uint16_t*)addr);
    psw_Z_ = *(uint16_t*)addr;
    psw_V_ = (uint32_t)(*(uint16_t*)addr) - 1 != (uint32_t)(*(uint16_t*)addr - 1);
    (*(uint16_t*)addr)--;
}

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

void EmulatorPDP11::op_sob(void* reg, void* n) {
    if (--(*(uint16_t*)reg))
        pc_ -= *((uint8_t*)(&n)) * 2;
}

void EmulatorPDP11::op_mov(void* src, void* dst) {
    if (dst > ROM_ADDR)
        throw;

    *(uint16_t*)dst = *(uint16_t*)src;
    psw_N_ = WORD_MSB(*(uint16_t*)dst);
    psw_Z_ = *(uint16_t*)dst;
    psw_V_ = 0;
}

void EmulatorPDP11::op_cmp(void* a, void*b){return;}
void EmulatorPDP11::op_bit(void* a, void*b){return;}
void EmulatorPDP11::op_bic(void* a, void*b){return;}
void EmulatorPDP11::op_bis(void* a, void*b){return;}

void EmulatorPDP11::op_add(void* src, void* dst) {
    if (dst > ROM_ADDR)
        throw;

    psw_V_ = (uint32_t)(*(uint16_t*)dst) + (uint32_t)(*(uint16_t*)src) !=
            (uint32_t)(*(uint16_t*)dst + *(uint16_t*)src);
    *(uint16_t*)dst += *(uint16_t*)src;
    psw_N_ = WORD_MSB(*(uint16_t*)dst);
    psw_Z_ = *(uint16_t*)dst;
}

void EmulatorPDP11::op_movb(void* src, void* dst) {
    if (dst > ROM_ADDR)
        throw;

    *(uint8_t*)dst = *(uint8_t*)src;
    psw_N_ = BYTE_MSB(*(uint8_t*)dst);
    psw_Z_ = *(uint8_t*)dst;
    psw_V_ = 0;

}

void EmulatorPDP11::op_cmpb(void* a, void*b){return;}
void EmulatorPDP11::op_bitb(void* a, void*b){return;}
void EmulatorPDP11::op_bicb(void* a, void*b){return;}
void EmulatorPDP11::op_bisb(void* a, void*b){return;}

void EmulatorPDP11::op_sub(void* src, void* dst) {
    if (dst > ROM_ADDR)
        throw;

    psw_V_ = (uint32_t)(*(uint16_t*)dst) - (uint32_t)(*(uint16_t*)src) !=
            (uint32_t)(*(uint16_t*)dst - *(uint16_t*)src);
    *(uint16_t*)dst -= *(uint16_t*)src;
    psw_N_ &= WORD_MSB(*(uint16_t*)dst);
    psw_Z_ &= *(uint16_t*)dst;
}

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

void EmulatorPDP11::op_incb(void* addr, void* unused) {
    if (addr > ROM_ADDR)
        throw;

    psw_V_ = ((uint16_t)(*(uint8_t*)addr) + 1) != (uint16_t)(*(uint8_t*)addr + 1);
    (*(uint8_t*)addr)++;
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_Z_ = *(uint8_t*)addr;
}

void EmulatorPDP11::op_decb(void* addr, void* unused) {
    if (addr > ROM_ADDR)
        throw;

    psw_V_ = ((uint16_t)(*(uint8_t*)addr) - 1) != (uint16_t)(*(uint8_t*)addr - 1);
    (*(uint8_t*)addr)--;
    psw_N_ = BYTE_MSB(*(uint8_t*)addr);
    psw_Z_ = *(uint8_t*)addr;
}

void EmulatorPDP11::op_negb(void* a, void*b){return;}
void EmulatorPDP11::op_adcb(void* a, void*b){return;}
void EmulatorPDP11::op_sbcb(void* a, void*b){return;}
void EmulatorPDP11::op_tstb(void* a, void*b){return;}
void EmulatorPDP11::op_rorb(void* a, void*b){return;}
void EmulatorPDP11::op_rolb(void* a, void*b){return;}
void EmulatorPDP11::op_asrb(void* a, void*b){return;}
void EmulatorPDP11::op_aslb(void* a, void*b){return;}
