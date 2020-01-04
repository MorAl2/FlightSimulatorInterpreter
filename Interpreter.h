#ifndef HW1__INTERPRETER_H_
#define HW1__INTERPRETER_H_

#include <string>
#include <stack>
#include <map>
#include <list>
#include <queue>
#include "Expression.h"
#include "Value.h"
// Class that belongs to ex1 Expression.
class Interpreter {
    map<string, double> varMap;


public:
    // returns true if var name is a valid var name, if i is 1 checks in var map too if exist.
    bool isValidVarName(string varName, int i);

    Expression *interpret(string expression);

    void setVariables(string expression);

    // checking if the char is one of /*+-().
    bool isOprator(string op);

    // returns 1 if the left is higher presence, 2 if the right and 3 if equel.
    int checkPresedence(string opChar);

    // returns expression based on the postfix queue sent.
    Expression *createExp(std::queue<string> *s);

    // returns true if exp is really a number
    bool isValidDouble(string exp);

    void addToMap(string name,double val);

    map<string, double> getMap();

    virtual ~Interpreter();

};

#endif //HW1__INTERPRETER_H_
