#include "connectControlClient.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "openDataServer.h"
#include "thread"
#include "string.h"
#include "arpa/inet.h"

// crating the socket and connecting the to simulatort
void runClient(const char *ip, int port, connectControlClient *thisClass) {
  // creating the socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    // Error
    cout << "Error-Socket" << endl;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip);
  address.sin_port = htons(port);

  cout << "Waiting.....Client" << endl;

  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  // trying to connect again and again to the simulator.
  while (is_connect == -1) {
    sleep(1);
    cout << "trying to connect" << endl;
    is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  }
  cout << "got Connection Client" << endl;
  //getting the connections and setting the client number.
  thisClass->setClient(client_socket);
}
//
void sndData(int client_socket, connectControlClient *thisClass) {
  string msg;
  // runiing the thread.
  while (!*(thisClass->getIsDone())) {
    auto vars = thisClass->getSym()->getSimMap();
    // going on all the Vars
    for (auto const &x : *vars) {
      // checking if the var is sim chaning and it there is a new data.
      if (x.second->getChanged() && x.second->getSide() == 1) {
        x.second->setChanged(false);
        // sending the new data.
        msg = "set " + x.second->getSim() + " " + to_string(x.second->getVal()) + "\r\n";
        int is_sent = send(thisClass->getClient(), msg.c_str(), msg.length(), 0);
        if (is_sent == -1) {
          cout << "The Message Wasn't sent: " + msg << endl;
        }
      }
    }
  }
  // closing the socket.
  close(client_socket);
}
// executing the data.
int connectControlClient::execute() {
  // setting the params.
  this->port = (int) interpreter->interpret(this->portAsString)->calculate();
  // creting the socket and waiting to connect.
  thread run(runClient, connectControlClient::ip.c_str(), connectControlClient::port, this);
  run.join();
  // sending new data to the sim.
  thread *rcv = new thread(sndData, connectControlClient::client_Socket, this);
  rcv->detach();
  return this->numParam + 1;
}
// setting the params for the command.
void connectControlClient::setParam(string array[], int index, Interpreter *i) {
  this->numParam = 2;
  this->interpreter = i;
  string tempIp = array[index + 1];
  this->portAsString = array[index + 2];
  if (tempIp.find("\"") != -1) {
    tempIp = tempIp.substr(1, tempIp.length() - 2);
    this->ip = tempIp;
  }
  if (this->portAsString.find("\"") != -1) {
    this->portAsString = this->portAsString.substr(1, this->portAsString.length() - 2);
    this->port = stoi(this->portAsString);
  } else {
    this->portAsString = this->removeSpaces(this->portAsString);
  }
}
// removing spaces from the string.
string connectControlClient::removeSpaces(string str) {
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
// getting the # of data.
int connectControlClient::getNumParam() {
  return this->numParam;
}
// constructor.
connectControlClient::connectControlClient(Symbol_Table *symVal, bool *is) {
  sym = symVal;
  isDone = is;
}
// the isDone field for the thread.
bool *connectControlClient::getIsDone() {
  return isDone;
}
// setting the client number.
void connectControlClient::setClient(int cs) {
  client_Socket = cs;
}
// getting the client number.
int connectControlClient::getClient() {
  return client_Socket;
}
// getting the Symbol Table
Symbol_Table *connectControlClient::getSym() {
  return sym;
}
