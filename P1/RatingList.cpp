// Author: Nadezhda Chernova
// File: RatingList.cpp
// Date: 10/10/23
// Implementation for RatingList class described in RatingList.h

#include "RatingList.h"
#include <iostream>

using namespace std;

RatingList::RatingList() {
    row = 100;
    column = 100;
    numElements = 0;
    ratings = new int *[column];
    for (int i = 0; i < column; i++) {
        ratings[i] = new int[row]; // initialize to zero
    }
}

RatingList::~RatingList() {
    for (int i = 0; i < column; i++) {
        delete[] ratings[i];
    }
    delete[] ratings;
}

RatingList::RatingList(const RatingList &obj) {
    // assign numElements and capacity (from obj)
    row = obj.row;
    column = obj.column;

    // allocate memory based on new capacity
    ratings = new int *[column];
    for (int i = 0; i < column; i++) {
        ratings[i] = new int[row]; //initialize to zero
    }

    // copy over elements (from obj)
    for (int k = 0; k < column; k++) {
        for (int j = 0; j < row; j++) {
            ratings[k][j] = obj.ratings[k][j];
        }
    }
}

RatingList &RatingList::operator=(const RatingList &obj) {
    if (this != &obj) {
        // deallocate memory for the old array
        for (int i = 0; i < column; i++) {
            delete[] ratings[i];
        }
        delete[] ratings;

        // assign row and column (from obj)
        row = obj.row;
        column = obj.column;

        // allocate memory based on new capacity
        ratings = new int *[column];
        for (int i = 0; i < column; i++) {
            ratings[i] = new int[row]; // initialize to zero
        }

        // copy over elements (from obj)
        for (int k = 0; k < column; k++) {
            for (int j = 0; j < row; j++) {
                ratings[k][j] = obj.ratings[k][j];
            }
        }
    }
    return *this;
}


void RatingList::add(int rIndex, int colIndex, int rating) {
    if (rIndex < 0 || colIndex < 0) {
        cout << "Invalid row or column index";
        return;
    }

    if (rIndex >= row && colIndex >= column)
        resize();
    ratings[rIndex][colIndex] = rating;
    numElements++;
}

bool RatingList::empty() const {
    return numElements == 0;
}

int RatingList::getRating(int rIndex, int colIndex) const {
    if (!empty()) {
        return ratings[rIndex][colIndex];
    } else {
        return 0;
    }
}


void RatingList::resize() {
    // update capacity
    row *= 2;
    column *= 2;

    // create new array based on updated capacity
    int **tempArr = new int *[column];
    for (int i = 0; i < column; i++) {
        tempArr[i] = new int[row];
    }
    // copy old array values to new array
    for (int k = 0; k < column; k++) {
        for (int j = 0; j < row; j++) {
            tempArr[k][j] = ratings[k][j];
        }
    }

    // delete old array
    for (int i = 0; i < column; i++) {
        delete[] ratings[i];
    }
    delete[] ratings;

    // reassign old array to new array
    ratings = tempArr;
}

