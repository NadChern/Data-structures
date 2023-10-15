// Author: Nadezhda Chernova
// File: BookList.cpp
// Date: 9/29/23
// Implementation file for the BookList class.

#include "BookList.h"
#include <sstream>
#include <cstdlib>

BookList::BookList(int cap) {
    books = new Book[cap];
    capacity = cap;
    numElements = 0;
}

BookList::Book::Book() {
    isbn = "";
    author = "";
    title = "";
    year = "";
}

BookList::~BookList() {
    delete[] books;
}

 string BookList::generateIsbn() {
    int randomIsbn = rand();
    stringstream ss;
    ss << randomIsbn;
    return ss.str();
}

void BookList::add(const string &author,
                   const string &title, const string &year) {
    if (numElements >= capacity)
        resize();
    books[numElements].isbn = generateIsbn();
    books[numElements].author = author;
    books[numElements].title = title;
    books[numElements].year = year;

    numElements++;
}



bool BookList::empty() const {
    return numElements == 0;
}

string BookList::to_string() const {
    stringstream ss;
    for (int i = 0; i < numElements; i++) {
        ss << (i + 1) << ", "
           << books[i].author << ", "
           << books[i].title << ", "
           << books[i].year << "\n";
    }
    return ss.str();
}

void BookList::resize() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    Book *tempArr = new Book[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = books[i];

    // delete old array
    delete[] books;

    // reassign old array to new array
    books = tempArr;
}



