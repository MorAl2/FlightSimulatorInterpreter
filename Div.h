#ifndef HW1__DIV_H_
#define HW1__DIV_H_

#include "BinaryOperator.h"
#include "Value.h"
// Class that belongs to ex1 Expression.

class Div : public BinaryOperator {
public:
    Div(Expression *l, Expression *r);

    double calculate();

    virtual ~Div() {};
};

#endif //HW1__DIV_H_
