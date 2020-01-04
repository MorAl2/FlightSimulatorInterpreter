#include "Interpreter.h"
#include "Sleep.h"
// setting the params by the parser
void Sleep :: setParam(string array[],int index,Interpreter* i ){
    this->numParam=1;
    this->interpreter = i;
    this->timeAsString=this->removeSpaces(array[index+1]);
}
// removing the spaces from the string.
string Sleep::removeSpaces(std::__cxx11::string str) {
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
// getting the num of params for the command.
int Sleep::getNumParam() {
    return this->numParam;
}
// setting the time to sleep.
void Sleep::setTime(int time) {
  time = time;
}
// executing the command.
int Sleep::execute(){
  this->time = (int)interpreter->interpret(this->timeAsString)->calculate();
  // sleeping and converting to seconds from ms.
  sleep(time/1000);
  return this->numParam+1;
}