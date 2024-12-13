#include "MemoryDevice.hpp"

MemoryDevice::MemoryDevice() {
    memory.reserve(33554432);
    for(int i = 0; i < 33554432; i++) {
        memory.push_back(0LL);
    }
}

void MemoryDevice::writeMemory(const int &address, const int64_t &value) {
    memory[address] = value;
}

int64_t MemoryDevice::readMemory(const int &address) {
    return memory[address];
}

void MemoryDevice::printMemory() {
    for(int i = 0; i < 33554432; i++) {
        if(memory[i] != 0) {
            std::cout << std::dec << "MEM[" << i << "] = " << std::hex << std::setw(14) << std::setfill('0') << (memory[i] & 0x00ffffffffffffff) << " = " << std::dec << memory[i] << std::endl;
        }
    }
}
