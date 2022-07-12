/*
 * This file implements the user-facing functions of the command line when running the metro simulation. 
 */

#include "Metro.h"
#include "Passenger.h"
#include "MetroSim.h"

#include <string>
#include <vector>
#include <sstream>

using namespace std;
// Stop the simulation and exit the program, printing exit message
// when the simulation terminates, the default destructor of the MetroSim, Metro, PassengerQueue,and Passenger classes will garbage collect all data automatically.
void MetroSim::stop()
{
    on = false;
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/*
disembarks all passengers arriving at the current station and adds their farewell statements to output, then moves the train forward one stop and boards passengers at the next station. the print function will indicate the train is present at the next station, and all passengers will at that station will have boarded
*/
void MetroSim::move()
{
    metro.moveTrain();
    output += metro.departFromTrain();
    metro.printTrain();
}

/*
adds a new passenger to the simulation, which is initialized with an id and assigned to the station "from" 
*/
void MetroSim::addPassenger(int from, int to)
{
    Passenger *p = new Passenger(++numPassengers, from, to);
    metro.addToStation(*p);
}

// reads the names of the stations in stationsFile in order and assigns new stations to the metro
void MetroSim::readStations(string stationName)
{
    metro.newStation(stationName);
}

// reads the command as a line and performs the appropriate function call
void MetroSim::readCommand(string command)
{
    if (command == "m f") { 
        stop(); 
    }
    else if (command == "m m") { 
        move(); 
    }
    else if (command[0] == 'p') {
        stringstream ss(command);
        int from, to;
        string buff;
        vector<string> args;
        while (ss >> buff){
            args.push_back(buff);
        }
        from = stoi(args[1]);
        to   = stoi(args[2]);
        addPassenger(from, to);
    }
}
