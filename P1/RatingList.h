// Author: Nadezhda Chernova
// File: RatingList.h
// Date: 10/10/23
// Specification file for the RatingList class.
// Purpose: The RatingList class includes 2D dynamic array to keep track of
// book ratings, consists of following functions (methods):
// constructor, destructor, overloaded = operator, copy constructor,
// add method (to add rating), to_string method (to represent member in string
// format), empty and resize methods, getRating method (to get rating on the
// book).


#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H

using namespace std;

class RatingList{
public:
    RatingList();
    // Constructor

    ~RatingList();
    // Destructor

    RatingList(const RatingList &);
    // Copy constructor

    RatingList &operator=(const RatingList &);
    // Overloaded = operator

    void add(int, int, int);
    // Add or change rating on the book

    int getRating(int, int) const;
    // Get rating on the book

    bool empty() const;
    // Check for empty array

private:
    int ** ratings; // Pointer to 2D array of ratings
    int row; // Rows of 2D array (members)
    int column; // Columns of 2D array (books)
    int numElements; // Number of ratings

    void resize();
    // Resize array

};

#endif //P1_RATINGLIST_H
