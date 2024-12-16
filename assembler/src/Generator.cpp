#include "Generator.hpp"

k_13::Generator::Generator() {
    binaryCode.clear();
}

int k_13::Generator::generate(const std::map<int, command> &commands_, const std::list<std::pair<std::string, identifier>> &identifiers_) {
    commands = commands_;
    identifiers = identifiers_;
    int64_t code = 0;
    int64_t opcode = 0;
    int64_t offset = 0;
    std::bitset<56> bs;
    int progSize = commands.size();
    for(auto &idn : identifiers) {
        if(idn.second.isData) {
            idn.second.memLoc = progSize;
            progSize++;
        }
    }
    for(auto &com : commands) {
        switch (com.second.opcode) {
        case LexemType::LOAD:
            opcode = 0;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::STORE:
            opcode = 1LL << 39;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::LOAD_REG:
            opcode = 2LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SWAP:
            opcode = 3LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::ADD:
            opcode = 4LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SUB:
            opcode = 5LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::XADD:
            opcode = 6LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::XSUB:
            opcode = 7LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::MULT:
            opcode = 8LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::IMULT:
            opcode = 9LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::INC:
            opcode = 10LL << 39;
            code = r1_type(opcode, com.second.operand1);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::DEC:
            opcode = 11LL << 39;
            code = r1_type(opcode, com.second.operand1);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::AND:
            opcode = 12LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::OR:
            opcode = 13LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::XOR:
            opcode = 14LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::NOT:
            opcode = 15LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SAL:
            opcode = 16LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SAR:
            opcode = 17LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::CMPEQ:
            opcode = 18LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::BT:
            opcode = 19LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::ADB:
            opcode = 20LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::SBB:
            opcode = 21LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::RCL:
            opcode = 22LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::RCR:
            opcode = 23LL << 39;
            code = r3_type(opcode, com.second.operand1, com.second.operand2, com.second.operand3);
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::BEZ:
            opcode = 24LL << 39;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::BNZ:
            opcode = 25LL << 39;
            code = r1_type(opcode, com.second.operand1);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMA:
            opcode = 26LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMB:
            opcode = 27LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMAE:
            opcode = 28LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMBE:
            opcode = 29LL << 39;
            code = r2_type(opcode, com.second.operand1, com.second.operand2);
            if(!findOffset(offset, com.second.offset))
                return -1;
            code |= offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::JMP:
            opcode = 30LL << 39;
            if(!findOffset(offset, com.second.offset))
                return -1;
            code = opcode | offset;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        case LexemType::HALT:
            opcode = 31LL << 39;
            code = opcode;
            bs = std::bitset<56>(code);
            binaryCode.push_back(bs);
            break;
        default:
            break;
        }
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

bool k_13::Generator::findOffset(int64_t &operand, const std::string &name) {
    try{
        operand = std::stoll(name);
        return true;
    } catch (std::invalid_argument &e) {
        for(auto &idn : identifiers) {
            if(idn.first == name) {
                operand = idn.second.memLoc;
                return true;
            }
        }
    }
    std::cerr << "\t[GEN_ERROR] unknown identifier - " << name << std::endl;
    return false;   
}

int64_t k_13::Generator::r3_type(const int64_t &opcode, const int64_t &operand1, const int64_t &operand2, const int64_t &operand3) {
    int64_t op1 = operand1 << 32;
    int64_t op2 = operand2 << 25;
    int64_t op3 = operand3;
    return (opcode | op1 | op2 | op3);
}

int64_t k_13::Generator::r2_type(const int64_t &opcode, const int64_t &operand1, const int64_t &operand2) {
    int64_t op1 = operand1 << 32;
    int64_t op2 = operand2 << 25;
    return (opcode | op1 | op2);
}

int64_t k_13::Generator::r1_type(const int64_t &opcode, const int64_t &operand1) {
    int64_t op1 = operand1 << 32;
    return (opcode | op1);
}