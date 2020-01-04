#ifndef FLIGHTS_DEFINEVARCOMMAND_H
#define FLIGHTS_DEFINEVARCOMMAND_H
#include "Interpreter.h"
#include "Command.h"
#include "Symbol_Table.h"
// define DefineVarCommand as inherit class of Command
class DefineVarCommand : public Command{
  int numParam;
  float value;
  string valAsString;
  string sim;
  string name;
  int side;
  Interpreter* interpreter;
  Symbol_Table* sym;
 public:
  /**
   * constructor of DefineVarCommand
   * @param s pointer of Symbol_Table
   */
  DefineVarCommand(Symbol_Table* s){
    this->sym = s;
  }
  /**
   * define new var and put him in LocMap , VarMap ( of interpeter )
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
  // function for delete space and tabs from string
  string removeSpaces(string str);
    /**
   * @return filed of number of parameters
   */
  int getNumParam();
};

#endif //FLIGHTS_DEFINEVARCOMMAND_H