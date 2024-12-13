#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <list>

#include "constants.hpp"

namespace k_13 {
class SyntaxAnalyzer {
public:
    SyntaxAnalyzer();
    ~SyntaxAnalyzer() = default;

    int analyze(const std::vector<Lexem> &lexems);
    std::map<int, command> getCommands() { return commands; }
    std::list<std::pair<std::string, identifier>> getIdentifiers() { return identifiers; }
private:
    int errors = 0;
    int position = 0;
    int memLoc = 0;

    std::vector<Lexem> code;
    std::map<int, std::vector<std::string>> errorMessages;
    std::list<std::pair<std::string, identifier>> identifiers;

    std::map<int, command> commands;
    command cmd;
    identifier idn;

    void program();
    void operators();
    void data();

    void r3_type();
    void r2_type();
    void r1_type();
    void r0_type();

    void i2_type();
    void i1_type();
    void i0_type();

    bool match(const LexemType expectedType);

    const int64_t LOW_NUM = (36028797018963968 * -1);
    const int64_t HIGH_NUM = 36028797018963967;
};};