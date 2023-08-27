#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "Lexer/Token.hpp"
#include "Parser/Node.hpp"
#include "Interpreter/RuntimeVal.hpp"



class Interpreter {
private:
    std::string currentLine;
    std::vector<Token> tokens;

    void eval(StmtsNode *stmtsNode);
    RuntimeVal* eval_expr(Node *ast);
    RuntimeVal* eval_assign_expr(AssignExpr *node);
    RuntimeVal* eval_bin_expr(BinaryExpr *node);
    RuntimeVal* eval_if_expr(IfExpr *node);
    RuntimeVal* eval_while_expr(WhileExpr *node);

public:
    std::map<std::string, RuntimeVal*> variables;

    void run(std::string &filePath);
};

#endif