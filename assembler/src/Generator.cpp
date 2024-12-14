#include "Generator.hpp"

k_13::Generator::Generator() {
    binaryCode.clear();
}

int k_13::Generator::generate(const std::map<int, command> &commands_, const std::list<std::pair<std::string, identifier>> &identifiers_) {
    commands = commands_;
    identifiers = identifiers_;
    int64_t code = 0;
    int64_t opcode = 0;
    int64_t offset1 = 0;
    int64_t offset2 = 0;
    std::bitset<56> bs;
    int progSize = commands_.size();
    for(auto &idn : identifiers) {
        if(idn.second.isData) {
            idn.second.memLoc = progSize;
            progSize++;
        }
    }
    int PC = 0;
    for(auto &com : commands) {
        switch (com.second.opcode) {
        case LexemType::LOAD:
            opcode = 0;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::STORE:
            opcode = 1LL << 51;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::LOAD_REG:
            opcode = 2LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SWAP:
            opcode = 3LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::ADD:
            opcode = 4LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SUB:
            opcode = 5LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::XADD:
            opcode = 6LL << 51;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::XSUB:
            opcode = 7LL << 51;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::MULT:
            opcode = 8LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::IMULT:
            opcode = 9LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::INC:
            opcode = 10LL << 51;
            code = r1_type(opcode, com.second.operand1);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::DEC:
            opcode = 11LL << 51;
            code = r1_type(opcode, com.second.operand1);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::AND:
            opcode = 12LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::OR:
            opcode = 13LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::XOR:
            opcode = 14LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::NOT:
            opcode = 15LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SAL:
            opcode = 16LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SAR:
            opcode = 17LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::CMPEQ:
            opcode = 18LL << 51;
            if(com.second.offsetAccess) {
                if(!findOffset(offset1, com.second.offset1, PC))
                    return -1;
                if(!findOffset(offset2, com.second.offset2, PC))
                    return -1;
                offset1 |= (1<<21);
                offset2 |= (1<<21);
                code = r3_type(opcode, com.second.operand1, offset1, offset2);
            } else {
                code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            }
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::BT:
            opcode = 19LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::ADB:
            opcode = 20LL << 51;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SBB:
            opcode = 21LL << 51;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::RCL:
            opcode = 22LL << 51;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::RCR:
            opcode = 23LL << 51;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::BEZ:
            opcode = 24LL << 51;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::BNZ:
            opcode = 25LL << 51;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMA:
            opcode = 26LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMB:
            opcode = 27LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMAE:
            opcode = 28LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMBE:
            opcode = 29LL << 51;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code |= offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMP:
            opcode = 30LL << 51;
            if(!findOffset(offset2, com.second.offset2, PC))
                return -1;
            code = opcode | offset2;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::HALT:
            opcode = 31LL << 51;
            code = opcode;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        default:
            break;
        }
        PC++;
    }
    for(auto &idn : identifiers) {
        if(idn.second.isData) {
            code = idn.second.value;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
        }
    }
    return 0;
}

bool k_13::Generator::identifierExist(const std::string &name) {
    for(auto &idn : identifiers) {
        if(idn.first == name) {
            return true;
        }
    }
    return false;
}

bool k_13::Generator::findOffset(int64_t &operand, const std::string &name, const int &PC) {
    try{
        operand = std::stoll(name) - PC;
        if(operand < -1048576 || operand > 1048575) {
            std::cerr << "\t[GEN_ERROR] Offset out of range (-1048576; 1048575)" << std::endl;
            return false;
        }
        return true;
    } catch (std::invalid_argument &e) {
        for(auto &idn : identifiers) {
            if(idn.first == name) {
                operand = idn.second.memLoc - PC;
                if(operand < -1048576 || operand > 1048575) {
                    std::cerr << "\t[GEN_ERROR] Offset out of range (-1048576; 1048575)" << std::endl;
                    return false;
                }
                return true;
            }
        }
    }
    std::cerr << "[GEN_ERROR]: unknown identifier - " << name << std::endl;
    return false;   
}

int64_t k_13::Generator::r3_type(const int64_t &opcode, const int64_t &operand1, const int64_t &operand2, const int64_t &operand3) {
    int64_t op1 = operand1 << 44;
    int64_t op2 = operand2 << 22;
    int64_t op3 = operand3;
    return (opcode | op1 | op2 | op3);
}

int64_t k_13::Generator::r2_type(const int64_t &opcode, const int64_t &operand1, const int64_t &operand2) {
    int64_t op1 = operand1 << 44;
    int64_t op2 = operand2 << 22;
    return (opcode | op1 | op2);
}

int64_t k_13::Generator::r1_type(const int64_t &opcode, const int64_t &operand1) {
    int64_t op1 = operand1 << 44;
    return (opcode | op1);
}