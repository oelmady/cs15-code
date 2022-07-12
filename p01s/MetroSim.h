/*
Defines the metro sim driver, containing functions for interpreting user commands when using the program. 
this class uniquely records the number of passengers in the simulation.
*/
#ifndef _METROSIM_H_
#define _METROSIM_H_

class MetroSim
{
public:
    MetroSim() { on = true; }
    void stop();
    void move();
    void addPassenger(int from, int to);
    void readStations(string stationName);
    void readCommand(string command);

    int numPassengers = 0;
    Metro metro;
    bool on;
    string output;
};

#endif