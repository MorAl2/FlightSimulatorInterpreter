
#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H
// Class that belongs to ex1 Expression.
using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //PROJECT_EXPRESSION_H
