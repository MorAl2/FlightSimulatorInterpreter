#include "Plus.h"

Plus::Plus(Expression *l, Expression *r) : BinaryOperator()  {
    this->right = r;
    this->left = l;
}

double Plus::calculate() {
    return (Plus::left->calculate() + Plus::right->calculate());
}
