#include "Processor.hpp"

Processor::Processor() {
    PC = 0;
    IR = 0;
    registerDevice = std::make_unique<RegisterDevice>();
    memoryDevice = std::make_unique<MemoryDevice>();
}

int Processor::initMemory(const std::string &inpPath) {
    std::ifstream inpFile(inpPath);
    if(!inpFile.is_open()) {
        return -1;
    }
    int memoryAdr = 0;

    while (!inpFile.eof()) {
        std::string line;
        std::getline(inpFile, line);
        std::bitset<56> value(line);
        int64_t val = value.to_ullong();
        if(value[55])
            val |= 0xFF00000000000000;
        memoryDevice->writeMemory(memoryAdr, val);
        memoryAdr++;
    }
    return 0;
}

void Processor::run() {
    bool halt = false;
    while (!halt) {
        IR = memoryDevice->readMemory(PC);
        int64_t temp = 0;
        bool cFlag = false;
        int64_t op1 = 0;
        int64_t op2 = 0;
        std::cout << "OPCODE = " << (IR >> 39) << std::endl;
        switch (IR >> 39) {
        case 0:
            registerDevice->writeRegister(((IR >> 32) & 0x7F), memoryDevice->readMemory(IR & 0x1FFFFFF));
            break;
        case 1:
            memoryDevice->writeMemory(IR & 0x1FFFFFF, registerDevice->readRegister(((IR >> 32) & 0x7F)));
            break;
        case 2:
            registerDevice->writeRegister(((IR >> 32) & 0x7F), registerDevice->readRegister((IR >> 25) & 0x7F));
            break;
        case 3:
            temp = registerDevice->readRegister(((IR >> 32) & 0x7F));
            registerDevice->writeRegister(((IR >> 32) & 0x7F), registerDevice->readRegister((IR >> 25) & 0x7F));
            registerDevice->writeRegister((IR >> 25) & 0x7F, temp);
            break;
        case 4:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) + registerDevice->readRegister((IR >> 25) & 0x7F));
            if(temp > 0x7FFFFFFFFFFFFFFF) {
                temp &= 0x7FFFFFFFFFFFFFFF;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else {
                cFlag = false;
                registerDevice->writeCFlag(cFlag);
            }
            registerDevice->writeRegister((IR & 0x7F), temp);
            break;
        case 5:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) - registerDevice->readRegister((IR >> 25) & 0x7F));
            if(temp < 0xFF80000000000000) {
                temp |= 0x0080000000000000;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else {
                cFlag = false;
                registerDevice->writeCFlag(cFlag);
            }
            registerDevice->writeRegister((IR & 0x7F), temp);
            break;
        case 6:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) + registerDevice->readRegister((IR >> 25) & 0x7F));
            if(temp > 0x7FFFFFFFFFFFFFFF) {
                temp &= 0x7FFFFFFFFFFFFFFF;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else {
                cFlag = false;
                registerDevice->writeCFlag(cFlag);
            }
            registerDevice->writeRegister((IR & 0x7F), temp);
            temp = registerDevice->readRegister(((IR >> 32) & 0x7F));
            registerDevice->writeRegister(((IR >> 32) & 0x7F), registerDevice->readRegister((IR >> 25) & 0x7F));
            registerDevice->writeRegister((IR >> 25) & 0x7F, temp);
            break;
        case 7:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) - registerDevice->readRegister((IR >> 25) & 0x7F));
            if(temp < 0xFF80000000000000) {
                temp |= 0x0080000000000000;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else {
                cFlag = false;
                registerDevice->writeCFlag(cFlag);
            }
            registerDevice->writeRegister((IR & 0x7F), temp);
            temp = registerDevice->readRegister(((IR >> 32) & 0x7F));
            registerDevice->writeRegister(((IR >> 32) & 0x7F), registerDevice->readRegister((IR >> 25) & 0x7F));
            registerDevice->writeRegister((IR >> 25) & 0x7F, temp);
            break;
        case 8:
            op1 = registerDevice->readRegister((IR >> 32) & 0x7F);
            op2 = registerDevice->readRegister((IR >> 25) & 0x7F);
            (op1 < 0) ? op1 *= -1 : op1;
            (op2 < 0) ? op2 *= -1 : op2;
            temp = (op1 * op2);
            cFlag = ((temp >> 55) != 0);
            temp &= 0x007FFFFFFFFFFFFF;
            registerDevice->writeRegister((IR & 0x7F), temp);
            registerDevice->writeCFlag(cFlag);
            break;
        case 9:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) * registerDevice->readRegister((IR >> 25) & 0x7F));
            if(temp > 0x007FFFFFFFFFFFFF) {
                temp &= 0x007FFFFFFFFFFFFF;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else if(temp < 0xFF80000000000000) {
                temp |= 0x0080000000000000;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else {
                cFlag = false;
                registerDevice->writeCFlag(cFlag);
            }
            registerDevice->writeRegister((IR & 0x7F), temp);
            break;
        case 10:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) + 1);
            if(temp > 0x7FFFFFFFFFFFFFFF) {
                temp &= 0x7FFFFFFFFFFFFFFF;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else {
                cFlag = false;
                registerDevice->writeCFlag(cFlag);
            }
            registerDevice->writeRegister(((IR >> 32) & 0x7F), temp);
            break;
        case 11:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) - 1);
            if(temp < 0xFF80000000000000) {
                temp |= 0x0080000000000000;
                cFlag = true;
                registerDevice->writeCFlag(cFlag);
            } else {
                cFlag = false;
                registerDevice->writeCFlag(cFlag);
            }
            registerDevice->writeRegister(((IR >> 32) & 0x7F), (registerDevice->readRegister((IR >> 32) & 0x7F) - 1));
            registerDevice->writeRegister(((IR >> 32) & 0x7F), temp);
            break;
        case 12:
            registerDevice->writeRegister((IR & 0x7F), (registerDevice->readRegister((IR >> 32) & 0x7F) & registerDevice->readRegister((IR >> 25) & 0x7F)));
            break;
        case 13:
            registerDevice->writeRegister((IR & 0x7F), (registerDevice->readRegister((IR >> 32) & 0x7F) | registerDevice->readRegister((IR >> 25) & 0x7F)));
            break;
        case 14:
            registerDevice->writeRegister((IR & 0x7F), (registerDevice->readRegister((IR >> 32) & 0x7F) ^ registerDevice->readRegister((IR >> 25) & 0x7F)));
            break;
        case 15:
            registerDevice->writeRegister((IR & 0x7F), ~(registerDevice->readRegister((IR >> 32) & 0x7F)));
            break;
        case 16:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) << (registerDevice->readRegister((IR >> 25) & 0x7F) - 1));
            cFlag = (temp & 0x1);
            temp <<= 1;
            registerDevice->writeRegister((IR & 0x7F), temp);
            registerDevice->writeCFlag(cFlag);
            break;
        case 17:
            temp = (registerDevice->readRegister((IR >> 32) & 0x7F) >> (registerDevice->readRegister((IR >> 25) & 0x7F) - 1));
            cFlag = (temp & 0x1);
            temp >>= 1;
            registerDevice->writeRegister((IR & 0x7F), temp);
            registerDevice->writeCFlag(cFlag);
            break;
        case 18:
            if(registerDevice->readRegister((IR >> 32) & 0x7F) == registerDevice->readRegister((IR >> 25) & 0x7F)) {
                registerDevice->writeRegister((IR & 0x7F), 1);
            } else {
                registerDevice->writeRegister((IR & 0x7F), 0);
            }
            break;
        case 19:
            cFlag = (registerDevice->readRegister((IR >> 32) & 0x7F) >> registerDevice->readRegister((IR >> 25) & 0x7F)) & 0x1;
            registerDevice->writeCFlag(cFlag);
            break;
        case 20:
            registerDevice->writeRegister((IR & 0x7F), (registerDevice->readRegister((IR >> 32) & 0x7F) + registerDevice->readRegister((IR >> 25) & 0x7F) + registerDevice->readCFlag()));
            break;
        case 21:
            registerDevice->writeRegister((IR & 0x7F), (registerDevice->readRegister((IR >> 32) & 0x7F) - registerDevice->readRegister((IR >> 25) & 0x7F) - registerDevice->readCFlag()));
            break;
        case 22:
            temp = registerDevice->readRegister((IR >> 32) & 0x7F);
            std::cout << "temp on start = " << temp << std::endl;
            for(int64_t i = 0; i < registerDevice->readRegister((IR >> 25) & 0x7F); i++) {
                cFlag = (temp >> 56) & 0x1;
                std::cout << "cFlag = " << cFlag << std::endl;
                registerDevice->writeCFlag(cFlag);
                temp <<= 1;
                temp |= cFlag;
                std::cout << "temp = " << temp << std::endl;
            }
            registerDevice->writeRegister(IR & 0x7F, temp);
            break;
        case 23:
            temp = registerDevice->readRegister((IR >> 32) & 0x7F);
            std::cout << "temp on start = " << temp << std::endl;
            for(int64_t i = 0; i < registerDevice->readRegister((IR >> 25) & 0x7F); i++) {
                cFlag = temp & 0x1;
                std::cout << "cFlag = " << cFlag << std::endl;
                registerDevice->writeCFlag(cFlag);
                temp >>= 1;
                op1 = cFlag;
                temp |= (op1 << 56);
                std::cout << "temp = " << temp << std::endl;
            }
            registerDevice->writeRegister(IR & 0x7F, temp);
            break;
        case 24:
            if(registerDevice->readRegister((IR >> 32) & 0x7F) == 0) {
                PC = (IR & 0x1FFFFFF) - 1;
            }
            break;
        case 25:
            if(registerDevice->readRegister((IR >> 32) & 0x7F) != 0) {
                PC = (IR & 0x1FFFFFF) - 1;
            }
            break;
        case 26:
            if(registerDevice->readRegister((IR >> 32) & 0x7F) > registerDevice->readRegister((IR >> 25) & 0x7F)) {
                PC = (IR & 0x1FFFFFF) - 1;
            } 
            break;
        case 27:
            if(registerDevice->readRegister((IR >> 32) & 0x7F) < registerDevice->readRegister((IR >> 25) & 0x7F)) {
                PC = (IR & 0x1FFFFFF) - 1;
            } 
            break;
        case 28:
            if(registerDevice->readRegister((IR >> 32) & 0x7F) >= registerDevice->readRegister((IR >> 25) & 0x7F)) {
                PC = (IR & 0x1FFFFFF) - 1;
            } 
            break;
        case 29:
            if(registerDevice->readRegister((IR >> 32) & 0x7F) <= registerDevice->readRegister((IR >> 25) & 0x7F)) {
                PC = (IR & 0x1FFFFFF) - 1;
            } 
            break;
        case 30:
            PC = (IR & 0x1FFFFFF) - 1;
            break;
        case 31:
            halt = true;
            break;
        default:
            break;
        }
        std::cout << "\nPC = " << PC << " IR = " << IR << std::endl;
        registerDevice->printRegisters();
        std::cout << std::endl;
        memoryDevice->printMemory();
        PC++;
    }
}