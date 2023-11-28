// Author: Nadezhda Chernova
// File: lab6.cpp
// Date: 11/19/23
// Purpose: This program tests HashTable class functionality.
// Input:   None.
// Process: The program creates new HashTable with capacity 4093 and inserts
//          4083 unique integers, then verifies that the size() is 4083.
//          Adds 10 additional key/value pairs, tests get and contains
//          functions.
// Output:  Displays introduction and goodbye messages, steps and results of
//          testing functions.


#include <iostream>
#include "HashTable.h"

using namespace std;

void welcome();
// Prints welcome message.
// IN: none
// MODIFY:none
// OUT: none

void goodbye();
// Prints goodbye message.
// IN: none
// MODIFY:none
// OUT: none

int main() {
    const int SIZE = 4093; // capacity of hash table
    const int NUM_PAIRS = 4083; // number of key-value pairs to insert
    const int SIZE1 = 10; // size of the key, value arrays
    int probesCount;
    int totalCollisions = 0;

    int *keys; // pointer on the array of keys
    keys = new int[SIZE1]{1179, 9702, 7183, 50184, 4235,
                          644, 77, 3077, 23477, 90777};

    int *values; // pointer on array of values
    values = new int[SIZE1]{120, 121, 122, 123,
                            124, 125, 126, 127};

    HashTable hashT(SIZE); // HashTable object

    for (int i = 0; i < NUM_PAIRS; i++) {
        probesCount = 0;
        hashT.put(i + 1, i + 10, probesCount);
        totalCollisions += probesCount;
    }

    welcome();

    // Test size function after inserting
    cout << "\nCreating a new HashTable with capacity "
         << SIZE << " and inserting " << endl;
    cout << hashT.size() << " random key-value pairs with unique keys.. done."
         << endl;

    // Insert 10 key-values
    cout << "\nInserting 10 additional key-values.." << endl;
    for (int i = 0; i < SIZE1; i++) {
        probesCount =0;
        hashT.put(keys[i], values[i], probesCount);
        totalCollisions += probesCount;
        cout << "(" << keys[i] << " , " << values[i] << ")" << endl;
    }

    cout << "\nCollisions encountered: " << totalCollisions << endl;

    // Average probes theoretically
    cout << "\nAverage number of probes for such hashtable: "
         << hashT.averageProbesLinearProbing() << endl;

    // Test contains function
    cout << "\nTesting contains.." << endl;
    cout << "contains(50184): " << boolalpha << hashT.contains(50184)
         << endl;
    cout << "contains(   77): " << boolalpha << hashT.contains(77) << endl;
    cout << "contains(    0): " << boolalpha << hashT.contains(0) << endl;
    cout << "contains(   -1): " << boolalpha << hashT.contains(-1) << endl;

    // Test get function
    cout << "\nTesting get.." << endl;
    cout << "get(50184): " << hashT.get(50184)
         << endl;
    cout << "get(   77): " << hashT.get(77) << endl;
    cout << "get(    0): " << hashT.get(0) << endl;
    cout << "get(   -1): " << hashT.get(-1) << endl;

    goodbye();

    // Deallocate memory from the dynamic arrays
    delete[] keys;
    delete[] values;

    return 0;
}

void welcome() {
    cout << "\nWelcome to the HashTable testing program.\n";
}

void goodbye() {
    cout << "\nThanks for using the HashTable testing program. Goodbye.\n";
}