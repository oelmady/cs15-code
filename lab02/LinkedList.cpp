/* 
 * LinkedList.cpp
 * 
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2020
 * Edited by Matt Russell, Juliana Vega, and Alexis Blair, Jan 2021 
 * 
 * An implementation of the LinkedList interface, the LinkedList can be used
 * to store Planets. 
 * 
 * NOTE: This is implemented using a singly-linked list with no back pointer.
 */
#include <iostream>
#include "LinkedList.h"

using namespace std;

/* Purpose: initializes an empty LinkedList */
LinkedList::LinkedList()
{
    front = nullptr;
    size  = 0;
}

LinkedList::~LinkedList() 
{
    if (size == 0) return;

    Node * current = front;
    Node * temp;
    while (current != nullptr)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
    front = nullptr;
}
/* print
 *    Purpose: Prints the list to the provided ostream
 * Parameters: an ostream to print to
 *    Returns: None
 */
void LinkedList::print(ostream &out) const
{
    out << "\nLinkedList of size " << this->size << "\n";
    out << "---------------------\n";
    
    Node *curr = this->front;
    while (curr != nullptr){
        curr->print(out);
        out << endl;
        curr = curr->next;
    }
       
    out << "\n" << endl;
}


/* ****************************************
 * TODO: implement the pushAtFront function
 * **************************************** 
 * pushAtFront
 *    Purpose: Adds a Planet to the front of the list
 * Parameters: The Planet to be added to the list
 *    Returns: None
 */
void LinkedList::pushAtFront(Planet p)
{
    Node * new_planet = new Node;
    new_planet->info = p;
    new_planet->next = front;
    front = new_planet;
    size++;
}


/* ****************************************
 * TODO: implement the reverse function
 * **************************************** 
 * reverse
 *    Purpose: reverses the list
 * Parameters: None
 *    Returns: None
 */
void LinkedList::reverse()
{
    if (front == nullptr || front->next == nullptr) 
    {
        return;
    }
    Node * current = front;
    Node * temp;
    Node * prev;

    while (current->next != nullptr) 
    {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    front = current;
    front->next = prev;
}

/* 
 * ****************************************
 * TODO: implement the pushAtBack function
 * ****************************************
 * pushAtBack
 *    Purpose: Adds a Planet to the back of the list
 * Parameters: The Planet to be added to the list
 *    Returns: None
 */
void LinkedList::pushAtBack(Planet p)
{
    Node * new_planet = new Node;
    new_planet->info = p;
    new_planet->next = nullptr;
    if (front == nullptr) 
    {
        front = new_planet;
        size++;
        return;
    }
    Node * last = front;

    while (last->next != nullptr) 
    {
        last = last->next;
    }
    last->next = new_planet;
    size++; 
}
