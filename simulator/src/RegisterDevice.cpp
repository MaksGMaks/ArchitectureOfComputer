#include "RegisterDevice.hpp"

RegisterDevice::RegisterDevice() {
    for(int i = 0; i < 128; i++) {
        registers[i] = 0;
    }
    cFlag = false;
}

void RegisterDevice::writeRegister(const char &reg, const int64_t &value) {
    registers[reg] = value;
}

int64_t RegisterDevice::readRegister(const char &reg) {
    return registers[reg];
}

void RegisterDevice::printRegisters() {
    std::cout << "CF = " << cFlag << std::endl;
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << std::dec << "\tREG[" << i*4 + j << "]" << (((i*4 + j) < 10) ? "  " : ((i*4 + j) < 100) ? " " : "") << " = " << std::hex << std::setw(14) << std::setfill('0') << (registers[i*4 + j] & 0x00ffffffffffffff) << "\t";
        }
        std::cout << std::endl;
    }
}

void RegisterDevice::printRegistersFile(std::ofstream &outFile) {
    outFile << "CF = " << cFlag << std::endl;
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 4; j++) {
            outFile << std::dec << "\tREG[" << i*4 + j << "]" << (((i*4 + j) < 10) ? "  " : ((i*4 + j) < 100) ? " " : "") << " = " << std::hex << std::setw(14) << std::setfill('0') << (registers[i*4 + j] & 0x00ffffffffffffff) << "\t";
        }
        outFile << std::endl;
    }
}

void RegisterDevice::writeCFlag(bool &value) {
    cFlag = value;
}

bool RegisterDevice::readCFlag() {
    return cFlag;
}