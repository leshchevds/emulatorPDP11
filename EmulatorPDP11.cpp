#include "EmulatorPDP11.h"

#include <cstring>

EmulatorPDP11::EmulatorPDP11() {
    memset(mem_, 0xf0, 64*1024); // 64*1024 = memory size
}


EmulatorPDP11::EmulatorPDP11(const char* source, size_t count) :
                    EmulatorPDP11() {
    memcpy(mem_, source, count);
}


EmulatorPDP11::~EmulatorPDP11() {
}

const char* EmulatorPDP11::videomem() {
    return mem_ + 32 * 1024; // video mem address
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
