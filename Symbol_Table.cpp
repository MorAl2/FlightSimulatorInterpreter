//
// Created by mor on 18.12.2019.
//

#include "Symbol_Table.h"

Symbol_Table::Symbol_Table() {
  LocVars = new map<string, Var *>();
  simVars = new map<string, Var *>();
  orderedSimVars = new vector<Var *>();
  Var *tVar;

  // adding  all the values of the XML to the maps by XML order
  tVar = new Var("s", 0, "/instrumentation/airspeed-indicator/indicated-speed-kt", 0);
  simVars->emplace("/instrumentation/airspeed-indicator/indicated-speed-kt", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/sim/time/warp", 0);
  simVars->emplace("/sim/time/warp", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/switches/magnetos", 0);
  simVars->emplace("/controls/switches/magnetos", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/heading-indicator/offset-deg", 0);
  simVars->emplace("/instrumentation/heading-indicator/offset-deg", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/altimeter/indicated-altitude-ft", 0);
  simVars->emplace("/instrumentation/altimeter/indicated-altitude-ft", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/altimeter/pressure-alt-ft", 0);
  simVars->emplace("/instrumentation/altimeter/pressure-alt-ft", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/attitude-indicator/indicated-pitch-deg", 0);
  simVars->emplace("/instrumentation/attitude-indicator/indicated-pitch-deg", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/attitude-indicator/indicated-roll-deg", 0);
  simVars->emplace("/instrumentation/attitude-indicator/indicated-roll-deg", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/attitude-indicator/internal-pitch-deg", 0);
  simVars->emplace("/instrumentation/attitude-indicator/internal-pitch-deg", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/attitude-indicator/internal-roll-deg", 0);
  simVars->emplace("/instrumentation/attitude-indicator/internal-roll-deg", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/encoder/indicated-altitude-ft", 0);
  simVars->emplace("/instrumentation/encoder/indicated-altitude-ft", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/encoder/pressure-alt-ft", 0);
  simVars->emplace("/instrumentation/encoder/pressure-alt-ft", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/gps/indicated-altitude-ft", 0);
  simVars->emplace("/instrumentation/gps/indicated-altitude-ft", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/gps/indicated-ground-speed-kt", 0);
  simVars->emplace("/instrumentation/gps/indicated-ground-speed-kt", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/gps/indicated-vertical-speed", 0);
  simVars->emplace("/instrumentation/gps/indicated-vertical-speed", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/heading-indicator/indicated-heading-deg", 0);
  simVars->emplace("/instrumentation/heading-indicator/indicated-heading-deg", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/magnetic-compass/indicated-heading-deg", 0);
  simVars->emplace("/instrumentation/magnetic-compass/indicated-heading-deg", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/slip-skid-ball/indicated-slip-skid", 0);
  simVars->emplace("/instrumentation/slip-skid-ball/indicated-slip-skid", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/turn-indicator/indicated-turn-rate", 0);
  simVars->emplace("/instrumentation/turn-indicator/indicated-turn-rate", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0);
  simVars->emplace("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/flight/aileron", 0);
  simVars->emplace("/controls/flight/aileron", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/flight/elevator", 0);
  simVars->emplace("/controls/flight/elevator", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/flight/rudder", 0);
  simVars->emplace("/controls/flight/rudder", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/flight/flaps", 0);
  simVars->emplace("/controls/flight/flaps", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/engines/engine/throttle", 0);
  simVars->emplace("/controls/engines/engine/throttle", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/engines/current-engine/throttle", 0);
  simVars->emplace("/controls/engines/current-engine/throttle", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/switches/master-avionics", 0);
  simVars->emplace("/controls/switches/master-avionics", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/switches/starter", 0);
  simVars->emplace("/controls/switches/starter", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/engines/active-engine/auto-start", 0);
  simVars->emplace("/engines/active-engine/auto-start", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/flight/speedbrake", 0);
  simVars->emplace("/controls/flight/speedbrake", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/sim/model/c172p/brake-parking", 0);
  simVars->emplace("/sim/model/c172p/brake-parking", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/engines/engine/primer", 0);
  simVars->emplace("/controls/engines/engine/primer", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/engines/current-engine/mixture", 0);
  simVars->emplace("/controls/engines/current-engine/mixture", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/switches/master-bat", 0);
  simVars->emplace("/controls/switches/master-bat", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/controls/switches/master-alt", 0);
  simVars->emplace("/controls/switches/master-alt", tVar);
  orderedSimVars->push_back(tVar);
  tVar = new Var("s", 0, "/engines/engine/rpm", 0);
  simVars->emplace("/engines/engine/rpm", tVar);
  orderedSimVars->push_back(tVar);
}

// adding new Var to the remote vars list
void Symbol_Table::addToSimVars(string key, Var *value) {
  LocVars->emplace(key, value);
}
// adding new Var to the local vars list
void Symbol_Table::addToLocVars(string key, Var *value) {
  LocVars->emplace(key, value);
}
// getting the local Vars Map
map<string, Var *> *Symbol_Table::getLocalMap() {
  return LocVars;
}
// getting the remote Vars Map
map<string, Var *> *Symbol_Table::getSimMap() {
  return simVars;
}
// getting the ordered remote Vars Map
vector<Var *> *Symbol_Table::getOrderedSimMap() {
  return orderedSimVars;
}