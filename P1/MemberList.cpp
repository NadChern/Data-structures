// Author: Nadezhda Chernova
// File: MemberList.cpp
// Date: 10/10/23
// Implementation for MemberList class described in MemberList.h


#include "MemberList.h"
#include <sstream>


using namespace std;

int MemberList::accountCount = 1;

MemberList::MemberList(int cap) {
    members = new Member[cap];
    capacity = cap;
    numElements = 0;
    accountCount = 1;
}

MemberList::Member::Member() {
    accountId = 0;
    name = "";
    isLoggedIn = false;
}

MemberList::~MemberList() {
    delete[] members;
}

MemberList::MemberList(const MemberList &obj) {
    // assign numElements and capacity (from obj)
    capacity = obj.capacity;
    numElements = obj.numElements;

    // allocate memory based on new capacity
    members = new Member[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        members[i] = obj.members[i];
}

MemberList &MemberList::operator=(const MemberList &obj) {
    if (this != &obj) {
        // deallocate memory
        delete[] members;

        // assign numElements and capacity (from obj)
        capacity = obj.capacity;
        numElements = obj.numElements;

        // allocate memory based on new capacity
        members = new Member[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numElements; i++)
            members[i] = obj.members[i];
    }
    return *this;
}

int MemberList::size() const {
    return numElements;
}

bool MemberList::isLoggedIn(int accountId) const {
    return members[accountId - 1].isLoggedIn;
}

void MemberList::loginMember(int accountId) {
    for (int i = 0; i < numElements; i++) {
        if (members[i].accountId == accountId) {
            members[i].isLoggedIn = true;
        }
    }
}

void MemberList::logoutMember(int accountId) {
    if (members[accountId - 1].isLoggedIn) {
        members[accountId - 1].isLoggedIn = false;
    }
}

string MemberList::getMemberById(int num) const {
    for (int i = 0; i < numElements; i++) {
        if (members[i].accountId == num) {
            stringstream ss;
            ss << members[i].name;
            return ss.str();
        }
    }
    return "Member with such account doesn't exist.";
}

int MemberList::generateAccountId() {
    return accountCount++;
}

void MemberList::add(const string &name) {
    if (numElements >= capacity)
        resize();
    members[numElements].accountId = generateAccountId();
    members[numElements].name = name;
    members[numElements].isLoggedIn = false;
    numElements++;
}

bool MemberList::empty() const {
    return numElements == 0;
}

string MemberList::to_string() const {
    stringstream ss;
    for (int i = 0; i < numElements; i++) {
        ss << members[i].accountId << ", "
           << members[i].name << ", "
           << members[i].isLoggedIn << "\n";
    }
    return ss.str();
}

void MemberList::resize() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    auto *tempArr = new Member[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = members[i];

    // delete old array
    delete[] members;

    // reassign old array to new array
    members = tempArr;
}


