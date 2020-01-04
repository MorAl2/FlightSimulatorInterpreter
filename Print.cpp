//
// Created by mor on 18.12.2019.
//

#include "Print.h"
// setting the params by the parser.
void Print :: setParam(string array[],int index,Interpreter* i ){
  this->numParam=1;
  this ->interpreter=i;
  string tempToPrint = array[index+1];
    if (tempToPrint.find("\"") != -1) {
        this->boolPrintAsString=1;
        tempToPrint = tempToPrint.substr(1, tempToPrint.length() - 2);
    this->toPrint = tempToPrint;
  } else {
        this->boolPrintAsString=0;
    this->toPrintAsString = this->removeSpaces(tempToPrint);
  }
}
string Print::removeSpaces(std::__cxx11::string str) {
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
// executing the print command.
int Print ::  execute(){
  // interprting the data
    if(this->boolPrintAsString==0){
        this->toPrint = to_string(interpreter->interpret(this->toPrintAsString)->calculate());
    }
    // printing the data
  cout << this->toPrint <<endl;
  return numParam+1;
}
// getting the param #
int Print::getNumParam() {
    return this->numParam;
}