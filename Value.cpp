#include "Value.h"
// Class that belongs to ex1 Expression.
Value::Value(double val) {
    this->value = val;
}

double Value::calculate() {
    return Value::value;
}
