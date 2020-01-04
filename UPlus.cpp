#include "UPlus.h"
// Class that belongs to ex1 Expression.
UPlus::UPlus(Expression *val) : UnaryOperator() {
    this->valExp = val;
}

double UPlus::calculate() {
    return UPlus::valExp->calculate();
}