//
// Created by mor on 5.11.2019.
//

#ifndef HW1__VALUE_H_
#define HW1__VALUE_H_

#include "Expression.h"
// Class that belongs to ex1 Expression.
class Value : public Expression {
    double value;

public:
    Value(double val) ;

    double calculate();

    virtual ~Value() {}
};

#endif //HW1__VALUE_H_
