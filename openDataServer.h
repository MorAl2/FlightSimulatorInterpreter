#ifndef FLIGHTS__OPENDATASERVER_H_
#define FLIGHTS__OPENDATASERVER_H_

#include <thread>
#include "Command.h"
#include "Symbol_Table.h"
#include "Interpreter.h"

class openDataServer : public Command {
  int port = 5400;
  int client_socket = 0;
  int numParam;
  bool* isDone;
  int socketNum;
  Symbol_Table* sym;
  Interpreter* interpreter;

 public:
  openDataServer(Symbol_Table* s,Interpreter* i,bool* is);
  /**
 * creating and running the server socket.
 * @return amount of steps to moving in array
 */
  int execute();
  /**
 * set the client socket field.
 * @param cs client socket.
 */
  void setClientSocket(int client);
  /**
*
* @return the thread condition  field
*/
  bool* getIsDone();
  /**
 *
 * @return the symbol table field
 */
  Symbol_Table* getSym();
  /**
 *
 * @return the intepreter field
 */
  Interpreter* getInter();
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
   */
  void setParam(string array[],int index,Interpreter* i);
    /**
   * @return filed of number of parameters
   */
  int getNumParam();
  /**
   * set the socket number.
* @param num - the socket number.
*/
  void setSocketNum(int num);
  /**
* @return filed of socket number.
*/
  int getSocketNum();
};

#endif //FLIGHTS__OPENDATASERVER_H_
