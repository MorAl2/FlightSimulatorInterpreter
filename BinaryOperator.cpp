#include "BinaryOperator.h"
// Class that belongs to ex1 Expression.

BinaryOperator::BinaryOperator() : Expression() {}

BinaryOperator::~BinaryOperator() {
    delete (this->left);
    delete (this->right);
}
