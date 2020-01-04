#include "Div.h"
// Class that belongs to ex1 Expression.

Div::Div(Expression *l, Expression *r) : BinaryOperator()  {
    this->right = r;
    this->left = l;
}

double Div::calculate() {
    if (Div::right->calculate() == 0) {
        throw ("bad input");
    } else {
        return (Div::left->calculate() / Div::right->calculate());
    }
}
