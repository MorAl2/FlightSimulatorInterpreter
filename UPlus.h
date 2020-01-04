#ifndef HW1__UPLUS_H_
#define HW1__UPLUS_H_

#include "UnaryOperator.h"
#include "Value.h"
// Class that belongs to ex1 Expression.
class UPlus : public UnaryOperator {
public:
    UPlus(Expression *val);

    virtual ~UPlus() {}

    double calculate();
};

#endif //HW1__UPLUS_H_
