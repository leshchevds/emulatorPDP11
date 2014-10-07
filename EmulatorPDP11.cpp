#include "EmulatorPDP11.h"

#include <cstring>
#include <fstream>
#include <QPixmap>


EmulatorPDP11::EmulatorPDP11() {
    mem_ = new char[64*1024];
    char* video = mem_ + 32*1024;

    memset(mem_, 0xff, 64*1024);



    std::fstream file;
    file.open("D:\\emulatorPDP11\\screen.bmp", std::fstream::in | std::fstream::binary);
    file.seekg(62+512/2);
    file.read(mem_ + 48*1024 + 512, 16*1024 - 512);

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


EmulatorPDP11::EmulatorPDP11(const char* source, size_t count) :
                    EmulatorPDP11() {
    //memcpy(mem_, source, count);
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
