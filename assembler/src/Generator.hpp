#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <bitset>

#include "constants.hpp"

namespace k_13 {
class Generator {
public:
    Generator();
    ~Generator() = default;

    int generate(const std::map<int, command> &commands_, const std::list<std::pair<std::string, identifier>> &identifiers_);
    std::vector<std::bitset<56>> getBinaryCode() { return binaryCode; }
private:
    bool identifierExist(const std::string &name);
    bool findOffset(int64_t &operand, const std::string &name, const int &PC);

    int64_t r3_type(const int64_t &opcode, const int64_t &operand1, const int64_t &operand2, const int64_t &operand3);
    int64_t r2_type(const int64_t &opcode, const int64_t &operand1, const int64_t &operand2);
    int64_t r1_type(const int64_t &opcode, const int64_t &operand1);

    std::map<int, command> commands;
    std::list<std::pair<std::string, identifier>> identifiers;

    std::vector<std::bitset<56>> binaryCode;
};};