//
// Created by mor on 5.11.2019.
//

#ifndef HW1__UMINUS_H_
#define HW1__UMINUS_H_

#include "UnaryOperator.h"
#include "Expression.h"
#include "Value.h"
// Class that belongs to ex1 Expression.

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *val);

    double calculate();

    virtual ~UMinus() {}
};

#endif //HW1__UMINUS_H_
