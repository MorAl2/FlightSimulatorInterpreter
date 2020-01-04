#ifndef HW1__UNARYOPERATOR_H_
#define HW1__UNARYOPERATOR_H_

#include "Expression.h"

using namespace std;
// Class that belongs to ex1 Expression.

class UnaryOperator : public Expression {
protected:
    Expression *valExp;

public:
    UnaryOperator();
    virtual ~UnaryOperator();
};

#endif //HW1__UNARYOPERATOR_H_
