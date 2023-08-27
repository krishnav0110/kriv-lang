#include "Interpreter/RuntimeVal.hpp"

RuntimeVal::RuntimeVal(RuntimeValType type) {
    this->type = type;
}
std::string RuntimeVal::toString() {
    return "runtimeVal";
}



NullVal::NullVal(): RuntimeVal(RuntimeValType::NUL) {}
std::string NullVal::toString() {
    return "null";
}



NumberVal::NumberVal(float value): RuntimeVal(RuntimeValType::NUMBER) {
    this->value = value;
}
std::string NumberVal::toString() {
    return std::to_string(value);
}