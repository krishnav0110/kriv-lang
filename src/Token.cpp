#include "Lexer/Token.hpp"

std::string Token::toString() {
    std::string strValue = "";
    if(type == TokenType::EOL) {
        strValue += "EOL";
    }
    else if(type == TokenType::EOT) {
        strValue += "EOT";
    }

    else if(type == TokenType::NUL) {
        strValue += "NULL";
    }
    else if(type == TokenType::ECHO) {
        strValue += "ECHO";
    }
    else if(type == TokenType::ASS) {
        strValue += "ASS";
    }



    else if(type == TokenType::BIN_OP) {
        if(value == "+") {
            strValue += "PLUS";
        }
        else if(value == "-") {
            strValue += "MINUS";
        }
        else if(value == "*") {
            strValue += "MULT";
        }
        else if(value == "/") {
            strValue += "DIV";
        }
        else if(value == "==") {
            strValue += "EQ";
        }
        else if(value == "!=") {
            strValue += "NEQ";
        }
        else if(value == "<") {
            strValue += "LT";
        }
        else if(value == ">") {
            strValue += "GT";
        }
        else if(value == "<=") {
            strValue += "LTE";
        }
        else if(value == ">=") {
            strValue += "GTE";
        }
    }



    else if(type == TokenType::LPAREN) {
        strValue += "LPAREN";
    }
    else if(type == TokenType::RPAREN) {
        strValue += "RPAREN";
    }
    else if(type == TokenType::LBRACE) {
        strValue += "LBRACE";
    }
    else if(type == TokenType::RBRACE) {
        strValue += "RBRACE";
    }



    else if(type == TokenType::IF) {
        strValue += "IF";
    }
    else if(type == TokenType::ELSE) {
        strValue += "ELSE";
    }
    else if(type == TokenType::WHILE) {
        strValue += "WHILE";
    }



    else if(type == TokenType::INTEGER) {
        strValue += "INTEGER, " + value;
    }
    else {
        strValue += "IDENTIFIER, " + value;
    }
    
    return "(" + strValue + ")";
}