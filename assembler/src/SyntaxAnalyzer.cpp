#include "SyntaxAnalyzer.hpp"

k_13::SyntaxAnalyzer::SyntaxAnalyzer() {
    code.clear();
    errorMessages.clear();
    cmd = {LexemType::UNUSED, 0, 0, 0, ""};
    commands.clear();
}

int k_13::SyntaxAnalyzer::analyze(const std::vector<Lexem> &lexems) {
    std::cout << "[INFO] Starting syntax analysis" << std::endl;
    code = lexems;
    position = 0;
    memLoc = 0;

    program();
    if(errorMessages.size() > 0) {
        for(auto message : errorMessages) {
            std::cerr << message.second.front() << std::endl;
        }
        return -1;
    }
    return 0;
}

bool k_13::SyntaxAnalyzer::match(const LexemType expectedType) {
    if(code[position].type == expectedType) {
        position++;
        return true;
    } 
    return false;
}

void k_13::SyntaxAnalyzer::program() {
    if(code[position].type == LexemType::START) {
        position++;
        if(!match(LexemType::SEPARATOR)) {
            errorMessages[position].push_back("\t[SYN_ERROR] expected separator after code segment");
        }
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        operators();
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        if(!match(LexemType::DATA)) {
            errorMessages[position].push_back("\t[SYN_ERROR] expected .data segment");
        } else {
            if(!match(LexemType::SEPARATOR)) {
                errorMessages[position].push_back("\t[SYN_ERROR] expected separator after data segment");
            }
            while (code[position].type == LexemType::SEPARATOR) {
                position++;
            }
            data();
        }
    } else if(code[position].type == LexemType::DATA) {
        position++;
        if(!match(LexemType::SEPARATOR)) {
            errorMessages[position].push_back("\t[SYN_ERROR] expected separator after data segment");
        }
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        data();
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        if(!match(LexemType::START)) {
            errorMessages[position].push_back("\t[SYN_ERROR] expected .code segment");
        } else {
            if(!match(LexemType::SEPARATOR)) {
                errorMessages[position].push_back("\t[SYN_ERROR] expected separator after code segment");
            }
            while (code[position].type == LexemType::SEPARATOR) {
                position++;
            }
            operators();
        }
    } else {
        errorMessages[position].push_back("\t[SYN_ERROR] expected .code and .data segments");
    }
}

void k_13::SyntaxAnalyzer::data() {
    std::string name = code[position].value;
    idn.isData = true;
    for(auto &idn : identifiers) {
        if(idn.first == name) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": identifier already exists");
        }
    }
    if(!match(LexemType::IDENTIFIER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected identifier");
    }
    if(!match(LexemType::COLOMN)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected colomn");
    }
    if(!match(LexemType::NUMBER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected number");
    } else {
        int64_t numData = std::stoll(code[position - 1].value);
        if(numData > HIGH_NUM || numData < LOW_NUM) {
            std::cout << "\t[WARN] Number " + code[position - 1].value + " has more than 56-bits. Only first 56 bit will be writen, so expect loss of data" << std::endl;
        }
        idn.value = numData;
    }
    identifiers.push_back({name, idn});
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator");
    }
    while (code[position].type == LexemType::IDENTIFIER) {
        std::string name = code[position].value;
        idn.isData = true;
        for(auto &idn : identifiers) {
            if(idn.first == name) {
                errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": identifier already exists");
            }
        }
        if(!match(LexemType::IDENTIFIER)) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected identifier");
        }
        if(!match(LexemType::COLOMN)) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected colomn");
        }
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected number");
        } else {
            int64_t numData = std::stoll(code[position - 1].value);
            if(numData > HIGH_NUM || numData < LOW_NUM) {
                std::cout << "\t[WARN] Number " + code[position - 1].value + " has more than 56-bits. Only first 56 bit will be writen, so expect loss of data" << std::endl;
            }
            idn.value = numData;
        }
        identifiers.push_back({name, idn});
        if(!match(LexemType::SEPARATOR)) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator");
        }
    }
}

void k_13::SyntaxAnalyzer::operators() {
    cmd = {LexemType::UNUSED, 0, 0, 0, ""};
    while (code[position].type != LexemType::DATA && position < code.size()) {
        switch (code[position].type) {
        case LexemType::ADD:
        case LexemType::SUB:
        case LexemType::XADD:
        case LexemType::XSUB:
        case LexemType::MULT:
        case LexemType::IMULT:
        case LexemType::AND:
        case LexemType::OR:
        case LexemType::XOR:
        case LexemType::SAL:
        case LexemType::SAR:
        case LexemType::CMPEQ:
        case LexemType::ADB:
        case LexemType::SBB:
        case LexemType::RCL:
        case LexemType::RCR:
            cmd.opcode = code[position].type;
            position++;
            r3_type();
            break;
        case LexemType::LOAD_REG:
        case LexemType::SWAP:
        case LexemType::NOT:
        case LexemType::BT:
            cmd.opcode = code[position].type;
            position++;
            r2_type();
            break;
        case LexemType::INC:
        case LexemType::DEC:
            cmd.opcode = code[position].type;
            position++;
            r1_type();
            break;
        case LexemType::JMA:
        case LexemType::JMB:
        case LexemType::JMAE:
        case LexemType::JMBE:
            cmd.opcode = code[position].type;
            position++;
            i2_type();
            break;
        case LexemType::BEZ:
        case LexemType::BNZ:
        case LexemType::LOAD:
        case LexemType::STORE:
            cmd.opcode = code[position].type;
            position++;
            i1_type();
            break;
        case LexemType::JMP:
            cmd.opcode = code[position].type;
            position++;
            i0_type();
            break;
        case LexemType::HALT:
            cmd.opcode = code[position].type;
            position++;
            r0_type();
            break;
        case LexemType::SEPARATOR:
            position++;
            cmd = {LexemType::UNUSED, 0, 0, 0, ""};
            break;
        case LexemType::IDENTIFIER:
            if(code[position-1].type == LexemType::COLOMN || code[position-1].type == LexemType::IDENTIFIER) {
                errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected operand but get identifier. possible reason: misspelling");
            }
            for(auto &idn_ : identifiers) {
                if(idn_.first == code[position].value) {
                    errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": label already exists");
                    break;
                }
            }
            idn.isData = false;
            idn.memLoc = memLoc;
            identifiers.push_back({code[position].value, idn});
            position++;
            if(!match(LexemType::COLOMN)) {
                errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected colomn after label");
            }
            break;
        case LexemType::UNKNOWN:
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": unknown statement - " + code[position].value);
            position++;
            break;
        default:
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": unknown statement - " + code[position].value);
            position++;
            break;
        }
    }
}

void k_13::SyntaxAnalyzer::r3_type() {
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register rA. Current value - " + code[position].value);
    } else {
        cmd.operand1 = std::stoll(code[position-1].value);
    }
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register rB. Current value - " + code[position].value);
    } else {
        cmd.operand2 = std::stoll(code[position-1].value);
    }
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register destReg. Current value - " + code[position].value);
    } else {
        cmd.operand3 = std::stoll(code[position-1].value);
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::r2_type() {
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register rA. Current value - " + code[position].value);
    } else {
        cmd.operand1 = std::stoll(code[position-1].value);
    }
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register destReg. Current value - " + code[position].value);
    } else {
        cmd.operand2 = std::stoll(code[position-1].value);
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::r1_type() {
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register destReg. Current value - " + code[position].value);
    } else {
        cmd.operand1 = std::stoll(code[position-1].value);
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::r0_type() {
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::i2_type() {
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register rA. Current value - " + code[position].value);
    } else {
        cmd.operand1 = std::stoll(code[position-1].value);
    }
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register rB. Current value - " + code[position].value);
    } else {
        cmd.operand2 = std::stoll(code[position-1].value);
    }
    cmd.offset = code[position].value;
    if(!match(LexemType::IDENTIFIER)) {
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected label/offset. Current value - " + code[position].value);
        } else if(std::stoll(code[position - 1].value) < 0 || std::stoll(code[position - 1].value) > 33554431) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": memory location out of range. Current value - " + code[position].value);
        }
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::i1_type() {
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected register rA");
    } else {
        cmd.operand1 = std::stoll(code[position-1].value);
    }
    cmd.offset = code[position].value;
    if(!match(LexemType::IDENTIFIER)) {
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected label/offset");
        } else if(std::stoll(code[position - 1].value) < 0 || std::stoll(code[position - 1].value) > 33554431) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": memory location out of range");
        }
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator");
    }
}

void k_13::SyntaxAnalyzer::i0_type() {
    cmd.offset = code[position].value;
    if(!match(LexemType::IDENTIFIER)) {
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected label/offset");
        } else if(std::stoll(code[position - 1].value) < 0 || std::stoll(code[position - 1].value) > 33554431) {
            errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": memory location out of range");
        }
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("\t[SYN_ERROR] - " + std::to_string(code[position].line) + ": expected separator");
    }
}