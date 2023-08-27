#include <fstream>
#include <sstream>
#include "Lexer/Tokenizer.hpp"
#include "Error/ErrorHandler.hpp"

Tokenizer::Tokenizer(std::string &filePath) {
    this->filePath = filePath;
}

std::vector<Token> Tokenizer::generateTokens() {
    std::ifstream srcFile(filePath);

    while(std::getline(srcFile, currentLine)) {
        generateLineTokens();
    }
    srcFile.close();
    tokens.emplace_back(Token{TokenType::EOT});
    return tokens;
}

void Tokenizer::generateLineTokens() {
    currentCharIndex = 0;

    while(currentChar()[0] != 0) {
        // skippable characters
        if(currentChar() == " " || currentChar() == "\t" || currentChar() == "\n") {
            currentCharAndAdvance();
        }

        // comment
        else if(currentChar() == "#") {
            break;
        }
        


        // assignment and equal operator
        else if(currentChar() == "=") {
            if(nextChar() == "=") {
                tokens.emplace_back(Token{TokenType::BIN_OP, "=="});
                currentCharAndAdvance();
                currentCharAndAdvance();
            }
            else {
                tokens.emplace_back(Token{TokenType::ASS});
                currentCharAndAdvance();
            }
        }



        // binary operators
        else if(currentChar() == "+" || currentChar() == "-" || currentChar() == "*" || currentChar() == "/") {
            tokens.emplace_back(Token{TokenType::BIN_OP, currentCharAndAdvance()});
        }
        else if(currentChar() == "<") {
            if(nextChar() == "=") {
                tokens.emplace_back(Token{TokenType::BIN_OP, "<="});
                currentCharAndAdvance();
                currentCharAndAdvance();
            }
            else {
                tokens.emplace_back(Token{TokenType::BIN_OP, "<"});
                currentCharAndAdvance();
            }
        }
        else if(currentChar() == ">") {
            if(nextChar() == "=") {
                tokens.emplace_back(Token{TokenType::BIN_OP, ">="});
                currentCharAndAdvance();
                currentCharAndAdvance();
            }
            else {
                tokens.emplace_back(Token{TokenType::BIN_OP, ">"});
                currentCharAndAdvance();
            }
        }
        else if(currentChar() == "!") {
            if(nextChar() == "=") {
                tokens.emplace_back(Token{TokenType::BIN_OP, "!="});
                currentCharAndAdvance();
                currentCharAndAdvance();
            }
            else {
                ErrorHandler::handleError(new IllegalCharError(currentChar()));
            }
        }



        // punctuations
        else if(currentChar() == "(") {
            tokens.emplace_back(Token{TokenType::LPAREN});
            currentCharAndAdvance();
        }
        else if(currentChar() == ")") {
            tokens.emplace_back(Token{TokenType::RPAREN});
            currentCharAndAdvance();
        }
        else if(currentChar() == "{") {
            tokens.emplace_back(Token{TokenType::LBRACE});
            currentCharAndAdvance();
        }
        else if(currentChar() == "}") {
            tokens.emplace_back(Token{TokenType::RBRACE});
            currentCharAndAdvance();
        }



        // numbers
        else if(currentChar()[0] >= 48 && currentChar()[0] <= 57) {
            std::string num;
            num += currentCharAndAdvance();
            while(currentChar()[0] >= 48 && currentChar()[0] <= 57) {
                num += currentCharAndAdvance();
            }
            tokens.emplace_back(Token{TokenType::INTEGER, num});
        }



        // words
        else if((currentChar()[0] >= 65 && currentChar()[0] <= 90) || (currentChar()[0] >= 97 && currentChar()[0] <= 122)) {
            std::string word;
            word += currentCharAndAdvance();
            while((currentChar()[0] >= 65 && currentChar()[0] <= 90) || (currentChar()[0] >= 97 && currentChar()[0] <= 122)) {
                word += currentCharAndAdvance();
            }

            Token keyToken = getKeyword(word);
            if(keyToken.type != TokenType::EOL) {
                tokens.emplace_back(keyToken);
            }
            else {
                tokens.emplace_back(Token{TokenType::IDENTIFIER, word});
            }
        }

        else {
            ErrorHandler::handleError(new IllegalCharError(currentChar()));
        }
    }
    tokens.emplace_back(Token{TokenType::EOL});
}





Token Tokenizer::getKeyword(std::string &word) {
    if(word == "null") {
        return Token{TokenType::NUL};
    }
    else if(word == "echo") {
        return Token{TokenType::ECHO};
    }
    else if(word == "if") {
        return Token{TokenType::IF};
    }
    else if(word == "else") {
        return Token{TokenType::ELSE};
    }
    else if(word == "while") {
        return Token{TokenType::WHILE};
    }
    else {
        return Token{TokenType::EOL};
    }
}





std::string Tokenizer::currentChar() {
    if(currentCharIndex >= currentLine.size()) {
        return std::string(1, 0);
    }
    return std::string(1, currentLine[currentCharIndex]);
}
std::string Tokenizer::currentCharAndAdvance() {
    if(currentCharIndex >= currentLine.size()) {
        return std::string(1, 0);
    }
    char c = currentLine[currentCharIndex];
    ++currentCharIndex;
    return std::string(1, c);
}
std::string Tokenizer::nextChar() {
    int nextCharIndex = currentCharIndex + 1;
    if(nextCharIndex >= currentLine.size()) {
        return std::string(1, 0);
    }
    return std::string(1, currentLine[nextCharIndex]);
}