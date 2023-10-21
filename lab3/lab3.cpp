// Author: Nadezhda Chernova
// File: lab3.cpp
// Date: 15/10/23
// Purpose: This is a simple palindrome testing program.
//          Prompts user for the filename, reads from file (line by line),
//          displays the results - if each line is a palindrome or not.
// Input:   User input of file to test.
// Process: Prompts the user for the filename, reads from the file, validates
//          lines from file to check for the palindrome case (erases space
//          between chars, transforms chars to lowercase), checks for
//          palindrome, displays results.
// Output:  Displays introduction and goodbye messages, the results of test,
//          error message if the file is invalid.

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

void displayGreetings();
// Display short introduction
// IN: none
// MODIFY: none
// OUT: none

void displayGoodbye();
// Display goodbye message
// IN: none
// MODIFY: none
// OUT: none

string getValidString(string &);
// Validate user input to correct reading from file
// and palindrome testing, return verified input
// IN: user's input
// MODIFY: erase spaces, transform tolower case user's input
// OUT: verified input in a string format

bool isPalindrome(string &);
// Test for palindrome case (recursively), return true if it's a palindrome,
// otherwise false
// IN: verified input from the file
// MODIFY: none
// OUT: true (palindrome) or false (not a palindrome)

bool isPalindrome(string &, size_t, size_t);
// Helper overloaded function
// IN: verified input from file in a string format,
// index of first char, index of last char in unsigned integer type
// MODIFY: none
// OUT: true (palindrome) or false (not a palindrome)

int main() {
    ifstream inputFile; // create ifstream object to read from file
    string filename; // file name from user
    string line; // hold line from file
    string verifiedLine; // hold line with lowercase chars, without white space
    bool isValid = false; // validate input file


    displayGreetings();

    do {
        cout << "Enter the filename: ";
        getline(cin, filename);
        filename = getValidString(filename);

        inputFile.open(filename);
        cout << endl;

        if (inputFile) {
            isValid = true;
            while (getline(inputFile, line)) {
                verifiedLine = getValidString(line);

                if (isPalindrome(verifiedLine)) {
                    cout << line << " is a palindrome!" << endl;
                } else {
                    cout << line << " is NOT a palindrome!" << endl;
                }
            }
        } else {
            cout << "Cannot open the file. Please try again!" << endl;
        }
    } while (!isValid);

    inputFile.close();

    displayGoodbye();

    return 0;
}


void displayGreetings() {
    cout << "\nWelcome to the palindrome testing program!\n" << endl;
}

void displayGoodbye() {
    cout << "\nThanks for using the palindrome tester!" << endl;
}

string getValidString(string &str) {
    string line; // hold verified line from file (lowercase, no space)

    for (char s: str) {
        if (!isspace(s)) {
            // cast char to int and result back to char
            s = static_cast<char> (tolower(static_cast<int>(s)));
            line += s;
        }
    }
    return line;
}


bool isPalindrome(string &str) {
    return isPalindrome(str, 0, str.length() - 1);
}

bool isPalindrome(string &str, size_t first, size_t last) {
    if (first >= last)
        return true;

    if (str[first] == str[last]) {
        return isPalindrome(str, first + 1, last - 1);
    }

    return false;
}