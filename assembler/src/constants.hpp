#pragma once
#include <string>
#include <unordered_map>
#include <map>

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
        COMMENT          // start of comment
    };

    enum class Registers {
        REG0, REG1, REG2, REG3, REG4, REG5, REG6, REG7,
        REG8, REG9, REG10, REG11, REG12, REG13, REG14, REG15,
        REG16, REG17, REG18, REG19, REG20, REG21, REG22, REG23,
        REG24, REG25, REG26, REG27, REG28, REG29, REG30, REG31,
        REG32, REG33, REG34, REG35, REG36, REG37, REG38, REG39,
        REG40, REG41, REG42, REG43, REG44, REG45, REG46, REG47,
        REG48, REG49, REG50, REG51, REG52, REG53, REG54, REG55,
        REG56, REG57, REG58, REG59, REG60, REG61, REG62, REG63,
        REG64, REG65, REG66, REG67, REG68, REG69, REG70, REG71,
        REG72, REG73, REG74, REG75, REG76, REG77, REG78, REG79,
        REG80, REG81, REG82, REG83, REG84, REG85, REG86, REG87,
        REG88, REG89, REG90, REG91, REG92, REG93, REG94, REG95,
        REG96, REG97, REG98, REG99, REG100, REG101, REG102, REG103,
        REG104, REG105, REG106, REG107, REG108, REG109, REG110, REG111,
        REG112, REG113, REG114, REG115, REG116, REG117, REG118, REG119,
        REG120, REG121, REG122, REG123, REG124, REG125, REG126, REG127
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
        LexemType operand1{};
        LexemType operand2{};
        LexemType operand3{};
    };

    struct identifier {
        int memLoc{};
        bool isData{};
        int value{};
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

        std::map<std::string, Registers> registers = {
            {"r0", Registers::REG0},
            {"r1", Registers::REG1},
            {"r2", Registers::REG2},
            {"r3", Registers::REG3},
            {"r4", Registers::REG4},
            {"r5", Registers::REG5},
            {"r6", Registers::REG6},
            {"r7", Registers::REG7},
            {"r8", Registers::REG8},
            {"r9", Registers::REG9},
            {"r10", Registers::REG10},
            {"r11", Registers::REG11},
            {"r12", Registers::REG12},
            {"r13", Registers::REG13},
            {"r14", Registers::REG14},
            {"r15", Registers::REG15},
            {"r16", Registers::REG16},
            {"r17", Registers::REG17},
            {"r18", Registers::REG18},
            {"r19", Registers::REG19},
            {"r20", Registers::REG20},
            {"r21", Registers::REG21},
            {"r22", Registers::REG22},
            {"r23", Registers::REG23},
            {"r24", Registers::REG24},
            {"r25", Registers::REG25},
            {"r26", Registers::REG26},
            {"r27", Registers::REG27},
            {"r28", Registers::REG28},
            {"r29", Registers::REG29},
            {"r30", Registers::REG30},
            {"r31", Registers::REG31},
            {"r32", Registers::REG32},
            {"r33", Registers::REG33},
            {"r34", Registers::REG34},
            {"r35", Registers::REG35},
            {"r36", Registers::REG36},
            {"r37", Registers::REG37},
            {"r38", Registers::REG38},
            {"r39", Registers::REG39},
            {"r40", Registers::REG40},
            {"r41", Registers::REG41},
            {"r42", Registers::REG42},
            {"r43", Registers::REG43},
            {"r44", Registers::REG44},
            {"r45", Registers::REG45},
            {"r46", Registers::REG46},
            {"r47", Registers::REG47},
            {"r48", Registers::REG48},
            {"r49", Registers::REG49},
            {"r50", Registers::REG50},
            {"r51", Registers::REG51},
            {"r52", Registers::REG52},
            {"r53", Registers::REG53},
            {"r54", Registers::REG54},
            {"r55", Registers::REG55},
            {"r56", Registers::REG56},
            {"r57", Registers::REG57},
            {"r58", Registers::REG58},
            {"r59", Registers::REG59},
            {"r60", Registers::REG60},
            {"r61", Registers::REG61},
            {"r62", Registers::REG62},
            {"r63", Registers::REG63},
            {"r64", Registers::REG64},
            {"r65", Registers::REG65},
            {"r66", Registers::REG66},
            {"r67", Registers::REG67},
            {"r68", Registers::REG68},
            {"r69", Registers::REG69},
            {"r70", Registers::REG70},
            {"r71", Registers::REG71},
            {"r72", Registers::REG72},
            {"r73", Registers::REG73},
            {"r74", Registers::REG74},
            {"r75", Registers::REG75},
            {"r76", Registers::REG76},
            {"r77", Registers::REG77},
            {"r78", Registers::REG78},
            {"r79", Registers::REG79},
            {"r80", Registers::REG80},
            {"r81", Registers::REG81},
            {"r82", Registers::REG82},
            {"r83", Registers::REG83},
            {"r84", Registers::REG84},
            {"r85", Registers::REG85},
            {"r86", Registers::REG86},
            {"r87", Registers::REG87},
            {"r88", Registers::REG88},
            {"r89", Registers::REG89},
            {"r90", Registers::REG90},
            {"r91", Registers::REG91},
            {"r92", Registers::REG92},
            {"r93", Registers::REG93},
            {"r94", Registers::REG94},
            {"r95", Registers::REG95},
            {"r96", Registers::REG96},
            {"r97", Registers::REG97},
            {"r98", Registers::REG98},
            {"r99", Registers::REG99},
            {"r100", Registers::REG100},
            {"r101", Registers::REG101},
            {"r102", Registers::REG102},
            {"r103", Registers::REG103},
            {"r104", Registers::REG104},
            {"r105", Registers::REG105},
            {"r106", Registers::REG106},
            {"r107", Registers::REG107},
            {"r108", Registers::REG108},
            {"r109", Registers::REG109},
            {"r110", Registers::REG110},
            {"r111", Registers::REG111},
            {"r112", Registers::REG112},
            {"r113", Registers::REG113},
            {"r114", Registers::REG114},
            {"r115", Registers::REG115},
            {"r116", Registers::REG116},
            {"r117", Registers::REG117},
            {"r118", Registers::REG118},
            {"r119", Registers::REG119},
            {"r120", Registers::REG120},
            {"r121", Registers::REG121},
            {"r122", Registers::REG122},
            {"r123", Registers::REG123},
            {"r124", Registers::REG124},
            {"r125", Registers::REG125},
            {"r126", Registers::REG126},
            {"r127", Registers::REG127}
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

        std::map<Registers, std::string> enumRegsToString = {
            {Registers::REG0, "REG0"},
            {Registers::REG1, "REG1"},
            {Registers::REG2, "REG2"},
            {Registers::REG3, "REG3"},
            {Registers::REG4, "REG4"},
            {Registers::REG5, "REG5"},
            {Registers::REG6, "REG6"},
            {Registers::REG7, "REG7"},
            {Registers::REG8, "REG8"},
            {Registers::REG9, "REG9"},
            {Registers::REG10, "REG10"},
            {Registers::REG11, "REG11"},
            {Registers::REG12, "REG12"},
            {Registers::REG13, "REG13"},
            {Registers::REG14, "REG14"},
            {Registers::REG15, "REG15"},
            {Registers::REG16, "REG16"},
            {Registers::REG17, "REG17"},
            {Registers::REG18, "REG18"},
            {Registers::REG19, "REG19"},
            {Registers::REG20, "REG20"},
            {Registers::REG21, "REG21"},
            {Registers::REG22, "REG22"},
            {Registers::REG23, "REG23"},
            {Registers::REG24, "REG24"},
            {Registers::REG25, "REG25"},
            {Registers::REG26, "REG26"},
            {Registers::REG27, "REG27"},
            {Registers::REG28, "REG28"},
            {Registers::REG29, "REG29"},
            {Registers::REG30, "REG30"},
            {Registers::REG31, "REG31"},
            {Registers::REG32, "REG32"},
            {Registers::REG33, "REG33"},
            {Registers::REG34, "REG34"},
            {Registers::REG35, "REG35"},
            {Registers::REG36, "REG36"},
            {Registers::REG37, "REG37"},
            {Registers::REG38, "REG38"},
            {Registers::REG39, "REG39"},
            {Registers::REG40, "REG40"},
            {Registers::REG41, "REG41"},
            {Registers::REG42, "REG42"},
            {Registers::REG43, "REG43"},
            {Registers::REG44, "REG44"},
            {Registers::REG45, "REG45"},
            {Registers::REG46, "REG46"},
            {Registers::REG47, "REG47"},
            {Registers::REG48, "REG48"},
            {Registers::REG49, "REG49"},
            {Registers::REG50, "REG50"},
            {Registers::REG51, "REG51"},
            {Registers::REG52, "REG52"},
            {Registers::REG53, "REG53"},
            {Registers::REG54, "REG54"},
            {Registers::REG55, "REG55"},
            {Registers::REG56, "REG56"},
            {Registers::REG57, "REG57"},
            {Registers::REG58, "REG58"},
            {Registers::REG59, "REG59"},
            {Registers::REG60, "REG60"},
            {Registers::REG61, "REG61"},
            {Registers::REG62, "REG62"},
            {Registers::REG63, "REG63"},
            {Registers::REG64, "REG64"},
            {Registers::REG65, "REG65"},
            {Registers::REG66, "REG66"},
            {Registers::REG67, "REG67"},
            {Registers::REG68, "REG68"},
            {Registers::REG69, "REG69"},
            {Registers::REG70, "REG70"},
            {Registers::REG71, "REG71"},
            {Registers::REG72, "REG72"},
            {Registers::REG73, "REG73"},
            {Registers::REG74, "REG74"},
            {Registers::REG75, "REG75"},
            {Registers::REG76, "REG76"},
            {Registers::REG77, "REG77"},
            {Registers::REG78, "REG78"},
            {Registers::REG79, "REG79"},
            {Registers::REG80, "REG80"},
            {Registers::REG81, "REG81"},
            {Registers::REG82, "REG82"},
            {Registers::REG83, "REG83"},
            {Registers::REG84, "REG84"},
            {Registers::REG85, "REG85"},
            {Registers::REG86, "REG86"},
            {Registers::REG87, "REG87"},
            {Registers::REG88, "REG88"},
            {Registers::REG89, "REG89"},
            {Registers::REG90, "REG90"},
            {Registers::REG91, "REG91"},
            {Registers::REG92, "REG92"},
            {Registers::REG93, "REG93"},
            {Registers::REG94, "REG94"},
            {Registers::REG95, "REG95"},
            {Registers::REG96, "REG96"},
            {Registers::REG97, "REG97"},
            {Registers::REG98, "REG98"},
            {Registers::REG99, "REG99"},
            {Registers::REG100, "REG100"},
            {Registers::REG101, "REG101"},
            {Registers::REG102, "REG102"},
            {Registers::REG103, "REG103"},
            {Registers::REG104, "REG104"},
            {Registers::REG105, "REG105"},
            {Registers::REG106, "REG106"},
            {Registers::REG107, "REG107"},
            {Registers::REG108, "REG108"},
            {Registers::REG109, "REG109"},
            {Registers::REG110, "REG110"},
            {Registers::REG111, "REG111"},
            {Registers::REG112, "REG112"},
            {Registers::REG113, "REG113"},
            {Registers::REG114, "REG114"},
            {Registers::REG115, "REG115"},
            {Registers::REG116, "REG116"},
            {Registers::REG117, "REG117"},
            {Registers::REG118, "REG118"},
            {Registers::REG119, "REG119"},
            {Registers::REG120, "REG120"},
            {Registers::REG121, "REG121"},
            {Registers::REG122, "REG122"},
            {Registers::REG123, "REG123"},
            {Registers::REG124, "REG124"},
            {Registers::REG125, "REG125"},
            {Registers::REG126, "REG126"},
            {Registers::REG127, "REG127"}
        };
    };
}