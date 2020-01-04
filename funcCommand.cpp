//
// Created by noy on 27/12/2019.
//

#include "funcCommand.h"
#include "funcCommand.h"
#include "Interpreter.h"
#include "Var.h"
// function for delete space and tabs from string
string funcCommand::removeSpaces(std::__cxx11::string str) {
  int count = 0;
  int newCount= 0;
  string newStr;
  for (int i = 0; i<str.length(); i++) {
    if (str[i] != ' ') {
      newStr += str[count];
      count++;
      newCount++;
    } else {
      count++;
    }
  }
  return newStr;
}
// update fields value from parser
void funcCommand :: setParam(string array[],int index,Interpreter* i ){
  this ->interpreter=i;
  this->name = array[index];
  this->paramFunc = array[index+1];
}

int funcCommand ::  execute(){
  // update var of parameter function
  string tempName = this->paramFunc.substr(4,this->paramFunc.length()-4);
  Var* tempVar = new Var(this->paramFunc.substr(4,this->paramFunc.length()-4),this->valueParam,"",0);
  // insert var of parameter function to interpreter map
  this->interpreter->addToMap(tempName,this->valueParam);
  // execute all command in vector commandsFunc
  for (auto i = this ->commandsFunc.begin(); i != this ->commandsFunc.end(); ++i){
    (*i)->execute();
  }
  return 2;
}
// function of add command to vector commandsFunc
void funcCommand::addToCommandsFunc(Command* command) {
  this->commandsFunc.push_back(command);
}
// function get for the field numParam of funcCommand
int funcCommand::getNumParam() {
  return this->numParam;
}
// function of update value of parameter function
void funcCommand:: setValueParam (string x){
  this->valueParam=interpreter->interpret(this->removeSpaces(x))->calculate();
}
// function of get function name
string funcCommand:: getName(){
  return this->name;
}
