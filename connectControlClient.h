#ifndef FLIGHTS__CONNECTCONTROLCLIENT_H_
#define FLIGHTS__CONNECTCONTROLCLIENT_H_

#include <thread>
#include "Command.h"
#include "Symbol_Table.h"
#include "vector"
#include "Interpreter.h"

class connectControlClient : public Command {
  string ip;
  int port;
  string portAsString;
  int numParam;
  Symbol_Table *sym;
  bool *isDone;
  int client_Socket;
  Interpreter *interpreter;


 public:
  connectControlClient(Symbol_Table *symVal, bool *is);
  /**
 *
 * @return the thread condition field.
 */
  bool *getIsDone();
  /**
 *  set the client socket field.
 * @param cs client socket.
 */
  void setClient(int cs);
  /**
 *
 * @return the client socket field.
 */
  int getClient();
  /**
 *
 * @return the symbol table field.
 */
  Symbol_Table *getSym();
  /**
* update parameters for fields of command by parser
* @param array contain tokens of fly.txt that split by lexer
* @param index current index of array
* @param i  pointer of Interpeter(ex1)
*/
  virtual void setParam(string array[], int index, Interpreter *i);
  /**
 * creating and running the client socket.
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
 * @return filed of number of parameters
 */
  int getNumParam();

};

#endif //FLIGHTS__CONNECTCONTROLCLIENT_H_
