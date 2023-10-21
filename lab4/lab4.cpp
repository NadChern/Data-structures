// Author: Nadezhda Chernova
// File: lab4.cpp
// Date: 10/21/23
// Purpose: This program tests template LinkedList class functions:
//          append, to_string and getLastNegative - on integers and doubles.
// Input:   None.
// Process: Creates two LinkedList objects of integers and doubles, appends
//          values to the lists, displays the lists, gets last negative values
//          from the lists, displays the results.
// Output:  Displays LinkedList values and last negative number of each list.


#include "LinkedList.h"
#include <iostream>

using namespace std;

int main() {

    LinkedList<int> list1; // create LL object with integers
    LinkedList<double> list2; // create LL object with doubles

    list1.append(3);
    list1.append(-2);
    list1.append(5);
    list1.append(12);
    list1.append(-2);
    list1.append(-4);
    list1.append(5);

    cout << "Linked List values: " << list1.to_string() << endl;
    cout << "Last negative number: " << list1.getLastNegative() << endl;


    list2.append(-3.2);
    list2.append(2.14);
    list2.append(-5.7);
    list2.append(-12.01);
    list2.append(-2.99);
    list2.append(4.6);
    list2.append(5.2);

    cout << "Linked List values: " << list2.to_string() << endl;
    cout << "Last negative number: " << list2.getLastNegative() << endl;


    return 0;
}