#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <vector>
#include <string>

#include "Token.hpp"

class Tokenizer {
private:
    std::vector<Token> tokens;
    std::string filePath;

    std::string currentLine;
    int currentCharIndex = 0;

    std::string currentChar();
    std::string currentCharAndAdvance();
    std::string nextChar();

    Token getKeyword(const std::string &word);

    void generateLineTokens();

public:
    Tokenizer(const std::string &filePath);
    std::vector<Token> generateTokens();
};

#endif