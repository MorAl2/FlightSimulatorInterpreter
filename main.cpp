#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Expression.h"
#include "Interpreter.h"
#include "Command.h"
#include "openDataServer.h"
#include "Sleep.h"
#include "Print.h"
#include "While.h"
#include "string.h"
#include "If.h"
#include "connectControlClient.h"
#include "DefineVarCommand.h"
#include "Symbol_Table.h"
#include "funcCommand.h"
#include <vector>
/**
* @param intertper - the Interpreter from ex1, s string to interpter.
* @return the value of the expression.
*/
float expToDouble(Interpreter *interpreter, string s) {
  return interpreter->interpret(s)->calculate();
}

int main(int argc, char **argv) {
  try {

    vector<thread *> *threadList = new vector<thread *>();
    // tells the thread if to keep run or not.
    bool globalWhileCondition = false;
    // define main interperter for expressions
    Interpreter *globalInterperter = new Interpreter();
    // define vector of set of command for send to simulator
    vector<string> *controlToSend = new vector<string>();
// symbol_Table contains two map for LocalVar and SimulatorVar
    Symbol_Table *sym = new Symbol_Table();
    // funcCommandMap is map of string and function
    map<string, funcCommand *> funcCommandMap;
    // commandMap is map of command and string of name of commmand
    map<string, Command *> commandMap;

    // adding all the Commands to the Command Map.
    commandMap.emplace("openDataServer", new openDataServer(sym, globalInterperter, &globalWhileCondition));
    commandMap.emplace("connectControlClient", new connectControlClient(sym, &globalWhileCondition));
    commandMap.emplace("var", new DefineVarCommand(sym));
    commandMap.emplace("Print", new Print());
    commandMap.emplace("Sleep", new Sleep());
    commandMap.emplace("while", new While());
    commandMap.emplace("if", new If());

    // lexer - get file txt and create vector of tokens
    int start = 0, end = 0, i = 0;
    string tempToken = "", firstToken = "", secondToken = "", middleToken = "";
    vector<string> tokens;
    // open file txt
    ifstream file(argv[1]);
    // check if file open successfully
    if(!file){
      cout << "There was an error opening the fly file!\n";
    }
    string str;
    // read line by line
    while (getline(file, str)) {
      // remove tabs from line
      str.erase(remove(str.begin(), str.end(), '\t'), str.end());
      // check char by char in line
      while (i < str.length()) {
        // create token until one of special chars appear
        while ((str[i] != '(') && (str[i] != ')') && (str[i] != ' ') && (str[i] != ',') && (i < str.length())) {
          tempToken += str[i];
          i++;
        }
        // create token between "
        if (str[i] == '"') {
          i++;
          while (str[i] != '"') {
            tempToken += str[i];
            i++;
          }
        }
        // create tokens before and after -> or <-
        int foundRight = tempToken.find("->");
        int foundLeft = tempToken.find("<-");
        if ((foundRight != -1) && (foundRight != 0)) {
          firstToken = tempToken.substr(0, foundRight);
          secondToken = tempToken.substr(foundRight + 2, tempToken.length() - (foundRight + 2));
          middleToken = "->";
          tokens.push_back(firstToken);
          tokens.push_back(middleToken);
          tokens.push_back(secondToken);
          firstToken = "";
          middleToken = "";
          secondToken = "";
        } else if ((foundLeft != -1) && (foundLeft != 0)) {
          firstToken = tempToken.substr(0, foundLeft);
          secondToken = tempToken.substr(foundLeft + 2, tempToken.length() - (foundLeft + 2));
          middleToken = "<-";
          tokens.push_back(firstToken);
          tokens.push_back(middleToken);
          tokens.push_back(secondToken);
          firstToken = "";
          middleToken = "";
          secondToken = "";
          // create token for other case
        } else {
          if (tempToken.length() != 0) {
            tokens.push_back(tempToken);
            // create token after = until end of line
            if (tempToken == "=") {
              tempToken = "";
              tempToken = str.substr(i + 1, str.length() - i + 1);
              tokens.push_back(tempToken);
              tempToken = "";
              i = str.length() - 1;
            }
            // create token after "while" or "if" until {
            if ((tempToken == "while") || (tempToken == "if")) {
              tempToken = "";
              tempToken = str.substr(i + 1, str.length() - i - 2);
              tokens.push_back(tempToken);
              tempToken = "";
              i = str.length() - 2;
            }
          }
        }
        tempToken = "";
        // create token for string between ()
        if (str[i] == '(') {
          i++;
          if (str[str.length() - 1] == '{') {
            if (str[str.length() - 2] == ' ') {
              while (i != str.length() - 3) {
                tempToken += str[i];
                i++;
              }
            } else {
              while (i != str.length() - 2) {
                tempToken += str[i];
                i++;
              }
            }
          } else {
            while (i != str.length() - 1) {
              tempToken += str[i];
              i++;
            }
          }
          int coma = tempToken.find(",");
          // if () have comma , split to two tokens : one before comma and one after comma
          if (coma != -1) {
            string fristComa = tempToken.substr(0, coma);
            string secondComa = tempToken.substr(coma + 1, tempToken.length() - (coma + 1));
            tokens.push_back(fristComa);
            tokens.push_back(secondComa);
            fristComa = "";
            secondComa = "";
            tempToken = "";
          } else {
            tokens.push_back(tempToken);
            tempToken = "";
          }
        }
        i++;
      }
      i = 0;
    }
    // convert vector to array
    string array[tokens.size()];
    for (int i = 0; i < tokens.size(); i++) {
      array[i] = tokens.at(i);
    }

    // parser
    int index = 0;
    // read all tokens until end
    while (tokens.size() > index) {
      // search first token in commandMap and return appropriate command
      Command *c = commandMap.find(array[index])->second;
      // command found and its not if or while
      if ((commandMap.find(array[index]) != commandMap.end()) && (array[index] != "if") &&
          (array[index] != "while")) {
        // TODO - Noy - check free
        // if command is Print or Sleep we define new Command for commandMap in order to not override values
        if(array[index] == "Print"){
          commandMap.find("Print")->second= new Print();
        }
        if(array[index] == "Sleep"){
          commandMap.find("Sleep")->second= new Sleep();
        }
        // Initialize values ​​of the command, its execution, and update index
        c->setParam(array, index, globalInterperter);
        index += c->execute();
        continue;
      }
      // if command is "If" command
      if ((commandMap.find(array[index]) != commandMap.end()) && (array[index] == "if")) {
        // if command is If we define new Command for commandMap in order to not override values
        commandMap.find("if")->second= new If();
        If *tempIf = (If *) c;
        // Initialize values ​​of the command
        tempIf->setParam(array, index, globalInterperter);
        index += 3;
        // define new index for scope of if
        int tempIndex = index;
        // read scope of If until '}'
        while (array[tempIndex] != "}") {
          c = commandMap.find(array[tempIndex])->second;
          if (commandMap.find(array[tempIndex]) != commandMap.end()) {
            if(array[tempIndex] == "Print"){
              commandMap.find("Print")->second= new Print();
            }
            if(array[tempIndex] == "Sleep"){
              commandMap.find("Sleep")->second= new Sleep();
            }
            c->setParam(array, tempIndex, globalInterperter);
            // all command in scope of If enter to vector by addToCommandsIf
            tempIf->addToCommandsIf(c);
            //update local index 'tempIndex' by num of param of the command
            tempIndex = tempIndex + c->getNumParam() + 1;
          } else {
            Var *tempVar = sym->getLocalMap()->find(array[tempIndex])->second;
            // Initialize values ​​of Var command
            tempVar->setParam(array, tempIndex, globalInterperter, controlToSend);
            //enter Var to vector by addToCommandsIf
            tempIf->addToCommandsIf((Command *) tempVar);
            // update local index 'tempIndex' by num of param of the command
            tempIndex = tempIndex + tempVar->getNumParam() + 1;
          }
        }
        // execute of If and update index
        index += tempIf->execute();
        continue;
      }
      // if command is 'While'
      if ((commandMap.find(array[index]) != commandMap.end()) && (array[index] == "while")) {
        // if command is While we define new Command for commandMap in order to not override values
        commandMap.find("while")->second= new While();
        While *tempWhile = (While *) c;
        // Initialize values ​​of the command
        tempWhile->setParam(array, index, globalInterperter);
        index += 3;
        // define new index for scope of While
        int tempIndex = index;
        // read scope of While until '}'
        while (array[tempIndex] != "}") {
          c = commandMap.find(array[tempIndex])->second;
          if (commandMap.find(array[tempIndex]) != commandMap.end()) {
            if(array[tempIndex] == "Print"){
              commandMap.find("Print")->second= new Print();
            }
            if(array[tempIndex] == "Sleep"){
              commandMap.find("Sleep")->second= new Sleep();
            }
            c->setParam(array, tempIndex, globalInterperter);
            // all command in scope of While enter to vector by addToCommandsWhile
            tempWhile->addToCommandsWhile(c);
            //update local index 'tempIndex' by num of param of the command
            tempIndex = tempIndex + c->getNumParam() + 1;
          } else {
            // Handling a variable exists on the map
            Var *tempVar = sym->getLocalMap()->find(array[tempIndex])->second;
            // Initialize values ​​of Var command
            tempVar->setParam(array, tempIndex, globalInterperter, controlToSend);
            //enter Var to vector by addToCommandsWhile
            tempWhile->addToCommandsWhile((Command *) tempVar);
            // update local index 'tempIndex' by num of param of the command
            tempIndex = tempIndex + tempVar->getNumParam() + 1;
          }
        }
        // execute of While and update index
        index += tempWhile->execute();
        continue;

      }
      // if command not exsits in commandMap
      if (commandMap.find(array[index]) == commandMap.end()) {
        // check if command is exsits var in LocalMap
        if (sym->getLocalMap()->find(array[index]) != sym->getLocalMap()->end()) {
          Var *tempVar = sym->getLocalMap()->find(array[index])->second;
          tempVar->setParam(array, index, globalInterperter, controlToSend);
          index = index + tempVar->execute();
          continue;
          // else - command is for define function
        } else {
          // if it is exsits function - function implementaion
          if(funcCommandMap.find(array[index]) != funcCommandMap.end()) {
            funcCommand* tempFuncEx = funcCommandMap.find(array[index])->second;
            tempFuncEx->setValueParam(array[index+1]);
            index += tempFuncEx->execute();
            // if it is new function - function definition
          } else {
            // define new index for scope of function
            int tempIndexFunc = index;
            // create new function command
            funcCommand* tempFunc = new funcCommand();
            // Initialize values ​​of the command
            tempFunc->setParam(array,tempIndexFunc,globalInterperter);
            // define name for function
            funcCommandMap.emplace(tempFunc->getName(),tempFunc);
            // update index of function
            tempIndexFunc += 3;
            // read scope of function until '}'
            while (array[tempIndexFunc] != "}") {
              c = commandMap.find(array[tempIndexFunc])->second;
              if ((commandMap.find(array[tempIndexFunc]) != commandMap.end())&&(array[tempIndexFunc] != "while")&&(array[tempIndexFunc] != "if")) {
                if(array[tempIndexFunc] == "Print"){
                  commandMap.find("Print")->second= new Print();
                }
                if(array[tempIndexFunc] == "Sleep"){
                  commandMap.find("Sleep")->second= new Sleep();
                }
                c->setParam(array, tempIndexFunc, globalInterperter);
                // all command in scope of function enter to vector by addToCommandsFunc
                tempFunc->addToCommandsFunc(c);
                // update local index 'tempIndexFunc' by num of param of the command
                tempIndexFunc = tempIndexFunc + c->getNumParam() + 1;
              }
                // when command while exsits in function
              else if((commandMap.find(array[tempIndexFunc]) != commandMap.end())&&(array[tempIndexFunc] == "while")) {
                // if command is While we define new Command for commandMap in order to not override values
                commandMap.find("while")->second= new While();
                While *tempWhile = (While *) c;
                // Initialize values ​​of the command
                tempWhile->setParam(array, tempIndexFunc, globalInterperter);
                // update index of function
                tempIndexFunc += 3;
                // read scope of while until '}'
                while (array[tempIndexFunc] != "}") {
                  c = commandMap.find(array[tempIndexFunc])->second;
                  if (commandMap.find(array[tempIndexFunc]) != commandMap.end()) {
                    if(array[tempIndexFunc] == "Print"){
                      commandMap.find("Print")->second= new Print();
                    }
                    if(array[tempIndexFunc] == "Sleep"){
                      commandMap.find("Sleep")->second= new Sleep();
                    }
                    c->setParam(array, tempIndexFunc, globalInterperter);
                    // all command in scope of While enter to vector by addToCommandsWhile
                    tempWhile->addToCommandsWhile(c);
                    // update local index 'tempIndexFunc' by num of param of the command
                    tempIndexFunc = tempIndexFunc + c->getNumParam() + 1;
                  } else {
                    // Handling a variable exists on the map
                    Var *tempVar = sym->getLocalMap()->find(array[tempIndexFunc])->second;
                    // Initialize values ​​of Var command
                    tempVar->setParam(array, tempIndexFunc, globalInterperter, controlToSend);
                    //enter Var to vector by addToCommandsWhile
                    tempWhile->addToCommandsWhile((Command *) tempVar);
                    // update local index 'tempIndexFunc' by num of param of the command
                    tempIndexFunc = tempIndexFunc + tempVar->getNumParam() + 1;
                  }
                }
                //enter while commamd to vector by addToCommandsFunc
                tempFunc->addToCommandsFunc((Command *) tempWhile);
                // update index of function
                tempIndexFunc += 1;
              }
                // when command if exsits in function
              else if((commandMap.find(array[tempIndexFunc]) != commandMap.end())&&(array[tempIndexFunc] == "if")) {
                // if command is if we define new Command for commandMap in order to not override values
                commandMap.find("if")->second= new If();
                If *tempIf = (If *) c;
                // Initialize values ​​of the command
                tempIf->setParam(array, tempIndexFunc, globalInterperter);
                // update index of function
                tempIndexFunc += 3;
                // read scope of if until '}'
                while (array[tempIndexFunc] != "}") {
                  c = commandMap.find(array[tempIndexFunc])->second;
                  if (commandMap.find(array[tempIndexFunc]) != commandMap.end()) {
                    if(array[tempIndexFunc] == "Print"){
                      commandMap.find("Print")->second= new Print();
                    }
                    if(array[tempIndexFunc] == "Sleep"){
                      commandMap.find("Sleep")->second= new Sleep();
                    }
                    c->setParam(array, tempIndexFunc, globalInterperter);
                    // all command in scope of While enter to vector by addToCommandsIf
                    tempIf->addToCommandsIf(c);
                    // update local index 'tempIndexFunc' by num of param of the command
                    tempIndexFunc = tempIndexFunc + c->getNumParam() + 1;
                  } else {
                    // Handling a variable exists on the map
                    Var *tempVar = sym->getLocalMap()->find(array[tempIndexFunc])->second;
                    // Initialize values ​​of Var command
                    tempVar->setParam(array, tempIndexFunc, globalInterperter, controlToSend);
                    //enter Var to vector by addToCommandsIf
                    tempIf->addToCommandsIf((Command *) tempVar);
                    // update local index 'tempIndexFunc' by num of param of the command
                    tempIndexFunc = tempIndexFunc + tempVar->getNumParam() + 1;
                  }
                }
                //enter if commamd to vector by addToCommandsFunc
                tempFunc->addToCommandsFunc((Command *) tempIf);
                // update index of function
                tempIndexFunc += 1;
              } else {
                // Handling a variable exists on the map
                Var *tempVar = sym->getLocalMap()->find(array[tempIndexFunc])->second;
                // Initialize values ​​of Var command
                tempVar->setParam(array, tempIndexFunc, globalInterperter, controlToSend);
                //enter Var to vector by addToCommandsFunc
                tempFunc->addToCommandsFunc((Command *) tempVar);
                // update local index 'tempIndexFunc' by num of param of the command
                tempIndexFunc = tempIndexFunc + tempVar->getNumParam() + 1;
              }
            }
            index = tempIndexFunc+1;
          }
        }

      }
    }
    // stops the threads
    globalWhileCondition = true;
  }
  catch(char const* s){
    cout << s << endl;
  }
  return 0;

}