/*
 *  CharLinkedList.cpp
 *  Omar Elmady
 *  June 8
 *
 *  CS 15 HW 2
 *
 *  This file defines the functions involved in implementing a CharLinkedList class with properties similar to std:vector using linked lists. This class only accepts char type data as input for the list. 
 *
 */

#include "CharLinkedList.h"
#include <iostream>

using namespace std;
//The default constructor takes no parameters and initializes an empty list with no nodes.
CharLinkedList::CharLinkedList()
{
    front  = nullptr;
    back   = nullptr;
    length = 0;
}

//helper function for destructor that recursively frees node data of each node.
void CharLinkedList::destroy(Node *node) 
{
    if (node == nullptr) return;

    Node * next = node->next;
    delete node;

    if (next != nullptr)
    {
        destroy(next);
    }
}

//Define a destructor that destroys/deletes/recycles all heap-allocated data in the cur- rent list. It has no parameters and returns nothing. This function uses a private recursive helper function destroy(Node *front).
CharLinkedList::~CharLinkedList()
{
    if (!isEmpty())
    {
        destroy(front);
    }
}

//A size function that takes no parameters and returns an integer value that is the number of characters in the list. The size of a list is 0 if and only if it isEmpty.
int CharLinkedList::size() const
{  
    return length;
    int result = 0;
    Node * temp = front;
    while (temp != nullptr) 
    {
        result++;
        temp = temp->next;
    }
    return result;
}

//An isEmpty function that takes no parameters and returns a boolean value that is true if this specific instance of the class is empty (has no characters) and false otherwise.
bool CharLinkedList::isEmpty() const
{
    return (front == nullptr);
}

//this constructor takes in a single character as a parameter and creates a one element list consisting of that character. 
CharLinkedList::CharLinkedList(char c)
{
    front  = new Node{c};
    back   = front;
    length = 1;
}

//A first function that takes no parameters and returns the first element (char) in the list. If the list is empty it should throw a C++ std::runtime_error exception with the message “cannot get first of empty LinkedList”.
char CharLinkedList::first() const
{
    if (isEmpty())
    {
        throw std::runtime_error("cannot get first of empty LinkedList");
    }
    return front->data;
}

// a recursive constructor that takes  a pointer to a head node and creates a deep copy of all nodes in the list
CharLinkedList::Node* CharLinkedList::copyRec(Node *node)
{
    if (node == nullptr) return nullptr;

    Node * newNode = new Node{node->data};
    newNode->next = copyRec(node->next);

    return newNode;
}

//A copy constructor for the class that makes a deep copy of a given instance.
CharLinkedList::CharLinkedList(const CharLinkedList &other)
{
    // if (this == other) return;
    if (other.length == 0) 
    {
        this->clear();
    }
    this->length = other.length;

    this->front = copyRec(other.front);
    this->back  = getBack(this->front);
}

//A clear function that takes no parameters and has a void return type. It makes the instance into an empty list using the recurisve destroy(*node) function.
void CharLinkedList::clear()
{
    if (!isEmpty())
    {
        destroy(front);
    }
    front  = nullptr;
    back   = nullptr;
    length = 0;
}

//A last function that takes no parameters and returns the last element (char) in the list. If the list is empty it throws a C++ std::runtime_error exception with the message “cannot get last of empty LinkedList”.
char CharLinkedList::last() const
{
    if (isEmpty()) 
    {
        throw std::runtime_error("cannot get last of empty linked list");
    }
    return back->data;
}

//A pushAtBack function that takes an element (char) and has a void return type. It inserts the given new element after the end of the existing elements of the list.
void CharLinkedList::pushAtBack(char c)
{
    Node * node = new Node{c, nullptr};
    back->next = node;
    back = node;
    length++;
}

//A pushAtFront function that takes an element (char) and has a void return type. It inserts the given new element in front of the existing elements of the list.
void CharLinkedList::pushAtFront(char c)
{
    Node * node = new Node{c, front};
    front = node;
    length++;
}

//An elementAt function that takes an integer index and returns the element (char) in the list at that index. NOTE: Indices are 0-based. If the index is out of range it should throw a C++ std::range_error exception with the message “index (IDX) not in range [0..SIZE)” where IDX is the index that was given and SIZE is the size of the linked list.
char CharLinkedList::elementAt(int index) const
{
    if (index < 0 || index >= size())
    {
        string msg = "index (" + to_string(index) + ") is not in range [0.." + to_string(size()) + ")";
        throw std::range_error(msg);
    }

    if (index == 0) return first();
    else if (index == size()) return last();

    Node * nextNode = front;
    for (int i = 0; i < index; i++) 
    {
        nextNode = nextNode->next;
    }
    return nextNode->data;
} 

//A toString function that takes no parameters and has a std::string return type. It returns a string which contains the characters of the CharLinkedList. The string will be formatted like this:
// [CharLinkedList of size 5 <<Alice >>]
string CharLinkedList::toString() const
{
    string msg = "[CharLinkedList of size " + to_string(length);
    msg +=  " <<";
    Node * node = front;
    char data;
    for (int i = 0; i < length; i++)
    {
        data = node->data;
        msg += data;
        node = node->next;
    }
    msg += ">>]";
    return msg;
}

//An insertAt function that takes an element (char) and an integer index as parameters and has a void return type. It inserts the new element at the specified index. The new element is then in the index-th position. If the index is out of range it should throw a C++ std::range_error exception with the message “index (IDX) not in range [0..SIZE]” where IDX is the index that was given and SIZE is the size of the list.
void CharLinkedList::insertAt(char c, int index)
{
    if (index < 0 || index > size())
    {
        string msg = "index (" + to_string(index) + ") is not in range [0.." + to_string(size()) + "]";
        throw std::range_error(msg);
    }
    if (index == size()) 
    {
        pushAtBack(c);
    }
    else if (index == 0)
    {
        pushAtFront(c);
    }
    else
    {
        Node * newNode = new Node{c};
        Node * prev = front;
        for (int i = 1; i < index; i++)
        {
            prev = prev->next;
        }
        newNode->next = prev->next;
        prev->next = newNode;
        length++;
    }
}

//An insertInOrder function that takes an element (char), inserts it into the list in alphabetical order, and returns nothing. When this function is called, it should insert the element at the first index after which some character greater than the inserted character appears.
void CharLinkedList::insertInOrder(char c) 
{
    length++;
    Node * temp = new Node{c, front};
    if (front == nullptr) 
    {
        front  = temp;
        back   = temp;
        return;
    }
    Node * greater = front;
    char data = greater->data;
    while (greater->next != nullptr) 
    {
        if (data > c) break; 
        greater = greater->next;
        data    = greater->data;
    }
    temp->next = greater->next;
    greater->next = temp;
    if (temp->next == nullptr) back = temp;
}
//A popFromFront function that takes no parameters and has void return type. It removes the first element from the list. If the list is empty, it should throw a C++ std::runtime_error exception with message“cannot pop from empty LinkedList”.
void CharLinkedList::popFromFront() 
{
    if (isEmpty()) 
    {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }
    Node * newFront = front->next;
    free(front);
    length--;
    front = newFront;
}
//A popFromBack function that takes no parameters and has void return type. It removes the last element from the list. If the list is empty, the function should throw a C++ std::runtime_error exception with message “cannot pop from empty LinkedList”.
void CharLinkedList::popFromBack()
{
    if (isEmpty())
    {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }
    free(back);
    length--;
    back = getBack(front);
}

//A removeAt function that takes an integer index and has void return type. It removes the element at the specified index. If the index is out of range it should throw a C++ std::range_error exception with message “index (IDX) not in range [0..SIZE)” where IDX is the input index and SIZE is the size of the list.
void CharLinkedList::removeAt(int index)
{
    if (index < 0 || index >= size())
    {
        string msg = "index (" + to_string(index) + ") is not in range [0.." + to_string(size()) + ")";
        throw std::range_error(msg);
    }
    if (index == 0)
    {
        popFromFront();
    }
    else if (index == size())
    {
        popFromBack();
    }
    else // index > 1 && index < size()
    {
        Node * rem = front;
        Node * prev;
        for (int i = 0; i < index; i++) 
        {
            prev = rem;
            rem = rem->next;
        }
        prev->next = rem->next;
        free(rem);
        length--;
    }
}

//A replaceAt function that takes an element (char) and an integer index as parameters and has a void return type. It replaces the element at the specified index with the new element. If the index is out of range it should throw a C++ std::range_error exception with the message “index (IDX) not in range [0..SIZE)” where IDX is the index that was given and SIZE is the size of the list.
void CharLinkedList::replaceAt(char c, int index)
{
    if (index < 0 || index >= size())
    {
        string msg = "index (" + to_string(index) + ") is not in range [0.." + to_string(size()) + ")";
        throw std::range_error(msg);
    }
    if (index == 0) 
    {
        front->data = c;
    }
    else if (index == size())
    {
        back->data = c;
    }
    else
    {
        Node * repl = front->next;
        for (int i = 1; i < index; i++)
        {
            repl = repl->next;
        }
        repl->data = c;
    }
}

//A concatenate function that takes a pointer to a CharLinkedList and has void re- turn type. It adds a copy of the list pointed to by the parameter to the end of the list on which the function was called.
void CharLinkedList::concatenate(CharLinkedList *other) 
{
    if (other->length == 0) return;
    if (this->length == 0) 
    {
        Node * node = new Node{other->front->data};
        front = back = node;
    }
    this->back->next = copyRec(other->front);
    this->back = getBack(this->back);
    this->length += other->length;
}

//This constructor takes an array of characters and the integer length of that array of characters as parameters. It will create a list containing the characters in the array. 
// incorrect result if size != length(arr[])
CharLinkedList::CharLinkedList(char arr[], int size)
{
    length = size;
    front = new Node{arr[0]};
    Node * prev = front;
    for (int i = 1; i < size; i++)
    {
        Node * node = new Node{arr[i]};
        prev->next = node;
        prev = node;
    }
    prev->next = nullptr;
    back = prev;
}
//Define an assignment operator for the class that recycles the storage associated with the instance on the left of the assignment and makes a deep copy of the instance on the right hand side into the instance on the left hand side.
CharLinkedList& CharLinkedList::operator=(const CharLinkedList &other)
{
    if (this->length > 0) this->clear();
    this->length = other.length;
    this->front  = copyRec(other.front);
    this->back   = getBack(this->front);
    return *this;
}
// returns a pointer to the node at the back of the list
CharLinkedList::Node* CharLinkedList::getBack(Node *node)
{
    while (node->next != nullptr)
    {
        node = node->next;
    }
    return node;
}