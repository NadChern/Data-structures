// Author: Nadezhda Chernova
// File: p1.cpp
// Date: 10/10/23
// Purpose: This program simulates the book recommendation program for its
//          members. Prompts user for the books and ratings filenames,
//          reads from files, populates the book list with the book
//          information, the member list with members and the rating list with
//          ratings. Then shows a simple menu to user that helps to add member,
//          add book, login/logout, rate book, see recommendations and ratings.
// Input:   User input of files, menu option, information about book/member,
//          rating (re-rate response).
// Process: BookList, MemberList classes with private struct Book and Member
//          are used to implement this program, as well as RatingList class.
//          Dynamic arrays are used in all classes.
// Output:  Displays introduction and goodbye messages, the results according
//          to the chosen menu option, error messages if the input is invalid
//          or not found.


#include "MemberList.h"
#include "BookList.h"
#include "RatingList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

const int STRONG_DISLIKE = -5; // constant value of allowed rating range
const int DISLIKE = -3; // constant value of allowed rating range
const int NOT_READ = 0; // constant value of allowed rating range
const int NEUTRAL = 1; // constant value of allowed rating range
const int LIKE = 3; // constant value of allowed rating range
const int STRONG_LIKE = 5; // constant value of allowed rating range


void displayGreetings();
// Display short intro and greetings
// IN: none
// MODIFY:none
// OUT: none

void displayGoodbye();
// Display goodbye message
// IN: none
// MODIFY:none
// OUT: none

void displayMainMenu();
// Display main menu (before login)
// IN: none
// MODIFY:none
// OUT: none

void displaySubMenu();
// Display submenu (after login)
// IN: none
// MODIFY:none
// OUT: none

void printBookNum(int);
// Print the number of elements (books) in BookList obj
// IN: number of books in populated book list
// MODIFY: none
// OUT: none

void printMemberNum(int);
// Print the number of elements (members) in MemberList obj
// IN: number of members in populated member list
// MODIFY: none
// OUT: none

int populateBookList(BookList &);
// Populate array of BookList obj with books
// IN: reference on BookList obj
// MODIFY: from default values of Book to values from file
// OUT: number of books from populated array of books

int populateMemberRatingLists(MemberList &, RatingList &);
// Populate arrays of MemberList obj and RatingList obj with members, ratings
// IN: reference on MemberList obj, RatingList obj
// MODIFY: from default values of Member and ratings array to values from file
// OUT: number of members from populated array of members

int getValidInput(const string &);
// Validate user input when choosing menu option or rating (check for numeric
// value)
// IN: const message, that asks user for input like "Enter a menu option" or
// "Enter your rating"
// MODIFY: none
// OUT: valid numeric rating or menu option

int getValidRating();
// Validate user input on correct rating value
// IN: none
// MODIFY: none
// OUT: valid rating

void addNewMember(MemberList &);
// Add new member to the member list
// IN: reference on MemberList obj
// MODIFY: MemberList array by adding new member
// OUT: none

void addNewBook(BookList &);
// Add new book to the book list
// IN: reference on BookList obj
// MODIFY: BookList array by adding new book
// OUT: none

void viewRatings(const MemberList &, const BookList &,
                 const RatingList &, int);
// Get and display ratings of the certain member
// IN: references on const MemberList obj, const BookList obj,
// const RatingList obj, account id of the member
// MODIFY: none
// OUT: none

void rateBook(const BookList &, RatingList &, int);
// Rate the chosen new book or re-rate it if it's already read
// (includes setNewRating function)
// IN: reference on const BookList obj, reference on RatingList obj, account id
// MODIFY: ratings array
// OUT: none

void setNewRating(const BookList &, RatingList &, int, int);
// Set new rating and display the result in a certain format
// IN: reference on const BookList obj, reference on RatingList obj, account id,
// isbn of the book
// MODIFY: ratings array
// OUT: none

bool isValidYesNoAnswer(const string &);
// Validate yes/no answer when asking about re-rate book (check for right input
// chars)
// IN: user's input (y/n)
// MODIFY: none
// OUT: false or true (if the input is right)

void getRecommendations(const MemberList &, const BookList &,
                        const RatingList &, int);
// Get recommendations for the member according similar taste with
// other members
// IN: references on const MemberList obj, const BookList obj,
// const RatingList obj, account id of the member
// MODIFY: none
// OUT: none

int main() {
    int mCount; // number of members
    int bCount; // number of books
    const int SIZE = 100; // capacity of the array
    BookList bList(SIZE); // BookList object
    MemberList mList(SIZE); // MemberList object
    RatingList rList; // RatingList object

    bool isLoggedIn = false; // control main and submenu switch
    bool isNotQuit = true; // control exit from the program
    int accountId; // hold current member
    int menuOption; // hold current user input about chosen menu option

    displayGreetings();

    bCount = populateBookList(bList);
    mCount = populateMemberRatingLists(mList, rList);

    printBookNum(bCount);
    printMemberNum(mCount);


    do {

        if (isLoggedIn) {
            displaySubMenu();
        } else {
            displayMainMenu();
        }

        string message = "\nEnter a menu option: ";
        menuOption = getValidInput(message);

        if (isLoggedIn) {
            switch (menuOption) {

                case 1: {
                    addNewMember(mList);
                    break;
                }

                case 2: {
                    addNewBook(bList);
                    break;
                }

                case 3: {
                    rateBook(bList, rList, accountId);
                    break;
                }

                case 4: {
                    viewRatings(mList, bList, rList, accountId);
                    break;
                }

                case 5: {
                    getRecommendations(mList, bList, rList, accountId);
                    break;
                }

                case 6: {  // Logout
                    mList.logoutMember(accountId);
                    isLoggedIn = mList.isLoggedIn(accountId);
                    break;
                }

                default:  // Invalid input
                    cout << "Invalid input. Please try again!" << endl;
                    break;
            }

        } else {
            switch (menuOption) {

                case 1: {
                    addNewMember(mList);
                    break;
                }

                case 2: {
                    addNewBook(bList);
                    break;
                }

                case 3: {    // Login
                    cout << "\nEnter member account: ";
                    cin >> accountId;
                    mList.loginMember(accountId);
                    isLoggedIn = mList.isLoggedIn(accountId);
                    if (isLoggedIn) {
                        cout << mList.getMemberById(accountId)
                             << ", you are logged in!" << endl;
                    } else {
                        cout << "Member not found or incorrect input."
                             << endl;
                    }
                    break;
                }

                case 4: {   // Quit
                    isNotQuit = false;
                    break;
                }

                default:     // Invalid input
                    cout << "Invalid input. Please try again!" << endl;
                    break;
            }
        }
    } while (isNotQuit);

    displayGoodbye();

    return 0;
}

void displayGreetings() {
    cout << "\nWelcome to the Book Recommendation Program." << endl;
    cout << "Program helps to find new books, add and rate books,\n"
         << "see your ratings.\n" << endl;
}

void displayGoodbye() {
    cout << "\nThank you for using the Book Recommendation Program!"
         << endl;
}

void displayMainMenu() {
    cout << endl;
    cout << "************** MENU **************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Login                       *" << endl;
    cout << "* 4. Quit                        *" << endl;
    cout << "**********************************" << endl;
}

void displaySubMenu() {
    cout << endl;
    cout << "************** MENU **************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Rate book                   *" << endl;
    cout << "* 4. View ratings                *" << endl;
    cout << "* 5. See recommendations         *" << endl;
    cout << "* 6. Logout                      *" << endl;
    cout << "**********************************" << endl;

}

void printBookNum(int count) {
    cout << endl;
    cout << "# of books: " << count << endl;
}

void printMemberNum(int count) {
    cout << "# of memberList: " << count << endl;
}

int populateMemberRatingLists(MemberList &mList, RatingList &rList) {
    ifstream inputFile; // create ifstream object to read from file
    string filename; // hold file name
    string line; // hold line from a file
    string name; // hold attributes of Book obj
    int mCount = 0; // size of 1D array (members)
    int rCount = 0; // rows of 2D array (ratings)
    int col; // columns of 2D array (ratings)
    int num; // read each integer in the line
    bool isValid = false; // validate the input file, control the loop

    do {
        cout << "Enter rating file: ";
        cin >> filename;

        inputFile.open(filename);
        if (inputFile) {
            isValid = true;
            while (getline(inputFile, line)) {
                name = line;
                mList.add(name);
                mCount++;

                getline(inputFile, line);
                stringstream ss(line);
                col = 0; // reset counter for new loop
                while (ss >> num) {
                    rList.add(rCount, col, num);
                    col++;
                }
                rCount++;
            }
        } else {
            cout << "Cannot open the file. Please try again!" << endl;
        }
    } while (!isValid);
    inputFile.close();
    return mCount;
}


int populateBookList(BookList &obj) {
    ifstream inputFile; // create ifstream object to read from file
    string filename; // hold file name
    string author, title, year; // hold attributes of Book obj
    int count = 0; // hold number of books
    bool isValid = false; // validate the input file, control the loop

    do {
        cout << "Enter books file: ";
        cin >> filename;

        inputFile.open(filename);
        if (inputFile) {
            isValid = true;
            while (getline(inputFile, author, ',')) {
                getline(inputFile, title, ',');
                getline(inputFile, year);
                obj.add(author, title, year);
                count++;
            }

        } else {
            cout << "Cannot open the file. Please try again!" << endl;
        }
    } while (!isValid);
    inputFile.close();
    return count;
}

int getValidInput(const string &message) {
    int input; // hold user's input
    bool isValid = false; // validate the input, control the loop

    while (!isValid) {
        cout << message;
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            isValid = true;
        }
    }
    return input;
}

int getValidRating() {
    int rating; // hold user's input (rating)
    bool isValid = false; // validate the input, control the loop
    do {
        rating = getValidInput("Enter you rating: ");
        if (rating == STRONG_DISLIKE || rating == DISLIKE ||
            rating == NOT_READ || rating == NEUTRAL
            || rating == LIKE || rating == STRONG_LIKE) {
            isValid = true;
        } else {
            cout << "Please enter a valid rating!\n";
        }
    } while (!isValid);
    return rating;
}

void addNewMember(MemberList &obj) {
    string newMember; // hold the name of new member

    cin.ignore();
    cout << "Enter the name of the new member: ";
    getline(cin, newMember);
    obj.add(newMember);
    cout << newMember + " (account #: " +
            to_string(obj.size()) + ") was added."
         << endl;
}

void addNewBook(BookList &obj) {
    string newAuthor; // hold the name of author
    string newTitle; // hold the title of the book
    string year; // hold year of the book

    cout << "Enter the author of the new book: ";
    cin.ignore();
    getline(cin, newAuthor);
    cout << "Enter the title of the new book: ";
    getline(cin, newTitle);
    cout << "Enter the year (or range of years) of the new book: ";
    getline(cin, year);
    obj.add(newAuthor, newTitle, year);
    cout << obj.getBookByIsbn(obj.size())
         << " was added."
         << endl;
}

void viewRatings(const MemberList &mList, const BookList &bList,
                 const RatingList &rList, int accountId) {
    cout << endl;
    cout << mList.getMemberById(accountId)
         << "'s ratings..."
         << endl;
    for (int i = 0; i < bList.size(); i++) {
        cout << bList.getBookByIsbn(i + 1)
             << " => rating: "
             << rList.getRating(accountId - 1, i) << "\n";
    }
}


void rateBook(const BookList &bList, RatingList &rList, int accountId) {
    string answer; // hold yes/no answer to re-rate the book
    int inputISBN; // hold isbn input
    bool exitLoop = false; // control the loop

    cout << "\nEnter the ISBN for the book you'd like to rate: ";
    cin >> inputISBN;

    while (!exitLoop) {
        if (bList.getBookByIsbn(inputISBN) == "0") {
            cout << "Book with such ISBN is not found!" << endl;
            exitLoop = true;
        } else {
            if (rList.getRating(accountId - 1, inputISBN - 1) !=
                NOT_READ) {

                cout << "Your current rating for "
                     << bList.getBookByIsbn(inputISBN)
                     << " => rating: "
                     << rList.getRating(accountId - 1,
                                        inputISBN - 1)
                     << endl;

                cin.ignore();
                cout << "Would you like to re-rate this book (y/n)? ";
                getline(cin, answer);

                while (!isValidYesNoAnswer(answer)) {
                    cout << "Please enter 'y' for yes or 'n' for no: ";
                    getline(cin, answer);
                }

                if (answer == "n") {
                    exitLoop = true;
                } else {
                    setNewRating(bList, rList, inputISBN, accountId);
                    exitLoop = true;
                }
            } else {
                setNewRating(bList, rList, inputISBN, accountId);
                exitLoop = true; // exit the loop
            }
        }
    }
}

bool isValidYesNoAnswer(const string &answer) {
    return (answer == "y" || answer == "n");
}

void setNewRating(const BookList &bList, RatingList &rList,
                  int inputISBN, int accountId) {
    int rating; // user's input (rating)
    rating = getValidRating();
    rList.add(accountId - 1,
              inputISBN - 1, rating);
    cout << "Your new rating for "
         << bList.getBookByIsbn(inputISBN)
         << " => rating: "
         << rList.getRating(accountId - 1,
                            inputISBN - 1)
         << endl;
}

void getRecommendations(const MemberList &mList, const BookList &bList,
                        const RatingList &rList, int accountId) {

    int bestMatchId; // track best matching member
    int bestSimilarity; // track best similarity

    bestMatchId = -1;
    bestSimilarity = -1;

    for (int i = 0; i < mList.size(); i++) {
        if (i != accountId - 1) { // exclude logged-in member

            int similarity = 0; // set sum to zero
            for (int j = 0; j < bList.size(); j++) {

                similarity += rList.getRating(accountId - 1, j) *
                              rList.getRating(i, j);
            }

            if (similarity > bestSimilarity) { // swap similarity to best one
                bestSimilarity = similarity;
                bestMatchId = i + 1; // update best match member
            }
        }
    }

        if (bestMatchId != -1) { // if best match member was found

        cout << "\nYou have similar taste in books as "
             << mList.getMemberById(bestMatchId) << "!" << endl;

        cout << "\nHere are the books they really liked:" << endl;

        for (int i = 0; i < bList.size(); i++) {
            if (rList.getRating(accountId - 1, i) == NOT_READ) {
                int rating = rList.getRating(bestMatchId - 1, i);

                if (rating == STRONG_LIKE) {  // recommend books rated 5
                    cout << bList.getBookByIsbn(i + 1) << endl;
                }
            }
        }

        cout << "\nAnd here are the books they liked:" << endl;
        for (int i = 0; i < bList.size(); i++) {
            if (rList.getRating(accountId - 1, i) == NOT_READ) {
                int rating = rList.getRating(bestMatchId - 1, i);

                if (rating == LIKE) {  // recommend books rated 3
                    cout << bList.getBookByIsbn(i + 1) << endl;
                }
            }
        }
    } else {
        cout << "No recommendations available." << endl;
    }
}


