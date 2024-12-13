#include "LexicalAnalyzer.hpp"

k_13::LexicalAnalyzer::LexicalAnalyzer() {
    isEndOfFile = false;
    literalId = 0;
    unknownId = 0;
}

const std::vector<k_13::Lexem> k_13::LexicalAnalyzer::getLexems() {
    return lexems;
}

int k_13::LexicalAnalyzer::readFromFile(const std::string &filename) {
    if(filename.find(".asm") != filename.length() - 4) {
        return -1;
    }
    std::ifstream file(filename);
    if(!file.is_open()) {
        return -2;
    }
    
    std::thread getTockenType(&LexicalAnalyzer::sortToken, this);

    State state = State::START;
    isEndOfFile = false;
    char ch, nch{};
    std::string buffer{}, rBuffer{};
    std::pair<std::pair<std::string, int>, LexemType> token{};
    int line = 1;
    LexemType type;
    int length = 0;
    
    if(!lexems.empty())
        lexems.clear();

    file.get(ch);

    std::cout << "[INFO] Start lexic analysis" << std::endl;
    while (1) {
        switch (state) {
        case State::START:
            if (file.eof())
                state = State::END_OF_FILE;
            else if(ch == '.')
                state = State::SPECIALKEYWORD; 
            else if (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A')
                state = State::LETTER;
            else if (ch <= '9' && ch >= '0')
                state = State::DIGIT;
            else if (ch == ' ' || ch == '\t' || ch == '\n')
                state = State::SEPARATORS;
            else if (ch == ';')
                state = State::COMMENT;
            else
                state = State::ANOTHER;
            break;
            
        case State::FINISH:
            if (!file.eof())
                state = State::START;
            else
                state = State::END_OF_FILE;
            break;

        case State::END_OF_FILE:
            {
                std::unique_lock<std::mutex> lock(mtx);
                isEndOfFile = true;
                getToken.notify_one();
            }
            if(getTockenType.joinable()) {
                getTockenType.join();
            }
            return 0;
            break;

        case State::REGISTER:
            rBuffer = "";
            for(int i = 1; i < buffer.size(); i++) {
                rBuffer += buffer[i];
            }
            
            if(std::stoi(rBuffer) > 127) {
                token = std::make_pair(std::make_pair(("r" + rBuffer), line), LexemType::UNKNOWN);
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    inputLexems.push(token);
                    getToken.notify_one();
                }
                state = State::FINISH;
                break;
            }
            token = std::make_pair(std::make_pair((rBuffer), line), LexemType::REGISTER);
            {
                std::unique_lock<std::mutex> lock(mtx);
                inputLexems.push(token);
                getToken.notify_one();
            }
            state = State::FINISH;
            break;
        
        case State::SPECIALKEYWORD:
            buffer = ch;
            file.get(ch);
            while (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A') {
                buffer += ch;
                file.get(ch);
                if(file.eof())
                    break;
            }
            token = std::make_pair(std::make_pair(buffer, line), LexemType::UNDEFINED);
            {
                std::unique_lock<std::mutex> lock(mtx);
                inputLexems.push(token);
                getToken.notify_one();
            }
            state = State::FINISH;
            break;
        case State::LETTER:
            buffer = ch;
            file.get(ch);
            while (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A' || ch <= '9' && ch >= '0' || ch == '_') {
                buffer += ch;
                file.get(ch);
            }
            if(buffer[0] == 'r' || buffer[0] == 'R') {
                if(buffer.size() < 5 && buffer.size() > 1) {
                    if(buffer[1] <= '9' && buffer[1] >= '0'){
                        state = State::REGISTER;
                        break;
                    }
                }
            }
            
            token = std::make_pair(std::make_pair(buffer, line), LexemType::UNDEFINED);
            {
                std::unique_lock<std::mutex> lock(mtx);
                inputLexems.push(token);
                getToken.notify_one();
            }
            state = State::FINISH;
            break;

        case State::DIGIT:
            if(buffer != "-")
                buffer = ch;
            else
                buffer += ch;
            file.get(ch);
            while (ch <= '9' && ch >= '0' && !file.eof()) {
                buffer += ch;
                file.get(ch);
            }
            token = std::make_pair(std::make_pair(buffer, line), LexemType::NUMBER);
            {
                std::unique_lock<std::mutex> lock(mtx);
                inputLexems.push(token);
                getToken.notify_one();
            }
            state = State::FINISH;
            break;

        case State::SEPARATORS:
            if (ch == '\n') {
                line++;
                token = std::make_pair(std::make_pair(std::string(1, ch), line), LexemType::SEPARATOR);
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    inputLexems.push(token);
                    getToken.notify_one();
                }
            }
            file.get(ch);
            state = State::FINISH;
            break;

        case State::COMMENT:
            while (ch != '\n' && !file.eof()) {
                file.get(ch);
            }
            if (file.eof()) {
                state = State::END_OF_FILE;
                break;
            }
            line++;
            file.get(ch);
            state = State::FINISH;
            break;
        case State::ANOTHER:
            if(ch == ':') {
                token = std::make_pair(std::make_pair(std::string(1, ch), line), LexemType::COLOMN);
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    inputLexems.push(token);
                    getToken.notify_one();
                }
                file.get(ch);
                state = State::FINISH;
                break;
            }
            if(ch == '-') {
                nch = file.peek();
                if(nch >= '0' && nch <= '9' && !file.eof()) {
                    buffer = ch;
                    file.get(ch);
                    state = State::DIGIT;
                    break;
                } else {
                    token = std::make_pair(std::make_pair(std::string(1, ch), line), LexemType::UNKNOWN);
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        inputLexems.push(token);
                        getToken.notify_one();
                    }
                    file.get(ch);
                    state = State::FINISH;
                    break;
                }
            }
        default:
            token = std::make_pair(std::make_pair(std::string(1, ch), line), LexemType::UNKNOWN);
            {
                std::unique_lock<std::mutex> lock(mtx);
                inputLexems.push(token);
                getToken.notify_one();
            }
            file.get(ch);
            state = State::FINISH;
            break;
        }
    }
}

void k_13::LexicalAnalyzer::checkLexem(int tokenLine, std::string token) {
    for(auto &specialKeyword : constants.specialKeywords) {
        if(specialKeyword.first == token) {
            lexems.push_back({specialKeyword.second, token, tokenLine});
            return;
        }
    }
    if(token.size() > 4 && token.size() < 12) {
        lexems.push_back({LexemType::IDENTIFIER, token, tokenLine});
        return;
    }
    else if(token.size() < 5) {
        std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c) { return std::tolower(c); });
        for(auto &keyword : constants.keywords_k13) {
            if(keyword.first == token) {
                lexems.push_back({keyword.second, token, tokenLine});
                return;
            }
        }
        lexems.push_back({LexemType::IDENTIFIER, token, tokenLine});
        return;
    } else {
        lexems.push_back({LexemType::UNKNOWN, token, tokenLine});
        return;
    }
}

void k_13::LexicalAnalyzer::sortToken() {
    while (!isEndOfFile || !inputLexems.empty()) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            if(inputLexems.empty()) {
                getToken.wait(lock);
            }
        }
        if(isEndOfFile && inputLexems.empty()) {
            return;
        }
        std::string token{};
            int tokenLine{};
            LexemType type{};
            {
                std::unique_lock<std::mutex> lock(mtx);
                token = inputLexems.front().first.first;
                tokenLine = inputLexems.front().first.second;
                type = inputLexems.front().second;
                inputLexems.pop();
            }
            switch (type) {
            case LexemType::REGISTER:
                lexems.push_back({LexemType::REGISTER, token, tokenLine});
                break;
            case LexemType::SEPARATOR:
                lexems.push_back({LexemType::SEPARATOR, token, tokenLine});
                break;
            case LexemType::COLOMN:
                lexems.push_back({LexemType::COLOMN, token, tokenLine});
                break;
            case LexemType::NUMBER:
                lexems.push_back({LexemType::NUMBER, token, tokenLine});
                break;
            case LexemType::UNKNOWN:
                lexems.push_back({LexemType::UNKNOWN, token, tokenLine});
                break;
            case LexemType::UNDEFINED:
                checkLexem(tokenLine, token);
                break;
            default:
                checkLexem(tokenLine, token);
                break;
            }
    }
}
