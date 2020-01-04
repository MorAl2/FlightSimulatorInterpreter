//
// Created by mor on 18.12.2019.
//

#ifndef FLIGHTS_PRINT_H
#define FLIGHTS_PRINT_H
#include "Interpreter.h"
#include "Command.h"
class Print : public Command{
    Interpreter* interpreter;
    string toPrint;
    string toPrintAsString;
    bool boolPrintAsString;
    int numParam;
public:
    int execute();
    string removeSpaces(string str);
    void setParam(string array[],int index, Interpreter* i);
    int getNumParam();
};

#endif //FLIGHTS_PRINT_H