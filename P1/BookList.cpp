// Author: Nadezhda Chernova
// File: BookList.cpp
// Date: 10/10/23
// Implementation for BookList class described in BookList.h

#include "BookList.h"
#include <sstream>


using namespace std;

int BookList::isbnCount = 1;

BookList::BookList(int cap) {
    books = new Book[cap];
    capacity = cap;
    numElements = 0;
    isbnCount = 1;
}

BookList::Book::Book() {
    isbn = 0;
    author = "";
    title = "";
    year = "";
}

BookList::~BookList() {
    delete[] books;
}

BookList::BookList(const BookList &obj) {
    // assign numElements and capacity (from obj)
    capacity = obj.capacity;
    numElements = obj.numElements;

    // allocate memory based on new capacity
    books = new Book[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        books[i] = obj.books[i];
}

BookList &BookList::operator=(const BookList &obj) {
    if (this != &obj) {
        // deallocate memory
        delete[] books;

        // assign numElements and capacity (from obj)
        capacity = obj.capacity;
        numElements = obj.numElements;

        // allocate memory based on new capacity
        books = new Book[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numElements; i++)
            books[i] = obj.books[i];
    }
    return *this;
}

int BookList::size() const {
    return numElements;
}

string BookList::getBookByIsbn(int num) const {
    for (int i = 0; i < numElements; i++) {
        if (books[i].isbn == num) {
            stringstream ss;
            ss << books[i].isbn << ", "
               << books[i].author << ", "
               << books[i].title << ", "
               << books[i].year;
            return ss.str();
        }
    }
    return "0";
}

int BookList::generateIsbn() {
    return isbnCount++;
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
        ss << books[i].isbn << ", "
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



