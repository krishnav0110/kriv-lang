#include <iostream>
#include "Parser/Parser.hpp"
#include "Error/ErrorHandler.hpp"

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;
}





Token Parser::currentToken() {
    return tokens[currentTokenIndex];
}
Token Parser::currentTokenAndAdvance() {
    Token token = tokens[currentTokenIndex];
    if(token.type != TokenType::EOT) {
        ++currentTokenIndex;
    }
    return token;
}
Token Parser::nextToken() {
    int nextTokenIndex = currentTokenIndex + 1;
    if(nextTokenIndex >= tokens.size()) {
        return Token{TokenType::EOT};
    }
    return tokens[nextTokenIndex];
}





void Parser::expectToken(TokenType type, std::string &err) {
    if(currentTokenAndAdvance().type != type) {
        ErrorHandler::handleError(new SyntaxError(err));
    }
}





Node* Parser::parse() {
    StmtsNode *node = new StmtsNode();
    while(currentToken().type != TokenType::EOT) {
        if(currentToken().type == TokenType::EOL) {
            currentTokenAndAdvance();
            continue;
        }
        node->stmts.emplace_back(parse_expr());
    }
    return node;
}

Node* Parser::parse_expr() {
    if(currentToken().type == TokenType::ECHO) {
        currentTokenAndAdvance();
        Node *value = parse_compare_expr();
        return new Echo(value);
    }
    else if(currentToken().type == TokenType::IF) {
        return parse_if_expr();
    }
    else if(currentToken().type == TokenType::WHILE) {
        return parse_while_expr();
    }
    else if(currentToken().type == TokenType::IDENTIFIER) {
        return parse_assign_expr();
    }
    return parse_compare_expr();
}





Node* Parser::parse_if_expr() {
    currentTokenAndAdvance();

    Node *condExpr = parse_compare_expr();
    StmtsNode *ifStmts = new StmtsNode();

    expectToken(TokenType::LBRACE, std::string("expected \'{\'"));

    while(currentToken().type != TokenType::RBRACE && currentToken().type != TokenType::EOT) {
        if(currentToken().type == TokenType::EOL) {
            currentTokenAndAdvance();
            continue;
        }
        ifStmts->stmts.emplace_back(parse_expr());
    }
    expectToken(TokenType::RBRACE, std::string("expected \'}\'"));

    while(currentToken().type == TokenType::EOL) {
        currentTokenAndAdvance();
    }

    if(currentToken().type != TokenType::ELSE) {
        return new IfExpr(condExpr, ifStmts, NULL);
    }

    StmtsNode *elseStmts = new StmtsNode();
    currentTokenAndAdvance();
    expectToken(TokenType::LBRACE, std::string("expected \'{\'"));

    while(currentToken().type != TokenType::RBRACE && currentToken().type != TokenType::EOT) {
        if(currentToken().type == TokenType::EOL) {
            currentTokenAndAdvance();
            continue;
        }
        elseStmts->stmts.emplace_back(parse_expr());
    }
    expectToken(TokenType::RBRACE, std::string("expected \'}\'"));
    return new IfExpr(condExpr, ifStmts, elseStmts);
}





Node* Parser::parse_while_expr() {
    currentTokenAndAdvance();

    Node *condExpr = parse_compare_expr();
    StmtsNode *loopStmts = new StmtsNode();

    expectToken(TokenType::LBRACE, std::string("expected \'{\'"));

    while(currentToken().type != TokenType::RBRACE && currentToken().type != TokenType::EOT) {
        if(currentToken().type == TokenType::EOL) {
            currentTokenAndAdvance();
            continue;
        }
        loopStmts->stmts.emplace_back(parse_expr());
    }
    expectToken(TokenType::RBRACE, std::string("expected \'}\'"));
    return new WhileExpr(condExpr, loopStmts);
}





Node* Parser::parse_assign_expr() {
    std::string identifier = currentToken().value;
    if(nextToken().type == TokenType::ASS) {
        currentTokenAndAdvance();
        currentTokenAndAdvance();
        Node *right = parse_compare_expr();
        return new AssignExpr(identifier, right);
    }
    else {
        return parse_compare_expr();
    }
}





Node* Parser::parse_compare_expr() {
    Node *left = parse_additive_expr();

    while(currentToken().value == "==" || currentToken().value == "!=" || currentToken().value == "<" ||
        currentToken().value == ">" || currentToken().value == "<=" || currentToken().value == ">=") {
            std::string op = currentTokenAndAdvance().value;
            Node *right = parse_additive_expr();

            Node *newNode = new BinaryExpr(left, right, op);
            left = newNode;
    }
    return left;
}





Node* Parser::parse_additive_expr() {
    Node *left = parse_multiplicative_expr();

    while(currentToken().value == "+" || currentToken().value == "-") {
        std::string op = currentTokenAndAdvance().value;
        Node *right = parse_multiplicative_expr();
        
        Node *newNode = new BinaryExpr(left, right, op);
        left = newNode;
    }
    return left;
}





Node* Parser::parse_multiplicative_expr() {
    Node *left = parse_primary_expr();

    while(currentToken().value == "*" || currentToken().value == "/") {
        std::string op = currentTokenAndAdvance().value;
        Node *right = parse_primary_expr();
        
        Node *newNode = new BinaryExpr(left, right, op);
        left = newNode;
    }
    return left;
}





Node* Parser::parse_primary_expr() {
    Token token = currentTokenAndAdvance();
    switch(token.type) {
        case TokenType::NUL:
            return new NullLiteral();
        break;
        case TokenType::IDENTIFIER:
            return new Identifier(token.value);
        break;
        case TokenType::INTEGER:
            return new NumericLiteral(token.value);
        break;
        case TokenType::LPAREN: {
            Node *value = parse_expr();
            expectToken(TokenType::RPAREN, std::string("expected closing parenthesis"));
            return value;
        }
        break;
        default:
            ErrorHandler::handleError(new SyntaxError(std::string("Unexpected Token: " + currentToken().toString() + std::to_string(currentTokenIndex))));
            return new Node(NodeType::NODE);
    }
}