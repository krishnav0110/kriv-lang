#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>

#include "Token.hpp"
#include "Node.hpp"

class Parser {
private:
    std::vector<Token> tokens;
    int currentTokenIndex = 0;

    Token currentToken();
    Token currentTokenAndAdvance();
    Token nextToken();
    void expectToken(TokenType type, const std::string &err);
    
public:
    Parser(const std::vector<Token> &tokens);

    Node* parse();
    Node* parse_expr();
    Node* parse_assign_expr();
    Node* parse_if_expr();
    Node* parse_while_expr();
    Node* parse_compare_expr();
    Node* parse_additive_expr();
    Node* parse_multiplicative_expr();
    Node* parse_primary_expr();
};

#endif