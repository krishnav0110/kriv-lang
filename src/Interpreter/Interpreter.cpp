#include <iostream>

#include "Interpreter.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"

void Interpreter::run(const std::string &filePath) {
    Tokenizer tokenizer(filePath);
    std::vector<Token> tokens = tokenizer.generateTokens();

    Parser parser(tokens);
    Node *ast = parser.parse();

    eval((StmtsNode*)ast);
    delete ast;
}





void Interpreter::eval(StmtsNode *stmtsNode) {
    for(Node *stmt: stmtsNode->stmts) {
        RuntimeVal *value = eval_expr(stmt);
        delete value;
    }
}





RuntimeVal* Interpreter::eval_expr(Node *ast) {
    switch(ast->type) {
        case NodeType::NULL_LITERAL:
            return new NullVal();
        break;
        case NodeType::ECHO_EXPR: {
            Echo *node = (Echo*)ast;
            std::cout << eval_expr(node->value)->toString() << "\n";
            return new RuntimeVal(RuntimeValType::NONE);
        }
        break;
        case NodeType::NUMERIC_LITERAL: {
            NumericLiteral *node = (NumericLiteral*)ast;
            return new NumberVal(node->value);
        }
        break;
        case NodeType::IDENTIFIER: {
            Identifier *node = (Identifier*)ast;
            if(variables.find(node->symbol) == variables.end()) {
                return new NullVal();
            }
            return variables.at(node->symbol);
        }
        break;
        case NodeType::ASSIGN_EXPR:
            return eval_assign_expr((AssignExpr*)ast);
        break;
        case NodeType::BINARY_EXPR:
            return eval_bin_expr((BinaryExpr*)ast);
        break;
        case NodeType::IF_EXPR:
            return eval_if_expr((IfExpr*)ast);
        break;
        case NodeType::WHILE_EXPR:
            return eval_while_expr((WhileExpr*)ast);
        break;

        default:
            return new RuntimeVal(RuntimeValType::NONE);
    }
}





RuntimeVal* Interpreter::eval_assign_expr(AssignExpr *node) {
    RuntimeVal *right = eval_expr(node->right);
    if(variables.find(node->identifier) == variables.end()) {   
        variables.emplace(node->identifier, right);
    }
    else {
        variables[node->identifier] = right;
    }
    return new RuntimeVal(RuntimeValType::NONE);
}





RuntimeVal* Interpreter::eval_bin_expr(BinaryExpr *node) {
    RuntimeVal *left = eval_expr(node->left);
    RuntimeVal *right = eval_expr(node->right);

    if(left->type == RuntimeValType::NUMBER && right->type == RuntimeValType::NUMBER) {
        NumberVal *lhs = (NumberVal*)left;
        NumberVal *rhs = (NumberVal*)right;

        if(node->op == "+") {
            return new NumberVal(lhs->value + rhs->value);
        }
        else if(node->op == "-") {
            return new NumberVal(lhs->value - rhs->value);
        }
        else if(node->op == "*") {
            return new NumberVal(lhs->value * rhs->value);
        }
        else if(node->op == "/") {
            return new NumberVal(lhs->value / rhs->value);
        }
        else if(node->op == "==") {
            return new NumberVal(lhs->value == rhs->value);
        }
        else if(node->op == "!=") {
            return new NumberVal(lhs->value != rhs->value);
        }
        else if(node->op == "<") {
            return new NumberVal(lhs->value < rhs->value);
        }
        else if(node->op == ">") {
            return new NumberVal(lhs->value > rhs->value);
        }
        else if(node->op == "<=") {
            return new NumberVal(lhs->value <= rhs->value);
        }
        else if(node->op == ">=") {
            return new NumberVal(lhs->value >= rhs->value);
        }
        else {
            return new NullVal();
        }
    }
    return new NullVal();
}





RuntimeVal* Interpreter::eval_if_expr(IfExpr *node) {
    RuntimeVal *condValue = eval_expr(node->cond);
    if(condValue->type == RuntimeValType::NUMBER) {
        NumberVal *condNumValue = (NumberVal*)condValue;
        if(condNumValue->value != 0) {
            eval(node->ifStmts);
        }
        else if(node->elseStmts != NULL) {
            eval(node->elseStmts);
        }
    }
    else if(node->elseStmts != NULL) {
        eval(node->elseStmts);
    }
    return new RuntimeVal(RuntimeValType::NONE);
}





RuntimeVal* Interpreter::eval_while_expr(WhileExpr *node) {
    while(true) {
        RuntimeVal *condValue = eval_expr(node->cond);
        if(condValue->type == RuntimeValType::NUMBER) {
            NumberVal *condNumValue = (NumberVal*)condValue;
            if(condNumValue->value != 0) {
                eval(node->loopStmts);
            }
            else {
                break;
            }
        }
        else if(condValue->type != RuntimeValType::NUL) {
            eval(node->loopStmts);
        }
    }
    return new RuntimeVal(RuntimeValType::NONE);
}