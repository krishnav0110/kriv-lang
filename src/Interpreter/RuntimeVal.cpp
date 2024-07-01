#include "RuntimeVal.hpp"

RuntimeVal::RuntimeVal(RuntimeValType type) {
    this->type = type;
}
std::string RuntimeVal::toString() const {
    return "runtimeVal";
}



NullVal::NullVal(): RuntimeVal(RuntimeValType::NUL) {}
std::string NullVal::toString() const {
    return "null";
}



NumberVal::NumberVal(float value): RuntimeVal(RuntimeValType::NUMBER) {
    this->value = value;
}
std::string NumberVal::toString() const {
    return std::to_string(value);
}