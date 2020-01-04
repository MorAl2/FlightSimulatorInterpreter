#ifndef HW1__MUL_H_
#define HW1__MUL_H_

#include "Expression.h"
#include "Value.h"
#include "BinaryOperator.h"
// Class that belongs to ex1 Expression.

class Mul : public BinaryOperator {
public:
    Mul(Expression *l, Expression *r);

    double calculate();

    virtual ~Mul() {}
};


#endif //HW1__MUL_H_
