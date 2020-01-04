//
// Created by mor on 18.12.2019.
//

#ifndef FLIGHTS_WHILE_H
#define FLIGHTS_WHILE_H

#include "Command.h"
#include "Interpreter.h"
// define While as inherit class of Command
class While : public Command {
  string condition;
  int numParam;
  Interpreter* interpreter;
  vector<Command*> commandsWhile;
 public:
    /**
   *
   * @param str string that contain space or tabs
   * @return string without space and tabs
   */
  string removeSpaces(string str);
    /**
   * if condition is true , execute all commands in vector commandsWhile, after that erase nodes of vector for next use
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
   * function of check if condition of While command is true
   * @param conditionToTest string of condition
   * @return true or false
   */
  bool conditionCheck(string conditionToTest);
    /**
   * function of add command to vector CommandsWhile
   * @param command pointer of command to add
   */
  void addToCommandsWhile (Command* command);
    /**
   * @return filed of number of parameters
   */
  int getNumParam();
};

#endif //FLIGHTS_WHILE_H