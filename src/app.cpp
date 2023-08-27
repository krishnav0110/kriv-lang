#include <iostream>
#include "Interpreter/Interpreter.hpp"

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "filePath not found\n";
        return 1;
    }
    std::string filePath = argv[1];
    if(filePath.substr(filePath.find("."), filePath.size()) != ".kitty") {
        std::cout << "file extension should be {fileName}.kitty\n";
        return 1;
    }

    Interpreter interpreter;
    interpreter.run(filePath);
    std::cout << "\nFinished execution...\n";
    return 0;
}