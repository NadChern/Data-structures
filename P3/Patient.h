// Author: Nadezhda Chernova
// File: Patient.h
// Date: 11/14/23
// Specification and implementation file for the Patient class.
// Purpose: The Patient class includes private variables: name
// (patient's full name), priorityCode (patient's assigned priority code),
// priority (patient's assigned priority code in string format),
// and arrivalOrder (assigned arrival number). The class includes constructors,
// overloaded operators in order to properly add, peek, and remove patients
// from the waiting room, getName functions to get name of the patient
// and setArrivalOrder function to assign proper order for each
// patient.


#ifndef P3_PATIENT_H
#define P3_PATIENT_H

#include <iostream>
#include <sstream>

using namespace std;

class Patient {
public:
    Patient();
    // Default constructor
    // IN: none
    // MODIFY: properties assigned default values
    // OUT: none

    Patient(const string &, const string &);
    // Overloaded constructor
    // IN: references on patient's name and priority
    // MODIFY: initialized instance of Patient class with passed in
    // as parameters name and priority, converted to int value priorityCode,
    // default value of arrivalOrder.
    // OUT: none

    bool operator>(const Patient &) const;
    // Overloaded operator >
    // Compare current patient with patient passed in as a parameter
    // IN: reference on Patient object
    // MODIFY: none
    // OUT: true if the current patient is greater (of higher priority),
    // otherwise false. If both patients have same priority, one who arrived
    // earlier is considered of higher priority.

    bool operator<(const Patient &) const;
    // Overloaded operator <
    // Compare current patient with patient passed in as a parameter
    // IN: reference on Patient object
    // MODIFY: none
    // OUT: true if the current patient is of lower priority,
    // otherwise false. If both patients have same priority, one who arrived
    // later is considered of lower priority.

    bool operator==(const Patient &) const;
    // Overloaded operator ==
    // Compare current patient with patient passed in as a parameter
    // IN: reference on Patient object
    // MODIFY: none
    // OUT: true if patients have same priorityCode and arrivalOrder,
    // otherwise false

    string to_string() const;
    // String representation of Patient object
    // IN: none
    // MODIFY: none
    // OUT: string representation of the object

    string getName() const;
    // Get patient's name
    // IN: none
    // MODIFY: none
    // OUT: string with patient's name

    void setArrivalOrder(const int &);
    // Set patient's arrival order according to the order of insertion
    // in the priority queue (nextPatientNumber)
    // IN: reference on nextPatientNumber
    // MODIFY: from default to insertion number
    // OUT: none

private:
    string name; // patient's full name
    string priority; // string representation of priority code
    int priorityCode; // patient's assigned priority code
    int arrivalOrder; // assigned arrival number

    int converter(const string &);
    // Convert string representation of the priority code to integer format
    // IN: reference on string representation of the priority code
    // MODIFY: from string value to int (ex. immediate -> 1)
    // OUT: integer value of the priorityCode
};

#endif //P3_PATIENT_H


Patient::Patient() {
    name = "";
    priority = "";
    priorityCode = 0;
    arrivalOrder = 1;
}

Patient::Patient(const string &name, const string &priority) {
    this->name = name;
    this->priority = priority;
    this->priorityCode = converter(priority);
    arrivalOrder = 1;
}


bool Patient::operator>(const Patient &anotherPatient) const {
    // current patient is of higher priority
    if (priorityCode < anotherPatient.priorityCode) {
        return true;

        // one who arrived earlier is of higher priority
    } else if (priorityCode == anotherPatient.priorityCode) {
        return arrivalOrder < anotherPatient.arrivalOrder;
    }
    return false;
}


bool Patient::operator<(const Patient &anotherPatient) const {
    // current patient is of lower priority
    if (priorityCode > anotherPatient.priorityCode) {
        return true;

        // one who arrived later is of lower priority
    } else if (priorityCode == anotherPatient.priorityCode) {
        return arrivalOrder > anotherPatient.arrivalOrder;
    }
    return false;
}


bool Patient::operator==(const Patient &anotherPatient) const {
    return priorityCode == anotherPatient.priorityCode &&
           arrivalOrder == anotherPatient.arrivalOrder;
}


string Patient::getName() const {
    return name;
}

void Patient::setArrivalOrder(const int &nextPatientNumber) {
    this->arrivalOrder = nextPatientNumber;
}


int Patient::converter(const string &level) {
    if (level == "immediate") {
        return 1;
    } else if (level == "emergency") {
        return 2;
    } else if (level == "urgent") {
        return 3;
    } else {
        return 4;
    }
}

string Patient::to_string() const {
    stringstream ss; // stream object
    ss << "\t " << arrivalOrder << "\t ";
    ss << "\t " << priority << " \t\t  ";
    ss << name << endl;
    return ss.str();
}


