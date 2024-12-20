#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

class MemoryDevice {
public:
    MemoryDevice();
    ~MemoryDevice() = default;

    void writeMemory(const int &address, const int64_t &value);
    int64_t readMemory(const int &address);
    void printMemory();
    void printMemoryFile(std::ofstream &outFile);
    
private:
    std::vector<int64_t> memory;
};