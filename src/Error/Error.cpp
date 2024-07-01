#include "Error.hpp"

std::string Error::toString() const {
    return "undefined error type";
}



IllegalCharError::IllegalCharError(const std::string &details) {
    this->details = details;
}
std::string IllegalCharError::toString() const {
    return "Illegal Character Error: " + details;
}



SyntaxError::SyntaxError(const std::string &details) {
    this->details = details;
}
std::string SyntaxError::toString() const {
    return "Syntax Error: " + details;
}