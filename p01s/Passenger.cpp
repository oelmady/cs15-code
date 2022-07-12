/*
 * this file implements the print function for the passenger class
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
Prints to output stream the following 
[ID, TO->FROM]

 */
void Passenger::print(std::ostream &out)
{
	string p = "[" + to_string(id) + ", " + to_string(from) + "->" + to_string(to) + "]";
	out << p;
}
