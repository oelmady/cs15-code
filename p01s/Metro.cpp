/*
This file implements the functions of the Metro class, which is responsible for managing the status of Passengers in the Metro sim. This class uses the PassengerQueue and Passenger classes to modify data representations of the metro compartments and its stations.
*/

#include "Passenger.h"
#include "PassengerQueue.h"
#include "Metro.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// adds a passenger to the station of the metro they are departing from
void Metro::addToStation(const Passenger &p)
{
    stations[p.from].enqueue(p);
}

// a function that creates a new station with the name stationName and appends it to the metro, incrementing the number of stations by 1
// also expands the size of the train
void Metro::newStation(string stationName)
{
    PassengerQueue *station = new PassengerQueue(stationName);
    stations.emplace_back(*station);
    numStations++;
    train.resize(numStations);
}

// a function that removes all passengers on the train departing at the current station, and returns a string of newline-separated data of each passenger who departs in order of their arrival into the train compartment, front to back
string Metro::departFromTrain()
{
    string output = "";
    auto& departure = train[currentStation];

    while (departure.size() > 0) {
        Passenger p = departure.front();
        output += farewell(p);
        departure.dequeue();
    }
    return output;
}

// a private helper function that returns the string data of a departing passenger 
string Metro::farewell(const Passenger &p)
{
    string message = "Passenger " + to_string(p.id) + " left train at station " + stations[p.to].name + "\n";
    return message;
}

// incrememnts the train's position and boards all passengers at the current station to their departure compartment
void Metro::moveTrain()
{
    currentStation = (currentStation + 1) % numStations;
    while (stations[currentStation].length > 0){
        Passenger p = stations[currentStation].front();
        train[p.to].enqueue(p);
        stations[currentStation].dequeue();
    }
}

// prints the contents of the metro 
// on the first line prints all boarded passengers
// on each subsequent line, prints the passengers waiting at that station 
//also prints the location of the train
void Metro::printTrain()
{
    cout << "Passengers on the train: {";
    for (int i = 0; i < numStations; i++){
        auto& compartment = train[i];
        compartment.print(cout);
    }
    cout << "}" << endl;

    for (int i = 0; i < numStations; i++){
        if (i == currentStation) {
            cout << "TRAIN: ";
        }
        else { 
            cout << "       "; 
        }
        auto& dest = stations[i];
        cout << "[" << i << "] " << dest.name << " {";
        dest.print(cout);
        cout << "}" << endl;
    }
}