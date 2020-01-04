#ifndef FLIGHTS__SLEEP_H_
#define FLIGHTS__SLEEP_H_

#include <unistd.h>
#include <thread>
#include "Command.h"
// define Sleep as inherit class of Command
class Sleep : public Command{
  Interpreter* interpreter;
  int numParam;
  int time;
  string timeAsString;

 public:
  Sleep(){}
  /**
* set the time to sleep
* @param time - time to sleep.
*/
  void setTime(int time);
  int execute();
    /**
   * update parameters for fields of command by parser
   * @param array contain tokens of fly.txt that split by lexer
   * @param index current index of array
   * @param i  pointer of Interpeter(ex1)
   */
  void setParam(string array[],int index, Interpreter* i);
    /**
   *
   * @param str string that contain space or tabs
   * @return string without space and tabs
   */
  string removeSpaces(string str);
    /**
   * @return filed of number of parameters
   */
  int getNumParam();
};

#endif //FLIGHTS__SLEEP_H_
