#include "Minus.h"
// Class that belongs to ex1 Expression.

Minus::Minus(Expression *l, Expression *r): BinaryOperator()  {
    this->right = r;
    this->left = l;
}

double Minus::calculate() {
    return (Minus::left->calculate() - Minus::right->calculate());
}
