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
    CharLinkedList t('t');

    char abby[] = "abbycat";
    CharLinkedList ll1(abby, 7);
    CharLinkedList ll2 = ll1;
    cout << "testing cat" << endl;
    t.concatenate(&ll2);

    cout << "printing t: " << t.toString() << endl;

    cout << "alhamdulillah!" << endl;
    return 0;
}