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
};