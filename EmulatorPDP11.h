#ifndef EMULATORPDP11_H
#define EMULATORPDP11_H

#include <stdint.h>
#include <string>

class EmulatorPDP11 {
public:
    EmulatorPDP11();
    explicit EmulatorPDP11(const char* source, size_t count = 16*1024) ;
    ~EmulatorPDP11();


    size_t WriteROM(const char* source, size_t count = 16*1024);

    uint16_t reg(uint8_t num);

    uint16_t psw() {return psw_;}
    bool isRunning() {return running_;}
    const char* videomem() {return mem_ + 32 * 1024;}

    void Run();
    void Stop();
    void Step();
    void Reset();


    std::string Decode(const uint16_t* pc); // could require up to 3 words allocated

private:
    char* mem_;
    uint16_t regs_[8];
    uint16_t psw_; // processor status word
    bool running_; // TODO: delete it!
    uint16_t& fp_ = regs_[5];
    uint16_t& sp_ = regs_[6];
    uint16_t& pc_ = regs_[7];

};

#endif // EMULATORPDP11_H
