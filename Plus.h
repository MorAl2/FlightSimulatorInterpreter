#ifndef HW1__PLUS_H_
#define HW1__PLUS_H_

#include "BinaryOperator.h"
#include "Value.h"

class Plus : public BinaryOperator {
public:
    Plus(Expression *l, Expression *r);

    double calculate();

    virtual ~Plus() {}

};

#endif //HW1__PLUS_H_
