//
// Created by mor on 18.12.2019.
//

#include "While.h"
#include "Interpreter.h"
// function for delete space and tabs from string
string While::removeSpaces(std::__cxx11::string str) {
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
void While :: setParam(string array[],int index,Interpreter* i ){
  this->condition = array[index+1];
  this ->interpreter=i;
}

// execute of While
int While ::  execute(){
  double sumParam = 0;
  int flag=0;
  // check if condition is true
  while (conditionCheck(this->condition)) {
    // execute all command in commandsWhile vector
    for (auto i = this ->commandsWhile.begin(); i != this ->commandsWhile.end(); ++i){
      if(flag==0) {
        sumParam = sumParam + (*i)->execute();
      } else {
        (*i)->execute();
      }
    }
    flag=1;
  }
  // erase nodes of vector
  commandsWhile.clear();
  this->numParam=sumParam;
  return this->numParam+1;
}

// function of check if condition is true
bool While:: conditionCheck(string conditionToTest){
  int pos;
  conditionToTest = this->removeSpaces(conditionToTest);
  // case of "<="
  if(conditionToTest.find("<=")!=-1){
    pos=conditionToTest.find("<=");
    double firstSide=interpreter->interpret(conditionToTest.substr(0,pos))->calculate();
    double secondSide=interpreter->interpret(conditionToTest.substr(pos+2,conditionToTest.length()-(pos+2)))->calculate();
    if((firstSide< secondSide)||(firstSide== secondSide)){
      return true;
    } else {
      return false;
    }
  }
  // case of ">="
  if(conditionToTest.find(">=")!=-1){
    pos=conditionToTest.find(">=");
    double firstSide=interpreter->interpret(conditionToTest.substr(0,pos))->calculate();
    double secondSide=interpreter->interpret(conditionToTest.substr(pos+2,conditionToTest.length()-(pos+2)))->calculate();
    if((firstSide> secondSide)||(firstSide== secondSide)){
      return true;
    } else {
      return false;
    }
  }
  // case of "=="
  if(conditionToTest.find("==")!=-1){
    pos=conditionToTest.find("==");
    double firstSide=interpreter->interpret(conditionToTest.substr(0,pos))->calculate();
    double secondSide=interpreter->interpret(conditionToTest.substr(pos+2,conditionToTest.length()-(pos+2)))->calculate();
    if(firstSide== secondSide){
      return true;
    } else {
      return false;
    }
  }
  // case of "!="
  if(conditionToTest.find("!=")!=-1){
    pos=conditionToTest.find("!=");
    double firstSide=interpreter->interpret(conditionToTest.substr(0,pos))->calculate();
    double secondSide=interpreter->interpret(conditionToTest.substr(pos+2,conditionToTest.length()-(pos+2)))->calculate();
    if(firstSide!= secondSide){
      return true;
    } else {
      return false;
    }
  }
  // case of "<"
  if(conditionToTest.find("<")!=-1){
    pos=conditionToTest.find("<");
    double firstSide=interpreter->interpret(conditionToTest.substr(0,pos))->calculate();
    double secondSide=interpreter->interpret(conditionToTest.substr(pos+1,conditionToTest.length()-(pos+1)))->calculate();
    if(firstSide< secondSide){
      return true;
    } else {
      return false;
    }
  }
  // case of ">"
  if(conditionToTest.find(">")!=-1){
    pos=conditionToTest.find(">");
    double firstSide=interpreter->interpret(conditionToTest.substr(0,pos))->calculate();
    double secondSide=interpreter->interpret(conditionToTest.substr(pos+1,conditionToTest.length()-(pos+1)))->calculate();
    if(firstSide> secondSide){
      return true;
    } else {
      return false;
    }
  }
}

// function of add command to vector commandsWhile
void While::addToCommandsWhile(Command* command) {
  this->commandsWhile.push_back(command);
}
// function get for the field numParam of While
int While::getNumParam() {
  return this->numParam;
}