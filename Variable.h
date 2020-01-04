#ifndef HW1__VARIABLE_H_
#define HW1__VARIABLE_H_

#include <string>
#include "Expression.h"

using namespace std;
// Class that belongs to ex1 Expression.
class Variable : public Expression {
    string name;
    double value;

public:
    Variable(string nameVal, double val);

    Variable &operator++();

    Variable &operator--();

    Variable &operator++(int);

    Variable &operator--(int);

    Variable &operator+=(double add);

    Variable operator=(double val);

    virtual ~Variable() {};

    double calculate();
};

#endif //HW1__VARIABLE_H_
