#ifndef HW1__BINARYOPERATOR_H_
#define HW1__BINARYOPERATOR_H_

#include <iostream>
#include "Expression.h"
// Class that belongs to ex1 Expression.

class BinaryOperator : public Expression {
protected:
    Expression *right;
    Expression *left;

public:
    BinaryOperator();
    virtual ~BinaryOperator();
};

#endif //HW1__BINARYOPERATOR_H_
