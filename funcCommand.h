//
// Created by noy on 27/12/2019.
//

#ifndef EX3_FUNCCOMMAND_H
#define EX3_FUNCCOMMAND_H


#include "Command.h"
#include "Interpreter.h"
#include "Var.h"
// define funcCommand as inherit class of Command
class funcCommand : public Command {
  string name;
  string paramFunc;
  double valueParam;
  int numParam;
  Interpreter* interpreter;
  vector<Command*> commandsFunc;
 public:
  /**
   *
   * @param str string that contain space or tabs
   * @return string without space and tabs
   */
  string removeSpaces(string str);
  /**
   * update var of parameter function , insert var of parameter function to interpreter map and execute all command in vector commandsFunc
   * @return amount of steps to moving in array
   */
  int execute();
    /**
   * update parameters for fields of command by parser
   * @param array contain tokens of fly.txt that split by lexer
   * @param index current index of array
   * @param i  pointer of Interpeter(ex1)
   */
  void setParam(string array[],int index, Interpreter* i);
  /**
   * function of add command to vector commandsFunc
   * @param command pointer of command to add
   */
  void addToCommandsFunc (Command* command);
    /**
   * @return filed of number of parameters
   */
  int getNumParam();
  /**
   * update value parameter of function
   * @param x string of new value
   */
  void setValueParam (string x);
  /**
   * getter name of function
   * @return name of function
   */
  string getName();
};


#endif //EX3_FUNCCOMMAND_H
