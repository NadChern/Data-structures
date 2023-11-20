// Author: Nadezhda Chernova
// File: HashTable.h
// Date: 11/19/23
// Specification and implementation file for the HashTable class.
// Purpose: The HashTable class uses struct Bucket to store key-value pairs
// and dynamic array to insert key-value pairs in buckets, retrieve
// value associated with a given key, check whether a given key exists in
// the hash table (buckets), check for empty hash table and number of key-value
// pairs stored in the hash table.


#ifndef LAB6_HASHTABLE_H
#define LAB6_HASHTABLE_H

#include <iostream>
#include <stdexcept>

using namespace std;

class HashTable {

public:

    HashTable(int capacity);
    // Constructor
    // IN: capacity of the array
    // MODIFY: array with specified capacity and initialized default values
    // of key, value = -1 (meaning empty), and number of elements in the array
    // set to 0
    // OUT: none

    ~HashTable();
    // Destructor
    // IN: none
    // MODIFY: delete array from the heap
    // OUT: none

    int put(int key, int value);
    // Insert key-value in the hash table by using hash function
    // IN: key and value
    // MODIFY: populated array with key-value pairs (if the key doesn't exist,
    // new bucket is created; if the key exists, value is updated)
    // OUT: previous value associated with key, or -1 if there was no mapping
    // for key; errors if hash table is full or invalid key.

    int get(int key);
    // Get value associated with the specified key
    // IN: key
    // MODIFY: none
    // OUT: value associated with the specified key or -1 if it does not exist,
    // or it is not valid

    bool contains(int key);
    // Check if the hash table contains a mapping for the specified key
    // IN: key
    // MODIFY: none
    // OUT: true if the hash table contains a mapping for the specified key,
    // otherwise false

    int size();
    // Get number of unique keys stored in the hash table
    // IN: none
    // MODIFY: none
    // OUT: number of unique keys (key-value pairs)

    bool empty();
    // Check if the hash table is empty
    // IN: none
    // MODIFY: none
    // OUT: true if hash table is empty (no unique keys), otherwise false


private:
    struct Bucket {
        int key; // specified key
        int value; // specified value
    };

    Bucket *buckets; // pointer to the array of buckets
    int capacity;     // capacity of the array
    int numElements; // number of elements (unique key-value pairs) in array

    int hash(int key);
    // Private helper function
    // Find position for key-value pair in the hash table (array)
    // IN: key
    // MODIFY: value of the key is not modified, but used to calculate position
    // (index) in array
    // OUT: position (index)

    int rehash(int index);
    // Private helper function
    // Find position for key-value pair in the hash table (array) when
    // collision occurs
    // IN: current position (index) calculated for the key
    // MODIFY: value of the index is not modified, but used to calculate new
    // position (index) in array
    // OUT: new position (index)

};

#endif //LAB6_HASHTABLE_H

HashTable::HashTable(int cap) {
    capacity = cap;
    numElements = 0;
    buckets = new Bucket[cap];
    for (int i = 0; i < capacity; i++) {
        buckets[i].key = -1;
        buckets[i].value = -1;
    }
}

HashTable::~HashTable() {
    delete[] buckets;
}

bool HashTable::empty() {
    return numElements == 0;
}

int HashTable::size() {
    return numElements;
}

int HashTable::hash(int key) {
    return key % capacity;
}

int HashTable::rehash(int index) {
    return (index + 1) % capacity;
}


int HashTable::put(int key, int value) {
    int oldValue; // previous value associated with key
    int probeCount = 0; // number of probes during linear probing
    int index = hash(key); // position for key-value pair in hashtable

    // Validate key value
    if (key < 0) { // valid keys are non-negative
        throw runtime_error("Key should be non-negative value!");
    }

    // Find position by linear probing (if collision occurs)
    while (buckets[index].key != -1 && buckets[index].key != key) {
        index = rehash(index);
        probeCount++;

        // Exit the loop, if hashtable is full (no empty bucket was found)
        if (probeCount >= capacity) {
            throw runtime_error("Hash table is full");
        }
    }

    // Empty bucket is found, count number of unique keys stored in the table
    if (buckets[index].key == -1) {
        numElements++;
    }

    // Create new bucket if the key doesn't exist,
    // update existing bucket if the key exists
    oldValue = buckets[index].value;
    buckets[index].key = key;
    buckets[index].value = value;
    return oldValue;
}


int HashTable::get(int key) {
    int index = hash(key); // position for key-value pair in hashtable
    int firstIndex = index; // first position received from hash function

    if (key < 0) {
        return -1;
    }

    while (buckets[index].key != key) {
        //  If the bucket empty, return -1
        if (buckets[index].key == -1) {
            return -1;
        }

        // Find next bucket index (case of collision)
        index = rehash(index);

        // Checked all the hash table, key not found
        if (index == firstIndex) {
            return -1;
        }
    }
    return buckets[index].key == key ? buckets[index].value : -1;
}


bool HashTable::contains(int key) {
    int index = hash(key); // position for key-value pair in hashtable
    int firstIndex = index; // first position received from hash function

    if (key < 0) {
        return false;
    }

    while (buckets[index].key != key) {
        if (buckets[index].key == -1) {
            return false;
        }
        index = rehash(index);
        if (index == firstIndex) {
            return false;
        }
    }
    return buckets[index].key == key;
}



