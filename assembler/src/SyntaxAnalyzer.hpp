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
    std::map<std::string, identifier> getIdentifiers() { return identifiers; }
private:
    int errors = 0;
    int position = 0;
    int memLoc = 0;

    std::vector<Lexem> code;
    std::map<int, std::vector<std::string>> errorMessages;
    std::map<std::string, identifier> identifiers;

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
};};