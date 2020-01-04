#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "openDataServer.h"
#include "thread"

// checking if the string supllied is a valid Double Number.
bool isValidDouble(string exp) {
  // checking eahc char if valid.
  int dotCount = 0;
  unsigned int j = 0;
  if (exp[0] == '-') {
    j++;
  }
  for (unsigned int i = j; i < exp.length(); i++) {
    if (!isdigit(exp[i]) && (i == 0 || i == exp.length() - 1)) {
      return false;
    }
    if (!isdigit(exp[i]) && exp[i] != '.') {
      return false;
    }
    if (exp[i] == '.') {
      dotCount++;
    }
    if (dotCount >= 2)
      return false;
  }
  return true;
}

// Creating the server socket and waiting for Connection from the simulator
void runServer(int port, openDataServer *thisClass) {
  // creating the socket.
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    // Error
    cout << "Error-Socket" << endl;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  // binding the socket.
  if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    // Error
    cout << "Error-Bind" << port <<  endl;
    throw "Error-Bind";
  }
  // listening for connections.
  if (listen(sockfd, 5) == -1) {
    // Error
    cout << "Error-Listen" << endl;
    throw "Error-Listen";

  }
  cout << "Waiting..... Server" << endl;

  // accepting clients
  int client_socket = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &address);
  cout << "got Connection Server" << endl;
  // saving the client number in a field.
  thisClass->setClientSocket(client_socket);
  thisClass->setSocketNum(sockfd);
}

// receving data from the simulator
void rcvData(int client_socket, openDataServer *thisClass) {
  // rcv buffer
  char buffer[4096] = {0};
  // keeping the thread alive until the main is done.
  while (!(*(thisClass->getIsDone()))) {
    // reading the data from the simulator.
    int valread = read(client_socket, buffer, 4096);
    // id the data isn't valid.
    if (buffer[0] == '\n') {
      continue;
    }
    // making a string of the data.
    string strBuff(buffer);
    // making a substring by the /n divider
    strBuff = strBuff.substr(0, strBuff.find_first_of('\n'));
    if (strBuff.length() < 36) {
      continue;
    }
    // the remote vars
    map<string, Var *> *simVars = thisClass->getSym()->getSimMap();
    // the remote orderes vars
    vector<Var *> *orederdSim = thisClass->getSym()->getOrderedSimMap();
    // splliting the data by ,
    int start = 0;
    int end = strBuff.find_first_of(',');
    // if ' wasnt found
    if (end == -1) {
      continue;
    }
    // going over all the Vars order
    for (auto const &x : *orederdSim) {
      // checking if its a valid value and if the Var is a sim changing var
      if (x->getSide() == 1 || isValidDouble(strBuff.substr(start, end - start)) == false
          || strBuff.substr(start, end - start) == "") {
        strBuff[end] = '-';
        start = end + 1;
        end = strBuff.find_first_of(',');
        if (end == string::npos) {
          end = strBuff.length();
        }
        if (end > strBuff.length() || start > strBuff.length()) {
          break;
        }
        continue;
      }
      // entering the new value to the Var from the sim data
      x->updateValue(stod(strBuff.substr(start, end - start)));
      // adding the var to the Interperter Var map from ex1
      try {
        thisClass->getInter()->addToMap(x->getName(), x->getVal());
      }
      catch (...) {
      }
      // updating the subtring postion for the next data
      strBuff[end] = '-';
      start = end + 1;
      end = strBuff.find_first_of(',');
      // if we get to the end of the string making it the last position
      if (end == string::npos) {
        end = strBuff.length();
      }
      if (end > strBuff.length() || start > strBuff.length()) {
        break;
      }
    }
  }
// the thread is done. closing the socket.
  close(client_socket);
  close(thisClass->getSocketNum());
  return;
}

int openDataServer::execute() {
  // runing the open server thread and waiting for connections.
  thread *run = new thread(runServer, openDataServer::port, this);
  run->join();
  // rcving data from the sim and updating the vars
  thread *rcv = new thread(rcvData, openDataServer::client_socket, this);
  rcv->detach();
  return this->numParam + 1;
}
// setting the params for the server
void openDataServer::setParam(string array[], int index, Interpreter *i) {
  this->numParam = 1;
  this->interpreter = i;
  this->port = interpreter->interpret(this->removeSpaces(array[index + 1]))->calculate();
}
// removing spaces from the strings
string openDataServer::removeSpaces(std::__cxx11::string str) {
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
// getting the # of params
int openDataServer::getNumParam() {
  return this->numParam;
}
// setting the socket number.
void openDataServer::setClientSocket(int client) {
  openDataServer::client_socket = client;
}
// getting the isDone field.
bool *openDataServer::getIsDone() {
  return isDone;
}
// getting the sym table.
Symbol_Table *openDataServer::getSym() {
  return sym;
}
// getting the interptrer of the program.
Interpreter *openDataServer::getInter() {
  return interpreter;
}
// constructor.
openDataServer::openDataServer(Symbol_Table *s, Interpreter *i, bool *is) {
  sym = s;
  interpreter = i;
  isDone = is;
}

void openDataServer::setSocketNum(int num) {
  openDataServer::socketNum = num;
}

int openDataServer::getSocketNum() {
  return openDataServer::socketNum;
}