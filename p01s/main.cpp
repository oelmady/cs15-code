/*
 Users of the simulation interface with the program using this file as a driver. When running then simulation, users can input commands to 
 1) add a new passenger to the simulation, 
 2) move the train to the next stop, 
 3) end the simulation.
 */
#include "Passenger.h"
#include "PassengerQueue.h"
#include "Metro.h"
#include "MetroSim.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string error;
	if (argc < 3 || argc > 4) {
		error = "Usage: ./MetroSim stationsFile outputFile [commandsFile]";
		cerr << error << endl;
		return -1;
	}
	ifstream stations;
	stations.open(argv[1]);
	if (!stations) {
		error = "Error: could not open file" + to_string(*argv[1]);
		cerr << error << endl;
		return -1;
	}
	ofstream output;
	output.open(argv[2]);
	if (!output) {
		error = "Error: could not open file" + to_string(*argv[2]);
		cerr << error << endl;
		return -1;
	}
	ifstream commands;
	if (argc == 4) {
		commands.open(argv[3]);
		if (!commands){
			error = "Error: could not open file" + to_string(*argv[3]);
			cerr << error << endl;
			return -1;
		}
	}

	MetroSim m;

	string stationName;
    while ( getline(stations, stationName)){
		m.readStations(stationName);
	}
	stations.close();

	string command;
	if (argc == 4){
		while( getline(commands, command)) {
			m.readCommand(command);
		}
		commands.close();
	}
	else {
		while (m.on) {
			cout << "Command? ";
			getline(cin, command);
			m.readCommand(command);
		}
	}
	// remove one trailing nextline char ?
	// m.output = m.output.substr(0, m.output.length() - 1);
	output << m.output << endl;
	output.close();

	return 0;
}
