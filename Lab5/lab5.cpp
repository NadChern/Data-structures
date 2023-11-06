// Author: Nadezhda Chernova
// File: lab5.cpp
// Date: 10/05/23
// Purpose: This program measures the time it takes to execute various sorting
//          algorithms (insertion sort, merge sort, heap sort, quick sort,
//          STL's Introsort).
// Input:   None.
// Process: Creates vector of longs filled with random numbers, calls sorting
//          functions from Sort.h and measures the time it takes to execute for
//          different values - sizes (40000, 80000, 160000 etc.), regenerates
//          this vector between trials and sorting algorithms.
// Output:  Displays the results (time took for sorting 40000 random numbers,
//          80000 etc.) for each algorithm.


#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <ctime>
#include <chrono>
#include "Sort.h"

using namespace std;

void getTimeOfSortAlgorithm(const string &, int);
// Measure the execution time of the sorting algorithm
// In: name of sorting algorithm, size of the random generated numbers
// Modify: vector of random longs is populated with random numbers, than
// regenerated again with second call of the function
// OUT: none


int main() {

    // Create vector if values (size of the random generated numbers)
    vector<int> values = {40000, 80000, 160000, 320000, 640000, 1280000,
                          2560000, 5120000, 10240000, 20480000};

    for (int value: values) {
        printf("Sorting %d values...\n", value);
        getTimeOfSortAlgorithm("QuickSort", value);
        getTimeOfSortAlgorithm("HeapSort", value);
        getTimeOfSortAlgorithm("MergeSort", value);
        getTimeOfSortAlgorithm("STLIntroSort", value);
        if (value >= 40000 && value <= 640000) {
            getTimeOfSortAlgorithm("InsertionSort", value);
        }
        printf("\n");
    }

    return 0;
}

void getTimeOfSortAlgorithm(const string &sortAlgmName, int value) {
    vector<long> randomNumbers; // vector of long integers

//    mt19937_64 randGenerator;
//    randGenerator.seed(value);

    mt19937_64 randGenerator(
            static_cast<unsigned long>(chrono::high_resolution_clock
            ::now().time_since_epoch().count()));// random number generator

   // Generate random integers within the range of possible long type
    uniform_int_distribution<long> dist(numeric_limits<long>::min(),
                                        numeric_limits<long>::max());

    // Generate a vector of random longs
    for (int i = 0; i < value; i++) {
        long randomValue = dist(randGenerator); // to hold random value
        randomNumbers.push_back(randomValue);
    }

    clock_t t = clock(); // to measure the execution time

    if (value >= 40000 && value <= 640000 && sortAlgmName == "InsertionSort") {
        insertionSort(randomNumbers.begin(), randomNumbers.end());
    } else if (sortAlgmName == "QuickSort") {
        quicksort(randomNumbers.begin(), randomNumbers.end());
    } else if (sortAlgmName == "HeapSort") {
        heapsort(randomNumbers.begin(), randomNumbers.end());
    } else if (sortAlgmName == "MergeSort") {
        mergesort(randomNumbers.begin(), randomNumbers.end());
    } else if (sortAlgmName == "STLIntroSort") {
        sort(randomNumbers.begin(), randomNumbers.end());
    }

    t = clock() - t;

    printf("It took me %d clocks (%f seconds) for %s.\n", (int) t,
           (float) (t) / CLOCKS_PER_SEC, sortAlgmName.c_str());

    randomNumbers.clear();
}

