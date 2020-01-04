#include <iostream>
#include "UnaryOperator.h"
// Class that belongs to ex1 Expression.

UnaryOperator::UnaryOperator() : Expression() {}

UnaryOperator::~UnaryOperator() {
    delete (this->valExp);
}
