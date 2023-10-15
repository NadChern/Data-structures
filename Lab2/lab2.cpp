// Author: Nadezhda Chernova
// File: lab2.cpp
// Date: 9/29/23
// Purpose: This program prompts user for the books file name, reads
//          from the file, populates the book list with the book information, displays
//          the results in a particular format.
// Input:   User input of file.
// Process: BookList class and struct Book are used to implement this program.
//          Opens and reads the file from the user, populates the array of Book objects.
// Output:  Displays the list of books with their attributes.


#include "BookList.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void printBookList(const BookList &);
// Print the elements of the array of BookList obj
// IN: reference on BookList obj
// MODIFY:none
// OUT: Elements of the array in a string format

void printBookNum(int);
// Print the number of elements (books) in BookList obj
// IN: integer number of elements
// MODIFY: none
// OUT: number of books in a specific format


int populateBookList(BookList &);
// Populate array of BookList obj with books
// IN: reference on BookList obj
// MODIFY: from default values to values from file
// OUT: populated array of books

int main() {
    const int SIZE = 100; // capacity of the array
    BookList list(SIZE); // create BookList object

    int count = populateBookList(list);
    printBookNum(count);
    printBookList(list);

    return 0;
}

void printBookList(const BookList &obj) {
    cout << endl;
    if (obj.empty()) {
        cout << "The book list is empty." << endl;
    } else {
        cout << obj.to_string() << endl;
    }
}

void printBookNum(int count) {
    cout << endl;
    cout << "# of books: " << count << endl;
}

int populateBookList(BookList &obj) {
    ifstream inputFile; // create ifstream object to read from file
    string filename; // hold file name
    string author, title, year; // hold attributes of Book obj
    int count = 0; // hold number of books

    cout << "\nEnter books file: ";
    cin >> filename;

    srand(static_cast<unsigned>(time(nullptr))); // random generator for isbn

    inputFile.open(filename);
    if (inputFile) {
        while (getline(inputFile, author, ',')) {
            getline(inputFile, title, ',');
            getline(inputFile, year);
            obj.add(author, title, year);
            count++;
        }

    } else {
        cout << "Error: cannot open file." << endl;
    }
    inputFile.close();

    return count;
}

