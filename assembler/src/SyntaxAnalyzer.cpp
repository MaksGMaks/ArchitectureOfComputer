#include "SyntaxAnalyzer.hpp"

k_13::SyntaxAnalyzer::SyntaxAnalyzer() {
    code.clear();
    errorMessages.clear();
    cmd = {LexemType::UNUSED, LexemType::UNUSED, LexemType::UNUSED, LexemType::UNUSED};
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
            errorMessages[position].push_back("Error: expected separator");
        }
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        operators();
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        if(!match(LexemType::DATA)) {
            errorMessages[position].push_back("Error: expected .data segment");
        } else {
            if(!match(LexemType::SEPARATOR)) {
                errorMessages[position].push_back("Error: expected separator");
            }
            while (code[position].type == LexemType::SEPARATOR) {
                position++;
            }
            data();
            for(auto &idn : identifiers) {
                if(idn.second.isData) {
                    idn.second.memLoc = memLoc;
                    memLoc++;
                }
            }
        }
    } else if(code[position].type == LexemType::DATA) {
        position++;
        if(!match(LexemType::SEPARATOR)) {
            errorMessages[position].push_back("Error: expected separator");
        }
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        data();
        for(auto &idn : identifiers) {
            if(idn.second.isData) {
                idn.second.memLoc = memLoc;
                memLoc++;
            }
        }
        while (code[position].type == LexemType::SEPARATOR) {
            position++;
        }
        if(!match(LexemType::START)) {
            errorMessages[position].push_back("Error: expected .code segment");
        } else {
            if(!match(LexemType::SEPARATOR)) {
                errorMessages[position].push_back("Error: expected separator");
            }
            while (code[position].type == LexemType::SEPARATOR) {
                position++;
            }
            operators();
        }
    } else {
        errorMessages[position].push_back("Error: expected .code and .data segments");
    }
}

void k_13::SyntaxAnalyzer::data() {
    std::string name = code[position].value;
    idn.isData = true;
    if(!match(LexemType::IDENTIFIER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected identifier");
    }
    if(!match(LexemType::COLOMN)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected colomn");
    }
    if(!match(LexemType::NUMBER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected number");
    } else {
        idn.value = std::stoi(code[position - 1].value);
    }
    identifiers.insert({name, idn});
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator");
    }
    while (code[position].type == LexemType::IDENTIFIER) {
        std::string name = code[position].value;
        idn.isData = true;
        if(!match(LexemType::IDENTIFIER)) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected identifier");
        }
        if(!match(LexemType::COLOMN)) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected colomn");
        }
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected number");
        } else {
            idn.value = std::stoi(code[position - 1].value);
        }
        identifiers.insert({name, idn});
        if(!match(LexemType::SEPARATOR)) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator");
        }
    }
}

void k_13::SyntaxAnalyzer::operators() {
    cmd = {LexemType::UNUSED, LexemType::UNUSED, LexemType::UNUSED, LexemType::UNUSED};
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
            cmd = {LexemType::UNUSED, LexemType::UNUSED, LexemType::UNUSED, LexemType::UNUSED};
            break;
        case LexemType::IDENTIFIER:
            idn.isData = false;
            idn.memLoc = memLoc;
            identifiers.insert({code[position].value, idn});
            position++;
            if(!match(LexemType::COLOMN)) {
                errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected colomn after label");
            }
            break;
        case LexemType::UNKNOWN:
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": unknown statement - " + code[position].value);
            position++;
            break;
        default:
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": unknown statement - " + code[position].value);
            position++;
            break;
        }
    }
}

void k_13::SyntaxAnalyzer::r3_type() {
    cmd.operand1 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register rA. Current value - " + code[position].value);
    }
    cmd.operand2 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register rB. Current value - " + code[position].value);
    }
    cmd.operand3 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register destReg. Current value - " + code[position].value);
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::r2_type() {
    cmd.operand1 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register rA. Current value - " + code[position].value);
    }
    cmd.operand2 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register destReg. Current value - " + code[position].value);
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::r1_type() {
    cmd.operand1 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register destReg. Current value - " + code[position].value);
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::r0_type() {
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::i2_type() {
    cmd.operand1 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register rA. Current value - " + code[position].value);
    }
    cmd.operand2 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register rB. Current value - " + code[position].value);
    }
    cmd.operand3 = code[position].type;
    if(!match(LexemType::IDENTIFIER)) {
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected label/offset. Current value - " + code[position].value);
        } else if(std::stoi(code[position - 1].value) < 0 || std::stoi(code[position - 1].value) > 33554431) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": offset out of range. Current value - " + code[position].value);
        }
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator. Current value - " + code[position].value);
    }
}

void k_13::SyntaxAnalyzer::i1_type() {
    cmd.operand1 = code[position].type;
    if(!match(LexemType::REGISTER)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected register rA");
    }
    cmd.operand3 = code[position].type;
    if(!match(LexemType::IDENTIFIER)) {
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected label/offset");
        } else if(std::stoi(code[position - 1].value) < 0 || std::stoi(code[position - 1].value) > 33554431) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": offset out of range");
        }
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator");
    }
}

void k_13::SyntaxAnalyzer::i0_type() {
    cmd.operand3 = code[position].type;
    if(!match(LexemType::IDENTIFIER)) {
        if(!match(LexemType::NUMBER)) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected label/offset");
        } else if(std::stoi(code[position - 1].value) < 0 || std::stoi(code[position - 1].value) > 33554431) {
            errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": offset out of range");
        }
    }
    commands.insert({memLoc, cmd});
    memLoc++;
    if(!match(LexemType::SEPARATOR)) {
        errorMessages[position].push_back("Syntax error at line " + std::to_string(code[position].line) + ": expected separator");
    }
}