#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <bitset>

#include "MemoryDevice.hpp"
#include "RegisterDevice.hpp"

class Processor {
public:
    Processor();
    ~Processor() = default;

    void run();
    int initMemory(const std::string &inpPath);

private:
    std::unique_ptr<MemoryDevice> memoryDevice;
    std::unique_ptr<RegisterDevice> registerDevice;

    int PC;
    int64_t IR;
    
    char findRegister1(const int64_t &operand);
    char findRegister2(const int64_t &operand);
    char findRegister3(const int64_t &operand);
    int findOffset(const int64_t &operand);

};