#include <iostream>
#include "ErrorHandler.hpp"

void ErrorHandler::handleError(Error *error) {
    std::cout << "\n" << error->toString() << "\n";
    std::exit(1);
}