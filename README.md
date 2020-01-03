# Flight Simulator Interpreter FSI.

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

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
GitHub Link for the project: https://github.com/MorAl2/FlightSimulatorInterpreter
