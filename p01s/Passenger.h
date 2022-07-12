/*
 The Passenger class creates instances of passengers with an id, a starting station, and a destination. Passengers are initialized with all three parameters, or otherwise no valid values. 

Author: Omar Elmady 
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>
#include <string>
using namespace std;

struct Passenger
{

	int id, from, to;

	Passenger()
	{
		id   = -1;
		from = -1;
		to   = -1;
	}

	Passenger(int newId, int arrivalStation, int departureStation)
	{
		id   = newId;
		from = arrivalStation;
		to   = departureStation;
	}

	void print(std::ostream &out);

};

#endif
