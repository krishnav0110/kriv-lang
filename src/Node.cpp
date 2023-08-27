#include "Parser/Node.hpp"

Node::Node(NodeType type) {
    this->type = type;
}
std::string Node::toString() {
    return "node";
}





StmtsNode::StmtsNode(): Node(NodeType::STMTS) {}
std::string StmtsNode::toString() {
    std::string strValue;
    for(Node *stmt: stmts) {
        strValue += stmt->toString() + "\n";
    }
    return strValue;
}
StmtsNode::~StmtsNode() {
    for(Node *stmt: stmts) {
        delete stmt;
    }
}





NullLiteral::NullLiteral(): Node(NodeType::NULL_LITERAL) {}
std::string NullLiteral::toString() {
    return "null";
}





NumericLiteral::NumericLiteral(std::string &value): Node(NodeType::NUMERIC_LITERAL) {
    this->value = std::stoi(value);
}
std::string NumericLiteral::toString() {
    return std::to_string(value);
}





Identifier::Identifier(std::string &symbol): Node(NodeType::IDENTIFIER) {
    this->symbol = symbol;
}
std::string Identifier::toString() {
    return symbol;
}





Echo::Echo(Node *value): Node(NodeType::ECHO_EXPR) {
    this->value = value;
}
std::string Echo::toString() {
    return "echo: " + value->toString();
}
Echo::~Echo() {
    delete value;
}





AssignExpr::AssignExpr(std::string &identifier, Node *right): Node(NodeType::ASSIGN_EXPR) {
    this->identifier = identifier;
    this->right = right;
}
std::string AssignExpr::toString() {
    return identifier + "=" + right->toString();
}
AssignExpr::~AssignExpr() {
    delete right;
}





BinaryExpr::BinaryExpr(Node *left, Node *right, std::string &op): Node(NodeType::BINARY_EXPR) {
    this->left = left;
    this->right = right;
    this->op = op;
}
std::string BinaryExpr::toString() {
    return "(" + left->toString() + op + right->toString() + ")";
}
BinaryExpr::~BinaryExpr() {
    delete left;
    delete right;
}





IfExpr::IfExpr(Node *cond, StmtsNode *ifStmts, StmtsNode *elseStmts): Node(NodeType::IF_EXPR) {
    this->cond = cond;
    this->ifStmts = ifStmts;
    this->elseStmts = elseStmts;
}
std::string IfExpr::toString() {
    std::string strValue = "if " + cond->toString() + " {\n";
    for(Node *stmt: ifStmts->stmts) {
        strValue += "\t" + stmt->toString() + "\n";
    }
    strValue += "}\n";

    if(elseStmts->stmts.size() > 0) {
        strValue += "else {\n";
        for(Node *stmt: elseStmts->stmts) {
            strValue += "\t" + stmt->toString() + "\n";
        }
        strValue += "}";
    }
    return strValue;
}
IfExpr::~IfExpr() {
    delete cond;
    delete ifStmts;
    delete elseStmts;
}





WhileExpr::WhileExpr(Node *cond, StmtsNode *loopStmts): Node(NodeType::WHILE_EXPR) {
    this->cond = cond;
    this->loopStmts = loopStmts;
}
std::string WhileExpr::toString() {
    std::string strValue = "while " + cond->toString() + " {\n";
    for(Node *stmt: loopStmts->stmts) {
        strValue += "\t" + stmt->toString() + "\n";
    }
    strValue += "}";
    return strValue;
}
WhileExpr::~WhileExpr() {
    delete cond;
    delete loopStmts;
}