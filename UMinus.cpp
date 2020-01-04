#include "UMinus.h"
// Class that belongs to ex1 Expression.

UMinus::UMinus(Expression *val) : UnaryOperator() {
    this->valExp = val;
}

double UMinus::calculate() {
    return ((-1) * (UMinus::valExp->calculate()));
}
