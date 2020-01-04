//
// Created by mor on 18.12.2019.
//

#include "Var.h"
// update fields value from parser
void Var::setParam(string array[], int index, Interpreter *i, vector<string> *controlToSend) {
  this->numParam = 2;
  this->tempValWhile = array[index + 2];
  this->controlToSend = controlToSend;
  this->interpreter = i;
}
// execute of Var Command
int Var::execute() {
  // calculate value of var by interpreter
  this->value = (float) interpreter->interpret(this->removeSpaces(this->tempValWhile))->calculate();
  this->isChanged = true;
  // add to map of interpreter for future use
  this->interpreter->addToMap(this->name, this->value);
  return this->numParam + 1;
}
// function for delete space and tabs from string
string Var::removeSpaces(string str) {
  int count = 0;
  int newCount = 0;
  string newStr;
  for (int i = 0; i < str.length(); i++) {
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
// function get for the field numParam of Var
int Var::getNumParam() {
  return this->numParam;
}

// constructor of Var
Var::Var(string name, float val, string simStr, int sideNum) {
  this->name = name;
  value = val;
  sim = simStr;
  side = side;
}
// setting new value
void Var::updateValue(float val) {
  value = val;
}
// getting the value
float Var::getVal() {
  return value;
}
// getting the name

string Var::getName() {
  return name;
}
// getting the sim
string Var::getSim() {
  return sim;
}
// getting the side
int Var::getSide() {
  return side;
}
// setting the isChanged for sending data to simulator
void Var::setChanged(bool val) {
  this->isChanged = val;
}
// getting the isChanged field
bool Var::getChanged() {
  return (this->isChanged);
}
// function of update  var : name , side and numParamChange
void Var::updateVar(string nameChange, int sideChange, int numParamChange) {
  this->name = nameChange;
  this->side = sideChange;
  this->numParam = numParamChange;
}