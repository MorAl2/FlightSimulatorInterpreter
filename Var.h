#ifndef FLIGHTS__VAR_H_
#define FLIGHTS__VAR_H_
#include <iostream>
#include "string"
#include "vector"
#include "Interpreter.h"
#include "Command.h"

using namespace std;
// define Var as inherit class of Command
class Var : public Command {
  string name;
  float value;
  string sim;
  // 1 if the Var changes data in the simulator, 0 if the sim cahnges the var 0 otherwise.
  int side;
  int numParam;
  // tells if the value had changed and then will send to simulator
  bool isChanged = false;
  vector<string> *controlToSend;
  Interpreter *interpreter;
  string tempValWhile;

 public:
  /**
   * constructor
   * @param name name of var
   * @param val value of var
   * @param simStr path of var in simulator
   * @param sideNum side of var -> or <-
   */
  Var(string name, float val, string simStr, int sideNum);
  /**
   * setter of value
   * @param val new value
   */
  void updateValue(float val);
  /**
   * getter of value
   * @return current value
   */
  float getVal();
  /**
   * getter of name
   * @return name of var
   */
  string getName();
  /**
   * getter of sim path
   * @return path of var in simulator
   */
  string getSim();
  /**
   * getter of side
   * @return number of side ( 1 -> , -1 <- ) , 0 is default
   */
  int getSide();
  /**
   * setting the isChanged for sending data to simulator
   * @param val - if the var has changed.
   */
  void setChanged(bool val);
  /**
   *  getting the isChanged field
   * @return if the var has changed.
   */
  bool getChanged();
  /**
   * function of update  var : name , side and numParamChange
   * @param nameChange new name of var
   * @param sideChange  new side of var
   * @param numParamChange new num param
   */
  void updateVar(string nameChange, int sideChange, int numParamChange);
  /**
   * execute of Var Command : calculate value of var by interpreter , add to map of interpreter for future use
   * @return amount of steps to moving in array
   */
  int execute();
    /**
   *
   * @param str string that contain space or tabs
   * @return string without space and tabs
   */
  string removeSpaces(string str);
    /**
   * update parameters for fields of command by parser
   * @param array contain tokens of fly.txt that split by lexer
   * @param index current index of array
   * @param i  pointer of Interpeter(ex1)
   * @param controlToSend pointer to vector controlToSend for send instructions to simulator
   */
  void setParam(string array[], int index, Interpreter *i, vector<string> *controlToSend);
    /**
     * @return filed of number of parameters
     */
  int getNumParam();
};
#endif //FLIGHTS__VAR_H_