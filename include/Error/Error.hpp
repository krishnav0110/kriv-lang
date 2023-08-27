#ifndef _ERROR_H_
#define _ERROR_H_

#include <string>

class Error {
public:
    virtual std::string toString();
};



class IllegalCharError: public Error {
private:
    std::string details;
public:
    IllegalCharError(std::string &details);
    std::string toString() override;
};



class SyntaxError: public Error {
private:
    std::string details;
public:
    SyntaxError(std::string &details);
    std::string toString() override;
};

#endif