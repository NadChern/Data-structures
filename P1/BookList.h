// Author: Nadezhda Chernova
// File: BookList.h
// Date: 10/10/23
// Specification file for the BookList class.
// Purpose: The BookList class includes private struct Book, that allows
// to keep track of the books and their attributes (isbn, author, title, year),
// consists of following functions (methods): constructors, destructor,
// overloaded = operator, copy constructor, add method (to add the book in the
// book list), to_string method (to represent book in string format),
// getBookByIsbn method (to get book from the list), empty, size and resize
// methods as well as generateIsbn method.


#ifndef P1_BOOKLIST_H
#define P1_BOOKLIST_H


#include <string>

using namespace std;

class BookList {

public:
    BookList(int);
    // Constructor

    ~BookList();
    // Destructor

    BookList(const BookList &);
    // Copy constructor

    BookList &operator=(const BookList &);
    // Overloaded = operator

    void add(const string &, const string &, const string &);
    // Add Book obj to array

    string to_string() const;
    // Convert Book obj to a string

    bool empty() const;
    // Check if the array is empty

    static int generateIsbn();
    //  Generate random ISBN

    int size() const;
    // Check the number of books

    string getBookByIsbn(int) const;
    // Find book in array, return book in string format

private:
    struct Book {
        int isbn; // ISBN number
        string author; // Author of the book
        string title;  // Title of the book
        string year; // Published year

        Book(); // Constructor
    };

    static int isbnCount; // isbn counter
    Book *books; // pointer to the array of Book objects
    int numElements; // number of elements in the array
    int capacity; // capacity of the array

    void resize();
    // Resize array (when full)

};

#endif //P1_BOOKLIST_H
