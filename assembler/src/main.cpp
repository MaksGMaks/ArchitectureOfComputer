#include <iostream>
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "Generator.hpp"
#include <filesystem>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: input path to file for compilation" << std::endl;
        return -1;
    }
    if(argc != 3) {
        std::cerr << "Error: input path to output file" << std::endl;
        return -1;
    }
    std::string inpPath = argv[1];
    std::string outPath = argv[2];
    std::ofstream out(outPath);

    k_13::LexicalAnalyzer lexic;
    k_13::SyntaxAnalyzer syntax;
    k_13::Generator generator;

    int lexicalAnalysStatus = lexic.readFromFile(inpPath);
    int syntaxAnalysStatus;
    int generatorStatus;

    int memoryAdr = 0;
    int64_t memoryVal = 0;

    switch (lexicalAnalysStatus) {
    case 0:
        std::cout << "[INFO] Done\n";
        syntaxAnalysStatus = syntax.analyze(lexic.getLexems());
        switch (syntaxAnalysStatus) {
        case 0:
            std::cout << "[INFO] Syntax analysis done" << std::endl;
            generatorStatus = generator.generate(syntax.getCommands(), syntax.getIdentifiers());
            switch (generatorStatus) {
            case 0:
                std::cout << "[INFO] Binary code generated" << std::endl;
                if(out.is_open()) {
                    for(auto &code : generator.getBinaryCode()) {
                        out << code << std::endl;
                    }
                } else {
                    std::cerr << "[ERROR] Can't open file for writing" << std::endl;
                }
                break;
            case -1:
                std::cout << "[INFO] Generator error" << std::endl;
                break;
            default:
                break;
            }   
            break;
        case -1:
            std::cout << "[INFO] Syntax errors found. Build failed" << std::endl;
            break;
        default:
            break;
        }
        break;
    case -1:
        std::cout << "Wrong file type. Require .asm\n";
        break;
    case -2:
        std::cout << "Can't reach file with path: " << inpPath << std::endl;
        break;
    default:
        break;
    }
    return 0;
}