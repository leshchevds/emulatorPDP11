#ifndef EMULATORPDP11_H
#define EMULATORPDP11_H

#include <stdint.h>
#include <string>
#include <functional>

class EmulatorPDP11;


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
    u_int16_t& fp_ = regs_[5];
    u_int16_t& sp_ = regs_[6];
    u_int16_t& pc_ = regs_[7];

    //u_int16_t psw_; // processor status word
    bool running_; // TODO: delete it!

    bool psw_[4];
    bool& psw_N_ = psw_[0];
    bool& psw_Z_ = psw_[1];
    bool& psw_V_ = psw_[2];
    bool& psw_C_ = psw_[3];

#include "decoders.inc"
#include "operations.inc"
#include "tab.inc"
    std::string step_and_list();
};

#endif // EMULATORPDP11_H
