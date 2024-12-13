#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <bitset>

#include "MemoryDevice.hpp"
#include "RegisterDevice.hpp"
#include "Processor.hpp"

int main(int argc, char *argv[]) {
    std::cout << "[INFO] Start simulator" << std::endl;
    if (argc < 2) {
        std::cerr << "Error: input path to file.mc for simulation" << std::endl;
        return -1;
    }

    std::string inpPath = argv[1];

    std::unique_ptr<MemoryDevice> memoryDevice = std::make_unique<MemoryDevice>();

    std::cout << "[INFO] Start reading file" << std::endl;
    
    Processor processor;
    if(processor.initMemory(inpPath) != 0) {
        std::cerr << "Error: failed to initialize memory" << std::endl;
        return -1;
    }
    std::cout << "[INFO] Done. Run simulation" << std::endl;

    processor.run();

    std::cout << "[INFO] Simulation completed" << std::endl;

    return 0;
}