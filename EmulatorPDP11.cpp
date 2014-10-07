#include "EmulatorPDP11.h"

#include <cstring>

EmulatorPDP11::EmulatorPDP11() {
    mem_ = new char[64*1024];
}


EmulatorPDP11::EmulatorPDP11(const char* source, size_t count) :
                    EmulatorPDP11() {
    memcpy(mem_, source, count);
}


EmulatorPDP11::~EmulatorPDP11() {
    delete mem_;
}

const char* EmulatorPDP11::videomem() {
    return mem_ + 32 * 1024;
}

size_t EmulatorPDP11::WriteROM(const char* source, size_t count) {
    memcpy(mem_ + 48 * 1024, source, count);
}

void EmulatorPDP11::Run() {

}

void EmulatorPDP11::Stop() {

}

void EmulatorPDP11::Step() {

}

void EmulatorPDP11::Reset() { // TODO: what is reset?
    pc_ = 48 * 1024;
    regs_[0] = regs_[1] = regs_[2] = regs_[3] = 0;
}
