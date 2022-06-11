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

    char followX[] = {'0', '1', '2', '3', 'X', '5', '6', '7', '8'};
    CharLinkedList list1(followX, 9);
    cout << list1.toString() << endl;

    try
    {
        // test elementAt() while removing elements from front and back of 
        // list. We keep track of the 'X' in the middle as we make each pass in
        // the for loop.
        for (int i = 0; i < 8; i++) {
            if (i % 2 == 0) {
                list1.popFromBack();
                if (list1.elementAt(list1.size() / 2) != 'X') {
                    throw std::runtime_error("elementAt() was incorrect!");
                }
            } else {
                list1.popFromFront();
                if (list1.elementAt((list1.size() / 2)) != 'X') {
                    throw std::runtime_error("elementAt() was incorrect!");
                }
            }
            cout << list1.toString() << endl;
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    

    std::cout << "Student correctly kept track of elementAt() while removing "
                 "elements."
              << std::endl;

    cout << "alhamdulillah!" << endl;
    return 0;
}