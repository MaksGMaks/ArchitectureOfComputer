#include <iostream>
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "Generator.hpp"
#include <filesystem>

void writeLexems(const std::vector<k_13::Lexem> &lexems);

std::string findDistance(const int maxSize, const std::string &lexems);

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
        writeLexems(lexic.getLexems());
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

void writeLexems(const std::vector<k_13::Lexem> &lexems) {
    k_13::constants_k13 constants;
    std::filesystem::path outputFile = std::filesystem::current_path() / "allLexems.txt";
    std::ofstream file(outputFile);
    if(file.is_open()) {
        file << "|----------------------------------------------------------------------------------------|\n";
        file << "|                                     Lexems table                                       |\n";
        file << "|----------------------------------------------------------------------------------------|\n";
        file << "|   line number  |     lexem     |     value     |  lexem code  |     type of lexem      |\n";
        file << "|----------------------------------------------------------------------------------------|\n";
        for(auto lexem : lexems) {
            file << "|\t" << lexem.line <<  findDistance(14, std::to_string(lexem.line)) << " |\t" << lexem.value << findDistance(10, lexem.value) << "\t |\t" << static_cast<std::underlying_type_t<k_13::LexemType>>(lexem.type) << " \t|\t" ;
            for(auto &enumToString : constants.enumToStringLexems) {
                if(lexem.type == enumToString.first) {
                    file << enumToString.second << findDistance(18, enumToString.second) << " |\n";
                    break;
                }
            }
            file << "|----------------------------------------------------------------------------------------|\n";
        }
        file.close();
    }
}
std::string findDistance(const int maxSize, const std::string &lexems) {
    int length = maxSize - (lexems.length() - (lexems.length() % 8));
    std::string distance = "";
    int tabs = length / 8;
    for(int i = 0; i < tabs; i++) {
        distance += "\t";
    }
    return distance;
}