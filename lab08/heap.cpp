/* Comp 15 Lab 9: Heaps 
 * Implementation of Heap class with string keys
 * Updated 11/2/2020 by Ellis Brown
 * Edited by: 
 */

#include <iostream>

#include "heap.h"

using namespace std;

/*
 * Default constructor
 */
Heap::Heap()
{
        heap        = new string[INIT_SIZE];
        heapSize    = 0;
        maxCapacity = INIT_SIZE;
}

/*
 * Destructor
 */
Heap::~Heap()
{
        delete [] heap;
}

/*
 * intialize a heap from an array
 */
Heap::Heap(string list[], int listSize)
{
        heap        = new string[listSize + 1];
        maxCapacity = listSize + 1;

        // Remember our implementation of a heap
        // starts at 1 not zero, so we store a
        // nonce value at index 0.
        // Don't use the fact that this value is there:
        // Clients could store this string in their heap!
        // Just remember index 0 is not used
        heap[0] = "I'M NOT PART OF THE HEAP";

        // copy the unsorted list over
        for (int i = 0; i < listSize; i++) {
                heap[i + 1] = list[i]; //notice indexing

        }
        heapSize = listSize;
        cout << heap[1];
        // use the build heap function
        // to make unsorted array into a heap
        buildHeap();
}

/*
 * insert a string into the heap. 
 * requires the function upHeap to be implemented
 */
void Heap::insert(string s)
{
        // NB:  We do not use slot zero in the array
        // The array is thus already of size (heapSize + 1)
        // But we want to add one more element, so we
        // need an array of size (heapSize + 2)
        ensureCapacity(heapSize + 2);

        // first, satisfy the shape invariant:
        // location to insert is heapSize + 1
        // (Recall, 0th location not used)
        heap[heapSize + 1] = s;
        heapSize++;
        cout << heapSize << " ";
        // re-establish the heap invariant
        //heapSize is the index with our inserted element
        upHeap(heapSize); 
}

/*
 * return smallest element in heap
 */
string Heap::min()
{
        return heap[1];
}

/*
 * remove and return smallest element in heap
 */
string Heap::removeMin()
{
        string min = heap[1];
        cout << "old min: " << min;
        heap[1] = "";
        downHeap(1);
        cout << ", new min: " << min;
        return min;
        
}

/*
 * return size of heap
 */
int Heap::size()
{
        return heapSize;
}

/*
 * downHeap establishes/verifies heap invariant from given 
 * location down to leaves
 * if parent is out of order with respect to children,
 * swap with smaller child and downHeap from updated child
 * Note: is only called on index <= heapSize / 2
 */
void Heap::downHeap(int location)
{
        string parent = heap[location];
        string left   = heap[leftChild(location)];
        string right  = heap[rightChild(location)];

        string temp;
        if (left != "" && 
        (right == "" || 
        (right != "" && left < right))){
                if (left < parent){
                        temp   = left;
                        left   = parent;
                        parent = temp;
                        downHeap(leftChild(location));
                }
        } else if (right != "" && 
        (left == "" || 
        (left != "" && right < left))){
                if (right < parent){
                        temp   = right;
                        right  = parent;
                        parent = temp;
                        downHeap(rightChild(location));
                }
        } 
}

/* NOT required for this lab, but you can write it if you have time
 * upHeap reestablishes heap invariant from given node to root
 * If child is out of order with respect to parent, swap and
 * continue to upHeap from parent to root
 */
void Heap::upHeap(int location)
{
        string child  = heap[location];
        string p = heap[parent(location)];
        string temp = child;
        if (child < p){
                child  = p;
                p = temp;
                upHeap(parent(location));
        }
}

/*
 * creates a heap out of the unsorted array.
 * Naive algorithm is O(n log n)
 * Algorithm from class/prelab is O(n) (proof in 160)
 */
void Heap::buildHeap()
{
        for (int i = heapSize / 2; i > 0; i--){
                downHeap(i);
        }
}

/*
 * Return left child for element at given index
 */
int Heap::leftChild(int index)
{
        return index * 2;
}

/*
 * Return right child for element at given index
 */
int Heap::rightChild(int index)
{
        return (index * 2) + 1;

}

/*
 * Return the parent for element at given index
 */
int Heap::parent(int index)
{
        return index / 2; // note integer division
}

/* 
 * Purpose: Ensure heap array has at least the desired capacity.
 */
void Heap::ensureCapacity(int desiredCapacity)
{
        if (maxCapacity >= desiredCapacity)
                        return;  // Nothing to do:  array is big enough

        // otherwise, expand
        int     newCapacity = max(desiredCapacity, 2 * maxCapacity + 2);
        string *newArray    = new string[newCapacity];

        // dutifully copying unused slot 0
        // Note elements occupy slots 1 .. heapSize, inclusive
        for (int i = 0; i < heapSize + 1; ++i) {
                newArray[i] = heap[i];
        }
        
        maxCapacity = newCapacity;
        delete [] heap;
        heap = newArray;
}


// Comp cat
// =^.^=
