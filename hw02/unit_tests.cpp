/*
 *  unit_tests.cpp
 *  Omar Elmady
 *  June 8
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  This file drives a CharLinkedList class with properties similar to std:vector 
 *
 */
#include <iostream>
#include "CharLinkedList.h"

using namespace std;

int main() {
    cout << "bismillah..." << endl;
    char w[] = "wow";
    CharLinkedList wow(w, 3);
    char am[] = "amazing";
    CharLinkedList amazing(am, 7);
    
    wow = amazing;
    CharLinkedList a;
    a.concatenate(&amazing);
    cout << wow.toString() << endl;
    cout << a.toString() << endl;
    cout << amazing.toString() << endl;

    try 
    {
        
    } 
    catch (const runtime_error &e) 
    {
        cerr << e.what() << endl;
    }

    cout << "alhamdulillah!" << endl;
    return 0;
}