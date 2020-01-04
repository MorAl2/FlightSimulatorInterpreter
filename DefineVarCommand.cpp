#include "Var.h"
#include "DefineVarCommand.h"

//execute of DefineVarCommand
int DefineVarCommand :: execute() {
  //add this var to the varMap od interpreter in order to calculate expression
  this->interpreter->addToMap(this->name,this->value);
  //if the cover orientation not exist
  if(this->side == 0){
    //calculate the expression of the value by interpreter (ex1)
    this->value=interpreter->interpret(this->valAsString)->calculate();
    //add this var to the varMap od interpreter in order to calculate expression
    this->interpreter->addToMap(this->name,this->value);
    //create new var
    Var* tempVar = new Var(this->name,this->value,this->sim,this->side);
    //add this var to the map of LocVars
    this->sym->addToLocVars(this->name,tempVar);
  }else {
    // search var in SimMap and put this object on  LocVars map as value
    this->sym->addToLocVars(this->name,(this->sym->getSimMap()->at(this->sim)));
    // update object in SimMap
    this->sym->getSimMap()->at(this->sim)->updateVar(this->name,this->side,this->numParam);
  }
  // Initializing side for next var
  this->side = 0;
  return this->numParam+1;
}
// update fields value from parser
void DefineVarCommand :: setParam(string array[],int index,Interpreter* i){
  this->interpreter = i;
  this->name = array[index + 1];
  // if string contain "sim" is simulator var
  if(array[index+3]=="sim") {
    this->numParam = 4;
    string simTemp;
    // update side of var -> or <-
    if (array[index + 2] == "<-") {
      this->side = -1;
    } else if (array[index + 2] == "->") {
      this->side = 1;
    } else {
      printf("Error Side");
    }
    // case of var is not sim var
    simTemp = array[index + 4];
    simTemp = simTemp.substr(1, simTemp.length() - 2);
    this->sim = simTemp;
  }
  // case of var is equal to another var
  if(array[index+2]=="="){
    this->numParam = 3;
    this->valAsString=this->removeSpaces(array[index+3]);
  }
}
// function for delete space and tabs from string
string DefineVarCommand::removeSpaces(string str) {
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
//func get for the field numParam of DefineVarCommand
int DefineVarCommand::getNumParam() {
  return this->numParam;
}