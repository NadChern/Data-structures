
// Created by Nadezhda Chernova on 9/22/23.
// Implementation file for the Date class.


#include "Date.h"
#include <string>

using namespace std;

Date::Date() {
    year = 2000;
    month = 1;
    day = 1;
}

Date::Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}

void Date::setDate(int y, int m, int d) {
    if (m < 1 || m > 12) month = 1;
    if (day < 1 || day > 31) day = 1;
    year = y;
    month = m;
    day = d;
}

string Date::getDate() const {
    string formattedYear = to_string(year);
    string formattedMonth = (month < 10) ? "0" + to_string(month) : to_string(month);
    string formattedDay = (day < 10) ? "0" + to_string(day) : to_string(day);
    string formattedDate = formattedMonth + "/" + formattedDay + "/" + formattedYear;
    return formattedDate;
}

string Date::getSeason() const {
//    const string spr = "Spring";
//    const string wnt = "Winter";
//    const string sum = "Summer";
//    const string fall = "Fall";
    const int firstSprSum = 21; // first day of spring or summer
    const int firstWnt = 22; // first day of winter
    const int firstFall = 23; // first day of fall

    if (month == 4 || month == 5) return spr;
    if (month == 7 || month == 8) return sum;
    if (month == 10 || month == 11) return fall;
    if (month == 1 || month == 2) return wnt;

    if (month == 3 && day >= firstSprSum) return spr;
    if (month == 6 && day < firstSprSum) return spr;

    if (month == 6 && day >= firstSprSum) return sum;
    if (month == 9 && day < firstFall) return sum;

    if (month == 9 && day >= firstFall) return fall;
    if (month == 12 && day < firstWnt) return fall;

    if (month == 12 && day >= firstWnt) return wnt;
    if (month == 3 && day < firstSprSum) return wnt;

    return "Error";

}

