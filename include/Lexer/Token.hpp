#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

enum class TokenType {
    EOL,
    EOT,
    NUL,
    ECHO,
    INTEGER,
    IDENTIFIER,
    ASS,
    UNARY_OP,
    BIN_OP,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    IF,
    ELSE,
    WHILE,
};

struct Token {
    TokenType type;
    std::string value;

    std::string toString();
};

#endif