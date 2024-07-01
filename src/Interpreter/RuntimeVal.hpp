#ifndef _RUNTIME_VAL_H_
#define _RUNTIME_VAL_H_

#include <string>

enum class RuntimeValType {NONE, NUL, NUMBER};

class RuntimeVal {
public:
    RuntimeValType type;
    RuntimeVal(RuntimeValType type);
    virtual std::string toString() const;
};



class NullVal: public RuntimeVal {
public:
    NullVal();
    std::string toString() const override;
};



class NumberVal: public RuntimeVal {
public:
    float value;
    NumberVal(float value);
    std::string toString() const override;
};

#endif