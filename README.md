# Flight Simulator Interpreter FSI.(https://github.com/MorAl2/FlightSimulatorInterpreter)

FSI is a imaginary Programming language Interpreter aimed for Controling and Flying Planes in the FlightGear Flight Simulator, Built using Sockets and Multi-Threading.

## Installation

Compile the files by Running The following Command:
"g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread"
** g++ must be Installed Beforehand by using "sudo apt-get install g++" 

## Usage

The program takes as CommandLine Argument the txt file you wish to Interpret.
for Example if you wish to run The file fly.txt the following command should execute:
"./a.out fly.txt".

The program should show it waits for connection.

Afterwards run the FlightGear Simulator or Alternatively Run the script Simulating it, the program should print it Accepted connection for both the server thread and the client thread, and will start interpreting the file supplied to it.

The Following Commands Are Allowed:

openDataServer(port) - open server using sockets for the simulator to send data 

connectControlClient(ip, port) - open client socket and connecting to the simulator for changing controls of the plane.

var - creating a new var , 
can be simluator depending/changing var - will be declered by (->) for changing and (<-) for depending or non for exapmple: 
(var h0 = 3)
 (var breaks -> sim(** breaks path**) will change the simualtor breaks.)
 (var alt <- sim(** altitude path**) will be changed by the data supplied by the simulator.)

Print(data) - print the paramater supplied to it can be string or expession.
   
Sleep(time) - stops the main thread for the specified time, can be string or expession.
   
while(condition) { commands } - while loop, can accapt only 1 condition.
   
if(conddition) { command } - will execute the commands only if the condition is true.
    
also the use of functions is Allowed but must be Declared Before the call to the function.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
GitHub Link for the project: https://github.com/MorAl2/FlightSimulatorInterpreter
