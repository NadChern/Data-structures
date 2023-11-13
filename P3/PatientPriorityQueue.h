// Author: Nadezhda Chernova
// File: PatientPriorityQueue.h
// Date: 11/14/23
// Specification and implementation file for the PatientPriorityQueue class.
// Purpose: The PatientPriorityQueue class uses private vector<Patient>
// to store the patients in heap order, and variable nextPatientNumber to keep
// track of the last patient inserted into the heap (this variable also helps
// to assign properly the arrival order of the patient).
// The class includes public constructor, add, peek, remove functions,
// as well as size (to display number of patients still waiting),
// to_string, and private helper functions.


#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H

#include "Patient.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cassert>
#include <stdexcept>

using namespace std;


class PatientPriorityQueue {
public:
    PatientPriorityQueue();
    // Default constructor
    // IN: none
    // MODIFY: nextPatientNumber is assigned to 0 (meaning empty queue)
    // OUT: none

    void add(Patient &);
    // Add patient to the priority queue (in heap order)
    // IN: reference on Patient object
    // MODIFY: from empty to populated vector<Patient> in heap order
    // OUT: none

    Patient peek() const;
    // Get patient with the highest priority without removing it
    // IN: none
    // MODIFY: none
    // OUT: Patient object with the highest priority code

    Patient remove();
    // Remove the highest priority patient from the queue
    // IN: none
    // MODIFY: removed Patient object from vector<Patient>
    // OUT: removed Patient object

    size_t size() const;
    // Get the number of patients still waiting in the queue
    // IN: none
    // MODIFY: none
    // OUT: number of elements in vector<Patient> (patients in the queue)

    string to_string() const;
    // String representation of Patient objects in heap order
    // IN: none
    // MODIFY: none
    // OUT: string representation of Patient objects (name, priority, order)

private:
    vector<Patient> list; // store patients in heap order
    int nextPatientNumber; // number of the last patient inserted into heap

    void siftUp(int);
    // Private helper function for public add function
    // Find correct position for newly added element to maintain heap order
    // (compares the element with parent and swap them if necessary)
    // IN: position (index) of the added element that needs to sift up
    // MODIFY: none (values are not modified, only the order)
    // OUT: none

    void siftDown(int);
    // Private helper function for public remove function
    // Maintain heap order after removing top element from the heap
    // IN: position (index) of the element that needs to sift down
    // MODIFY: none (values are not modified, only the order)
    // OUT: none

    int getLeftChild(int) const;
    // Private helper function for private siftDown function
    // Find index of the left child of the current node in the heap
    // IN: position (index) of the current element that needs to sift down
    // MODIFY: none
    // OUT: position (index) of the left child of the current node

    int getRightChild(int) const;
    // Private helper function for private siftDown function
    // Find index of the right child of the current node in the heap
    // IN: position (index) of the current element that needs to sift down
    // MODIFY: none
    // OUT: position (index) of the right child of the current node

    int getParent(int) const;
    // Private helper function for private siftUp function
    // Find index of the parent node in the heap
    // IN: position (index) of the current element that needs to sift up
    // MODIFY: none
    // OUT: position (index) of the parent node of the current element

};

#endif //P3_PATIENTPRIORITYQUEUE_H


PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 0;
}

void PatientPriorityQueue::add(Patient &patient) {
    nextPatientNumber++;
    patient.setArrivalOrder(nextPatientNumber);

    list.push_back(patient);
    int index = static_cast<int>(list.size() - 1); // cast result to int
    siftUp(index);
}


Patient PatientPriorityQueue::remove() {
    if (list.empty()) {
        throw runtime_error("There are no patients in the waiting area.");
    }
    Patient patient; // hold removed patient
    patient = list[0];
    list[0] = list[list.size() - 1];
    list.pop_back();
    if (!list.empty()) {
        siftDown(0);
    }
    return patient;
}


Patient PatientPriorityQueue::peek() const {
    if (list.empty()) {
        throw runtime_error("There are no patients in the waiting area.");
    }
    return list.front();
}


size_t PatientPriorityQueue::size() const {
    return list.size();
}


string PatientPriorityQueue::to_string() const {
    stringstream ss; // stream object to read attributes of Patient obj
    for (const auto & i : list) {
        ss << i.to_string();
    }
    return ss.str();
}


void PatientPriorityQueue::siftUp(int index) {
    int parentIdx; // index of the parent node in the heap
    if (index != 0) { // if not the root, siftUp
        parentIdx = getParent(index);
        if (list[parentIdx] < list[index]) {
            swap(list[parentIdx], list[index]);
            siftUp(parentIdx);
        }
    }
}


void PatientPriorityQueue::siftDown(int index) {
    int leftIdx; // position of the left child
    int rightIdx; // position of the right child
   int maxIdx; // position of the child with max value
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    if (rightIdx >= list.size()) {
        if (leftIdx >= list.size())
            return;
        else
            maxIdx = leftIdx;
    } else {
        if (list[leftIdx] > list[rightIdx])
            maxIdx = leftIdx;
        else
            maxIdx = rightIdx;
    }

    if (list[index] < list[maxIdx]) {
        swap(list[index], list[maxIdx]);
        siftDown(maxIdx);
    }
}


int PatientPriorityQueue::getLeftChild(int index) const {
    return 2 * index + 1;
}

int PatientPriorityQueue::getRightChild(int index) const {
    return 2 * index + 2;
}

int PatientPriorityQueue::getParent(int index) const {
    return (index - 1) / 2;
}

