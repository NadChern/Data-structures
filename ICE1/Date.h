
// Created by Nadezhda Chernova on 9/22/23.
// Specification file for the Date class.

#ifndef ICE1_DATE_H
#define ICE1_DATE_H

#include <string>

using namespace std;

class Date {
public:
    Date(); // default constructor
    Date(int, int, int); // overloaded constructor

    void setDate(int, int, int); // set year, month, day of Date obj

    string getDate() const; // return the date in mm/dd/yyyy format
    string getSeason() const; // return season in string based on the date

private:
    const string spr = "Spring";
    const string wnt = "Winter";
    const string sum = "Summer";
    const string fall = "Fall";
    int year;
    int month;
    int day;
};


#endif //ICE1_DATE_H
