//
// Created by mor on 18.12.2019.
//

#include "If.h"
#include "Interpreter.h"
// function for delete space and tabs from string
string If::removeSpaces(std::__cxx11::string str) {
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
void If :: setParam(string array[],int index,Interpreter* i ){
  this->condition = array[index+1];
  this ->interpreter=i;
}
//execute of If
int If ::  execute(){
  double sumParam = 0;
  // check if condition is true
  if (conditionCheck(this->condition)) {
    // execute all commands in vector commandsIf
    for (auto i = this ->commandsIf.begin(); i != this ->commandsIf.end(); ++i){
      sumParam=sumParam+(*i)->execute();
    }
    // erase nodes of vector
    commandsIf.clear();
  }
  this->numParam=sumParam;
  return this->numParam+1;
}
// function of check if condition is true
bool If:: conditionCheck(string conditionToTest){
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
// function of add command to vector commandsIf
void If::addToCommandsIf(Command* command) {
  this->commandsIf.push_back(command);
}
// function get for the field numParam of If
int If::getNumParam() {
  return this->numParam;
}