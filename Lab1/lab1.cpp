// Created by Nadezhda Chernova on 9/24/23.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {

    ifstream inputFile; // create an object to read from file
    string filename; // hold file name
    string line; // hold line from a file
    const int SIZE = 100; // capacity of arrays

    // Create a dynamic 1D array
    string *members; // pointer
    members = new string[SIZE]; // array in the heap

    // Create a dynamic 2D array
    int **ratings; // pointer
    ratings = new int *[SIZE];
    for (int i = 0; i < SIZE; i++) {
        ratings[i] = new int[SIZE]; //initialize to zero
    }

    // Ask for the file
    cout << "\nEnter rating file: ";
    cin >> filename;

    // Open and read from file
    inputFile.open(filename);

    int mCount = 0; // size of 1D array (members)
    int rCount = 0; // rows of 2D array (ratings)
    int col = 0; // columns of 2D array (ratings)
    int count = 0; // control even/odd lines in the loop
    int num; // read each integer in the line

    // Populate arrays
    if (inputFile) {
        while (getline(inputFile, line)) {

            // If it's even line
            if (count % 2 == 0) {
                members[mCount] = line;
                mCount++;

                // If it's odd line
            } else if (count % 2 != 0) {
                istringstream ss(line);
                col = 0; // reset counter for new loop
                while (ss >> num) {
                    ratings[rCount][col] = num;
                    col++;
                }
                rCount++;
            }
            count++;
        }
    } else {
        cout << "Error: cannot open file." << endl;
    }

    cout << "\n# of books: " << col << endl;
    cout << "# of members: " << mCount << endl;

    // Print arrays
    cout << endl;
    for (int i = 0; i < mCount; i++) {
        cout << members[i] << endl;
        for (int j = 0; j < col; j++) {
            cout << ratings[i][j] << " ";
        }
        cout << endl;
    }

    // Deallocate memory from the dynamic arrays
    delete[] members;

    for (int i = 0; i < SIZE; i++) {
        delete[] ratings[i];
    }
    delete[] ratings;

    // Close file
    inputFile.close();

    return 0;
}
