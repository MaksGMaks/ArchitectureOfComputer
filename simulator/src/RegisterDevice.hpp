#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

class RegisterDevice {
public:
    RegisterDevice();
    ~RegisterDevice() = default;

    void writeRegister(const char &reg, const int64_t &value);
    int64_t readRegister(const char &reg);
    void printRegisters();
    void printRegistersFile(std::ofstream &outFile);

    void writeCFlag(bool &value);
    bool readCFlag();

private:
    int64_t registers[128];
    bool cFlag;    
};