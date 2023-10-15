// Author: Nadezhda Chernova
// File: BookList.h
// Date: 9/29/23
// Specification file for the BookList class.

#ifndef LAB2_BOOKLIST_H
#define LAB2_BOOKLIST_H

#include <string>
using namespace std;

class BookList {

public:
    BookList(int);
    // Constructor

    ~BookList();
    // Destructor

    void add(const string &, const string &, const string &);
    // Add Book obj to array

    string to_string() const;
    // Convert Book obj to a string

    bool empty() const;
    // Check if the array is empty

    static string generateIsbn();
    //  Generate random ISBN

private:
    struct Book {
        string isbn; // ISBN number
        string author; // Author of the book
        string title;  // Title of the book
        string year; // Published year

        Book(); // Constructor
    };

    Book *books; // pointer to the array of Book objects
    int numElements; // number of elements in the array
    int capacity; // capacity of the array
    void resize(); // resize array (when full)

};

#endif //LAB2_BOOKLIST_H
