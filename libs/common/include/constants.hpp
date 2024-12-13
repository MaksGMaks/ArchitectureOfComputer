#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <cstdint>

namespace k_13 {
    enum class State {
        START,              // start of extracting the next lexeme
        FINISH,             // end of extracting the next lexeme
        LETTER,             // processing words (keywords and identifiers)
        DIGIT,              // processing digits
        REGISTER,           // processing registers
        SPECIALKEYWORD,     // processing special keywords
        SEPARATORS,         // removing spaces, tab characters, and new line characters
        ANOTHER,            // processing other characters
        END_OF_FILE,        // end of file
        COMMENT             // start of comment
    };

    enum class LexemType {
        LOAD,              // load
        STORE,             // store
        LOAD_REG,          // load register
        SWAP,              // swap

        ADD,               // add
        SUB,               // subtract
        XADD,              // add and swap
        XSUB,              // subtract and swap
        MULT,              // multiply (unsigned)
        IMULT,             // multiply (signed)
        INC,               // increment
        DEC,               // decrement

        AND,               // bitwise AND
        OR,                // bitwise OR
        XOR,               // bitwise XOR
        NOT,               // bitwise NOT
        SAL,               // shift left arithmetic
        SAR,               // shift right arithmetic
        CMPEQ,             // compare equal

        BT,                // bit load
        ADB,               // add with carry
        SBB,               // subtract with borrow
        RCL,               // rotate left through carry
        RCR,               // rotate right through carry

        BEZ,               // branch if equal zero
        BNZ,               // branch if not equal zero
        JMA,               // jump if A > B
        JMB,               // jump if A < B
        JMAE,              // jump if A >= B
        JMBE,              // jump if A <= B
        JMP,               // jump
        HALT,              // halt

        IDENTIFIER,         // identifier
        NUMBER,             // number
        REGISTER,           // register
        SEPARATOR,          // separator
        DATA,               // data
        START,              // start
        COLOMN,             // colomn

        UNKNOWN,            // unknown
        UNDEFINED,          // undefined

        UNUSED              // unused
    };

    struct Lexem {
        LexemType type{};
        std::string value{};
        int line{};
    };

    struct command {
        LexemType opcode{};
        int operand1{};
        int operand2{};
        int operand3{};
        std::string offset{};
    };

    struct identifier {
        int memLoc{};
        bool isData{};
        int64_t value{};
    };

    struct constants_k13
    {
        std::map<std::string, LexemType> keywords_k13 = {
            {"lw", LexemType::LOAD},
            {"sw", LexemType::STORE},
            {"lr", LexemType::LOAD_REG},
            {"swp", LexemType::SWAP},

            {"add", LexemType::ADD},
            {"sub", LexemType::SUB},
            {"xadd", LexemType::XADD},
            {"xsub", LexemType::XSUB},
            {"mul", LexemType::MULT},
            {"imul", LexemType::IMULT},
            {"inc", LexemType::INC},
            {"dec", LexemType::DEC},

            {"and", LexemType::AND},
            {"or", LexemType::OR},
            {"xor", LexemType::XOR},
            {"not", LexemType::NOT},
            {"sal", LexemType::SAL},
            {"sar", LexemType::SAR},
            {"cmpe", LexemType::CMPEQ},

            {"bt", LexemType::BT},
            {"adb", LexemType::ADB},
            {"sbb", LexemType::SBB},
            {"rcl", LexemType::RCL},
            {"rcr", LexemType::RCR},

            {"bez", LexemType::BEZ},
            {"bnz", LexemType::BNZ},
            {"jma", LexemType::JMA},
            {"jmb", LexemType::JMB},
            {"jmae", LexemType::JMAE},
            {"jmbe", LexemType::JMBE},
            {"jmp", LexemType::JMP},
            {"halt", LexemType::HALT}
        };

        std::map<std::string, LexemType> specialKeywords = {
            {".data", LexemType::DATA},
            {".start", LexemType::START},
            {".code", LexemType::START}
        };

        std::map<LexemType, std::string> enumToStringLexems = {
            {LexemType::LOAD, "LOAD"},
            {LexemType::STORE, "STORE"},
            {LexemType::LOAD_REG, "LOAD_REG"},
            {LexemType::SWAP, "SWAP"},
            {LexemType::ADD, "ADD"},
            {LexemType::SUB, "SUB"},
            {LexemType::XADD, "XADD"},
            {LexemType::XSUB, "XSUB"},
            {LexemType::MULT, "MULT"},
            {LexemType::IMULT, "IMULT"},
            {LexemType::INC, "INC"},
            {LexemType::DEC, "DEC"},
            {LexemType::AND, "AND"},
            {LexemType::OR, "OR"},
            {LexemType::XOR, "XOR"},
            {LexemType::NOT, "NOT"},
            {LexemType::SAL, "SAL"},
            {LexemType::SAR, "SAR"},
            {LexemType::CMPEQ, "CMPEQ"},
            {LexemType::BT, "BT"},
            {LexemType::ADB, "ADB"},
            {LexemType::SBB, "SBB"},
            {LexemType::RCL, "RCL"},
            {LexemType::RCR, "RCR"},
            {LexemType::BEZ, "BEZ"},
            {LexemType::BNZ, "BNZ"},
            {LexemType::JMA, "JMA"},
            {LexemType::JMB, "JMB"},
            {LexemType::JMAE, "JMAE"},
            {LexemType::JMBE, "JMBE"},
            {LexemType::JMP, "JMP"},
            {LexemType::HALT, "HALT"},
            {LexemType::IDENTIFIER, "IDENTIFIER"},
            {LexemType::NUMBER, "NUMBER"},
            {LexemType::REGISTER, "REGISTER"},
            {LexemType::SEPARATOR, "SEPARATOR"},
            {LexemType::DATA, "DATA"},
            {LexemType::START, "START"},
            {LexemType::COLOMN, "COLOMN"},
            {LexemType::UNKNOWN, "UNKNOWN"},
            {LexemType::UNDEFINED, "UNDEFINED"}
        };
    };
}