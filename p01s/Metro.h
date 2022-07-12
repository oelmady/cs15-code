/*
 * This file contains the header functions for the Metro class, which can enqueue, dequeue, and print passengers and stations on the Metro route of the metro sim
 */

#ifndef _Metro_H_
#define _Metro_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Metro
{
public:
    void addToStation(const Passenger &p);
    void moveTrain();
    void printTrain();
    void newStation(string stationName);
    int currentStation = 0;
    string departFromTrain();
private:
    string farewell(const Passenger &p);
    int numStations = 0;
    std::vector<PassengerQueue> stations; //named stations
    std::vector<PassengerQueue> train;
};

#endif
