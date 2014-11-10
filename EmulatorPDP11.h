#ifndef EMULATORPDP11_H
#define EMULATORPDP11_H


#include <stdint.h>
#include <string>

class EmulatorPDP11;

class EmulatorPDP11 {
public:
    EmulatorPDP11();
    EmulatorPDP11(const char* source, size_t count = 16*1024);
    ~EmulatorPDP11();

    char* videomem();
    void WriteROM(std::string source, size_t count = 16*1024);

    uint16_t reg(uint8_t num) {
        if (num < 8) {
            return regs_[num];
        } else {
            throw;
        }
    }

    inline bool NFlag() {return psw_N_;}
    inline bool ZFlag() {return psw_Z_;}
    inline bool VFlag() {return psw_V_;}
    inline bool CFlag() {return psw_C_;}

    void Reset();
    std::string step_and_list();

    // could require up to 3 words allocated NOT CONST!!! DECODER CHANGING PC!!!
    std::string Decode(uint16_t* pc);
private:
    char mem_[64*1024];
    char* const rom_ = mem_ + 48*1024;

    uint16_t regs_[8];
    uint16_t& fp_ = regs_[5];
    uint16_t& sp_ = regs_[6];
    uint16_t& pc_ = regs_[7];

    bool psw_[4];
    bool& psw_N_ = psw_[0];
    bool& psw_Z_ = psw_[1];
    bool& psw_V_ = psw_[2];
    bool& psw_C_ = psw_[3];

#include "decoders.inc"
#include "operations.inc"
#include "tab.inc"

    inline bool CheckInROM(void* addr);
};

#endif // EMULATORPDP11_H
