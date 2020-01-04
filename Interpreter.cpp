#include "Interpreter.h"
#include "Variable.h"
#include "Value.h"
#include "Mul.h"
#include "Div.h"
#include "Plus.h"
#include "Minus.h"
#include "UMinus.h"
#include "UPlus.h"
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <regex>
// Class that belongs to ex1 Expression.
Expression *Interpreter::interpret(string expression) {
    queue<string> *q = new queue<string>();
    stack<string> *s = new stack<string>();
    try {

        bool firstRun = true;
        unsigned int irit;
        int countBrases = 0;
        string temp;
        unsigned int i;
        for (i = 0; i < expression.length(); i++) {
            temp = expression[i];
            if (!Interpreter::isOprator(temp) && temp[0] != '(' && temp[0] != ')') {
                irit = i + 1;
                while (expression[irit] != '*' && expression[irit] != '/' && expression[irit] != '+' &&
                       expression[irit] != '-'
                       && irit <= expression.length() - 1 && expression[irit] != '(' && expression[irit] != ')') {
                    temp += expression[irit];
                    irit++;
                }
                i = irit - 1;
                q->push(temp);
            } else if (Interpreter::isOprator(temp)) {

                // checking for 2 opreators in a row
                if (i > 0 && i < expression.length() - 1) {
                    if (isOprator(string(1, expression[i + 1])) || isOprator(string(1, expression[i - 1]))) {
                        throw "bad input";
                    }
                }

                else if (i == 0 && expression.length() > 1) {
                    if (isOprator(string(1, expression[i + 1]))) {
                        throw "bad input";
                    }
                }
                else if (i == expression.length() - 1) {
                    if (isOprator(string(1, expression[i - 1]))) {
                        throw "bad input";
                    }
                }


                if (temp == "-") {
                    if (i == 0) {
                        temp = "#";
                    } else if (isdigit(expression[i + 1])) {
                        if (expression[i - 1] == '(') {
                            temp = "#";
                        }
                    } else if (expression[i + 1] == '(') {
                        if (expression[i - 1] == '(') {
                            temp = "#";
                        }
                    }

                } else if (temp == "+") {
                    if (i == 0) {
                        temp = "@";
                    } else if (isdigit(expression[i + 1])) {
                        if (expression[i - 1] == '(') {
                            temp = "@";
                        }
                    } else if (expression[i + 1] == '(') {
                        if (expression[i - 1] == '(') {
                            temp = "@";
                        }
                    }
                }
                // inserting the first operator
                if (firstRun) {
                    firstRun = false;
                    s->push(temp);
                    continue;
                }
                int stackPresedence;
                if (!s->empty()) {
                    stackPresedence = checkPresedence(s->top());
                } else {
                    stackPresedence = 4;
                }
                int tempPresedence = checkPresedence(temp);

                while (!s->empty()
                       && ((stackPresedence > tempPresedence || stackPresedence == tempPresedence) &&
                           s->top()[0] != '(')) {
                    q->push(s->top());
                    s->pop();
                    if (!s->empty())
                        stackPresedence = checkPresedence(s->top());

                }
                s->push(temp);
            } else if (temp[0] == '(') {
                countBrases++;
                s->push(temp);
            } else if (temp[0] == ')') {
                countBrases--;
                if (s->empty()) {
                    throw ("bad input");
                } else
                    while (s->top()[0] != '(' && !s->empty()) {
                        q->push(s->top());
                        s->pop();
                    }
                if (s->top()[0] == '(') {
                    s->pop();
                } else {
                    throw ("bad input");
                }
            } else {
                throw ("bad input");
            }
        }
        if (countBrases != 0) {
            throw ("bad input");
        }
        // while theres opretor in the stack
        while (!s->empty()) {
            q->push(s->top());
            s->pop();
        }

//    while (!q->empty()) {
//    cout << " " << q->front();
//    q->pop();
//  }
        delete s;
        s = NULL;
        Expression *res = createExp(q);
        delete q;
        q = NULL;
        return res;
    }
    catch (...) {
        if(q!= NULL)
        delete q;
        if(s!=NULL)
        delete s;
        throw "bad input";
    }
}

Expression *Interpreter::createExp(queue<string> *q) {
    stack<Expression *> *s = new stack<Expression *>();

    try {

        while (!q->empty()) {
            if ((!Interpreter::isOprator(q->front())) && q->front() != "@" && q->front() != "#") {
                if (!isdigit(q->front()[0])) {
                    if (isValidVarName(q->front(), 1)) {
                        s->push(new Value(Interpreter::varMap[q->front()]));
                    } else {
                        throw ("bad input");
                    }
                } else if (isdigit(q->front()[0])) {
                    if (Interpreter::isValidDouble(q->front())) {
                        s->push(new Value(stod(q->front())));
                    } else {
                        throw ("bad input");
                    }
                }
                if (!q->empty()) {
                    q->pop();
                } else {
                    throw ("bad input");
                }
            } else if (Interpreter::isOprator(q->front()) || (q->front() != "@" || q->front() != "#")) {
                if (q->front() == "*") {
                    if (s->size() < 2) {
                        throw ("bad input");
                    }
                    Expression *left = s->top();
                    s->pop();
                    Expression *right = s->top();
                    s->pop();
                    s->push(new Mul(left, right));
                    q->pop();
                } else if (q->front() == "/") {
                    if (s->size() < 2) {
                        throw ("bad input");
                    }
                    Expression *left = s->top();
                    s->pop();
                    Expression *right = s->top();
                    s->pop();
                    s->push(new Div(right, left));
                    q->pop();
                } else if (q->front() == "+") {
                    if (s->size() < 2) {
                        throw ("bad input");
                    }
                    Expression *left = s->top();
                    s->pop();
                    Expression *right = s->top();
                    s->pop();
                    s->push(new Plus(left, right));
                    q->pop();
                } else if (q->front() == "-") {
                    if (s->size() < 2) {
                        throw ("bad input");
                    }
                    Expression *left = s->top();
                    s->pop();
                    Expression *right = s->top();
                    s->pop();
                    s->push(new Minus(right, left));
                    q->pop();
                } else if (q->front() == "#") {
                    if (s->size() < 1) {
                        throw ("bad input");
                    }
                    Expression *val = s->top();
                    s->pop();
                    s->push(new UMinus(val));
                    q->pop();
                } else if (q->front() == "@") {
                    if (s->size() < 1) {
                        throw ("bad input");;
                    }
                    Expression *val = s->top();
                    s->pop();
                    s->push(new UPlus(val));
                    q->pop();
                }
            }
        }
        if (!s->empty()) {
            Expression *res = s->top();
            delete (s);
            return res;
        } else {
            throw ("bad input");
        }
    }
    catch (...) {
        delete s;
        throw "bad input";
    }

}

int Interpreter::checkPresedence(string opChar) {
    if (opChar[0] == '*' || opChar[0] == '/' || opChar[0] == '#' || opChar[0] == '@')
        return 2;
        // + or -
    else
        return 1;
}

// checking if the char is one of /*+-().
bool Interpreter::isOprator(string op) {
    if ((op[0] == '+') || (op[0] == '-') || (op[0] == '*') || (op[0] == '/')) {
        return true;
    } else
        return false;
}

void Interpreter::setVariables(string expression) {
    try {
        string token = "", name, value;
        unsigned int i = 0;
        while (i < expression.length()) {
            while (expression[i] != ';' && i < expression.length()) {
                token += expression[i];
                i++;
            }
            int indexEqual = token.find_first_of('=');
            name = token.substr(0, indexEqual);
            value = token.substr(token.find_first_of('=') + 1, token.length());
            token = "";
            if (isValidDouble(value) && isValidVarName(name, 0)) {
                double val = stod(value);
                Interpreter::varMap[name] = val;
            } else {
                throw ("bad input set var");
            }
            i++;
        }
    }
    catch (...) {
        cout << "Interpeteret Problem";
        throw "bad input";
    }
}

bool Interpreter::isValidVarName(string varName, int i) {
    regex b("[A-Za-z_][A-Za-z0-9_]*");
    if (i == 1) {
        if (Interpreter::varMap.find(varName) != Interpreter::varMap.end()) {
            return regex_match(varName, b);
        }
        return false;
    } else {
        return regex_match(varName, b);
    }
}

bool Interpreter::isValidDouble(string exp) {
    int dotCount = 0;
    unsigned int j = 0;
    if(exp[0] == '-'){
        j++;
    }
    for (unsigned int i=j; i < exp.length(); i++) {
        if (!isdigit(exp[i]) && (i == 0 || i == exp.length() - 1)) {
            return false;
        }
        if (!isdigit(exp[i]) && exp[i] != '.') {
            return false;
        }
        if (exp[i] == '.') {
            dotCount++;
        }
        if (dotCount >= 2)
            return false;
    }
    return true;
}

void Interpreter :: addToMap(string name,double val){
  this->varMap[name]=val;
}

map<string, double> Interpreter:: getMap(){
  return this->varMap;
}

Interpreter::~Interpreter() {

}
