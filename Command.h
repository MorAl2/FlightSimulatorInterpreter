//
// Created by mor on 18.12.2019.
//

#ifndef FLIGHTS_COMMAND_H
#define FLIGHTS_COMMAND_H
#include <iostream>
#include "string"
#include "map"
#include "Interpreter.h"

using namespace std;
class Command {
  int numParam;
 public:
  /**
   * update parameters for fields of command by parser
   * @param array contain tokens of fly.txt that split by lexer
   * @param index current index of array
   * @param i  pointer of Interpeter(ex1)
   */
  virtual void setParam(string array[],int index, Interpreter* i){};
  /**
   * executing the command
   * @return amount of steps to moving in array
   */
  virtual int execute()=0;
  /**
   * @return filed of number of parameters
   */
  virtual int getNumParam()=0;

};

#endif //FLIGHTS_COMMAND_H