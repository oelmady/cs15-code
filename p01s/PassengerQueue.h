/*
The PassengerQueue class defines the functionality for the metro simulator, adding and removing passengers from queues in the metro simulator.
*this class manages the placement of passengers in memory, and can delete or move data of class Passenger.
*/

#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include <iostream>
#include <string>
#include <list>

#include "Passenger.h"

class PassengerQueue
{
public:
    PassengerQueue() {};
    PassengerQueue(string str) { name = str; };
    Passenger front() const;
    void dequeue();
    void enqueue(const Passenger &p);
    int size();
    void print(std::ostream &os);
    string name;
    std::list<Passenger> queue;
    int length = 0;
};

#endif