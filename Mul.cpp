#include "Mul.h"
// Class that belongs to ex1 Expression.

Mul::Mul(Expression *l, Expression *r): BinaryOperator()  {
    this->right = r;
    this->left = l;
}

double Mul::calculate() {
    return (Mul::left->calculate() * Mul::right->calculate());
}