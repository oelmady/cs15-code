// testing functionality of PQ
#include "Passenger.h"
#include "PassengerQueue.h"

using namespace std;

int main()
{
    PassengerQueue q("dh");
    Passenger a(1,2,3);
    Passenger b(2,1,2);
    Passenger c(3,1,2);
    q.enqueue(a);
    q.enqueue(b);
    q.enqueue(c);
    q.print(cout);
}