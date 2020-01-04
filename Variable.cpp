#include "Variable.h"
// Class that belongs to ex1 Expression.

Variable::Variable(string nameVal, double val) {
    this->value = val;
    this->name = nameVal;
}

double Variable::calculate() {
    return Variable::value;
}

Variable &Variable::operator++() {
    this->value = this->value + 1;
    return *this;
}

Variable &Variable::operator--() {
    this->value = this->value - 1;
    return *this;
}

Variable &Variable::operator++(int) {
    this->value = this->value + 1;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value = this->value - 1;
    return *this;
}

Variable &Variable::operator+=(double add) {
    this->value = this->value + add;
    return *this;
}

Variable Variable::operator=(double val) {
    this->value = val;
    return *this;
}