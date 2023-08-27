#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <vector>

enum class NodeType {
    NODE,
    STMTS,
    NULL_LITERAL,
    ECHO_EXPR,
    IDENTIFIER,
    NUMERIC_LITERAL,
    ASSIGN_EXPR,
    BINARY_EXPR,
    IF_EXPR,
    WHILE_EXPR
};

class Node {
public:
    NodeType type;

    Node(NodeType type);
    virtual std::string toString();
    virtual ~Node() {};
};



class StmtsNode: public Node {
public:
    std::vector<Node*> stmts;
    StmtsNode();
    std::string toString() override;
    ~StmtsNode() override;
};



class NullLiteral: public Node {
public:
    NullLiteral();
    std::string toString() override;
};



class NumericLiteral: public Node {
public:
    int value;
    NumericLiteral(std::string &value);
    std::string toString() override;
};



class Identifier: public Node {
public:
    std::string symbol;
    Identifier(std::string &symbol);
    std::string toString() override;
};



class Echo: public Node {
public:
    Node *value;
    Echo(Node *value);
    std::string toString() override;
    ~Echo() override;
};



class AssignExpr: public Node {
public:
    std::string identifier;
    Node *right;
    AssignExpr(std::string &identifier, Node *right);
    std::string toString() override;
    ~AssignExpr() override;
};



class BinaryExpr: public Node {
public:
    Node *left, *right;
    std::string op;
    BinaryExpr(Node *left, Node *right, std::string &op);
    std::string toString() override;
    ~BinaryExpr() override;
};



class IfExpr: public Node {
public:
    Node *cond;
    StmtsNode *ifStmts;
    StmtsNode *elseStmts;
    IfExpr(Node *cond, StmtsNode *ifStmts, StmtsNode *elseStmts);
    std::string toString() override;
    ~IfExpr() override;
};



class WhileExpr: public Node {
public:
    Node *cond;
    StmtsNode *loopStmts;
    WhileExpr(Node *cond, StmtsNode *loopStmts);
    std::string toString() override;
    ~WhileExpr() override;
};

#endif