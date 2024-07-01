#ifndef _ERROR_H_
#define _ERROR_H_

#include <string>

class Error {
public:
    virtual std::string toString() const;
};



class IllegalCharError: public Error {
private:
    std::string details;
public:
    IllegalCharError(const std::string &details);
    std::string toString() const override;
};



class SyntaxError: public Error {
private:
    std::string details;
public:
    SyntaxError(const std::string &details);
    std::string toString() const override;
};

#endif