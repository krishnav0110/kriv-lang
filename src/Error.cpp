#include "Error/Error.hpp"

std::string Error::toString() {
    return "undefined error type";
}



IllegalCharError::IllegalCharError(std::string &details) {
    this->details = details;
}
std::string IllegalCharError::toString() {
    return "Illegal Character Error: " + details;
}



SyntaxError::SyntaxError(std::string &details) {
    this->details = details;
}
std::string SyntaxError::toString() {
    return "Syntax Error: " + details;
}