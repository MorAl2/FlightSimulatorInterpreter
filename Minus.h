#ifndef HW1__MINUS_H_
#define HW1__MINUS_H_

#include "BinaryOperator.h"
#include "Value.h"
// Class that belongs to ex1 Expression.

class Minus : public BinaryOperator {
public:
    Minus(Expression *l, Expression *r);

    double calculate();

    virtual ~Minus() {}
};

#endif //HW1__MINUS_H_
