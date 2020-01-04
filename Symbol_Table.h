#ifndef FLIGHTS__SYMBOL_TABLE_H_
#define FLIGHTS__SYMBOL_TABLE_H_

#include <iostream>
#include "string"
#include "map"
#include "Var.h"
#include "Command.h"

using namespace std;
class Symbol_Table {
  // the local and remote vars
    map<string, Var *> *LocVars;
    map<string, Var *> *simVars;
    // oredered list of the vars
    vector<Var*> *orderedSimVars;

public:
    Symbol_Table();
  /**
  * @param key, value to add to the sim map.
  */
    void addToSimVars(string key, Var *value);
  /**
  * @param key, value to add to the local map.
  */
    void addToLocVars(string key, Var *value);
  /**
  * @return the local map field.
  */
    map<string, Var *> *getLocalMap();
  /**
  * @return the sim map field.
  */
    map<string, Var *> *getSimMap();
  /**
  * @return the ordered map field.
  */
    vector<Var*>* getOrderedSimMap();
    /**
    * @return filed of number of parameters
    */
    int getNumParam();
};

#endif //FLIGHTS__SYMBOL_TABLE_H_


