// Author: Nadezhda Chernova
// File: LinkedList.h
// Date: 10/21/23
// Specification and implementation file for the template LinkedList class.
// Purpose: The LinkedList class includes private struct Node, pointer to
// the head of the list, private helper function getLastNegative, consists of
// following public functions (methods):
// constructor, destructor, append method (to add data to the end of the list),
// to_string method(to represent data in string format), getLastNegative method
// (to get last negative data from the list if exists).

#ifndef LAB4_LINKEDLIST_H
#define LAB4_LINKEDLIST_H

#include <iostream>
#include <sstream>
using namespace std;

template<typename T>
class LinkedList {

public:

    LinkedList();
    // Constructor
    // In: none
    // Modify: head is assigned to nullptr
    // OUT: none

    ~LinkedList();
    // Destructor
    // In: none
    // Modify: delete list from the heap
    // OUT: none

    void append(T);
    // Add to the end of the list
    // IN: data to add to the list
    // MODIFY: from empty list to populated list with data
    // OUT: none

    string to_string() const;
    // String representation  of the list
    // IN: none
    // MODIFY: from nodes with data to string format of data
    // OUT: string format of the list

    T getLastNegative() const;
    // Get last negative data from the list (if exists)
    // IN: none
    // MODIFY: none
    // OUT: returns last negative data in the list

private:

    struct Node {
        T data; // Data of the node
        Node *next; // Pointer to the next node
    };
    Node *head; // Pointer to the head of the list

    T getLastNegative(T, Node *) const;
    // Helper recursive function for public getLastNegative()
    // IN: current node pointer, current last negative value (start with 0)
    // MODIFY: update last negative value if exists
    // OUT: current last negative value, pointer to the next node
};


template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node *curr; // current pointer to traverse the list
    while (head != nullptr) {
        curr = head;
        head = head->next;
        delete curr;
    }
}

template<typename T>
void LinkedList<T>::append(T value) {
    Node *curr; // current pointer to traverse the list
    Node *newNode = new Node; // create new Node for keep value
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

template<typename T>
string LinkedList<T>::to_string() const {
    stringstream ss; // create stream object
    Node *curr = head; // current ptr to hold address of the head ptr
    while (curr != nullptr) {
        ss << curr->data << " ";
        curr = curr->next;
    }
    return ss.str();
}


template<typename T>
T LinkedList<T>::getLastNegative() const {
    Node *curr = head; // current ptr to hold address of the head ptr
    if (head == nullptr) { // if the list is empty
        return 0;
    }
    T lastN = getLastNegative(0, curr);
    return lastN;
}

template<typename T>
T LinkedList<T>::getLastNegative(T last, Node *ptr) const {
    if (ptr == nullptr) {
        return (last < 0) ? last : 0; // base case
    }

    if (ptr->data < 0) {
        last = ptr->data;
    }
    return getLastNegative(last, ptr->next);
}

#endif //LAB4_LINKEDLIST_H
