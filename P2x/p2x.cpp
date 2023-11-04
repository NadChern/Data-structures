// Author: Nadezhda Chernova
// File: p2.cpp
// Date: 10/31/23
// Purpose: This program tests functionality of BST template class on integers
//          and strings.
// Input:   Integer and string files from the user.
// Process: Creates two BST objects of integers and strings, displays empty
//          trees, inserts values to the trees from files, displays the trees
//          after inserting, tests functions such as insert, contains, remove,
//          traversals in different order, getLevel, getWidth, getHeight,
//          getLeafCount, getAncestors, checks for size, and if the tree
//          is empty.
// Output:  Displays introduction and goodbye messages, prompt to enter the
//          file name to read from, test titles and test results.


#include "BSTx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>


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

void displayIntTitle();
// Display title for integer BST testing section
// IN: none
// MODIFY:none
// OUT: none

void displayStrTitle();
// Display title for string BST testing section
// IN: none
// MODIFY:none
// OUT: none

string getValidString(string &);
// Validate user input to correct reading from file
// IN: user's input
// MODIFY: erase spaces
// OUT: verified input in a string format

template<typename T>
void displayEmptyBST(const BST<T> &);
// Display empty BST (with zero nodes, leaves, with height -1, empty -> true)
// IN: reference on the const BST object
// MODIFY:none
// OUT: none

template<typename T>
void displayStatistics(const BST<T> &);
// Get and display BST attributes
// (number of nodes, leaves, height, true/false from empty method)
// IN: reference on the const BST object
// MODIFY:none
// OUT: none

template<typename T>
void insertNumFromFile(BST<T> &, string &);
// Validate file, read from file if it's valid,
// insert numbers into BST in certain order, display the results
// IN: reference on the integers BST object, filename
// MODIFY: from empty BST to populated BST
// OUT: none

template<typename T>
void insertStrFromFile(BST<T> &, string &);
// Validate file, read from file if it's valid,
// insert strings into BST in certain order, display the results
// IN: reference on the string BST object, filename
// MODIFY: from empty BST to populated BST
// OUT: none

template<typename T>
void testTraversals(const BST<T> &);
// Display the results of testing traversal functions
// (pre-order, post-order, in-order traversals)
// IN: reference on the BST object
// MODIFY: none
// OUT: none

template<typename T>
void getTraversals(const BST<T> &tree);
// Get and display elements in pre-order, post-order and in-order traversal
// IN: reference on the BST object
// MODIFY: none
// OUT: none

template<typename T>
void testLevelAncestors(const BST<T> &, T *, int);
// Get the level and ancestor for each element of BST, display the results
// of testing getLevel and getAncestors functions
// IN: reference on the BST object, reference on the array (used to avoid
// duplicates), size of the array
// MODIFY: none
// OUT: none

template<typename T>
void testAddItems(BST<T> &, T *, int);
// Add some items to the current BST, display the results of testing insert
// function
// IN: reference on the BST object, reference on the array (used to insert
// values from it to BST and avoid duplicates), size of the array
// MODIFY: BST with added items as a result
// OUT: none

template<typename T>
void testContains(BST<T> &, T *, int);
// Check for existence of array values in BST object, displays the results of
// testing contains function
// IN: reference on the BST object, reference on the array, size of the array
// MODIFY: none
// OUT: none

template<typename T>
void testRemove(BST<T> &, T *, int);
// Remove elements from BST, display the results of testing remove function
// IN: reference on the BST object, reference on the array, size of the array
// MODIFY: BST after removing existing items as a result
// OUT: none

template<typename T>
void testCopyConstructor(const BST<T> &);
// Create new BST by using copy constructor, display the results of testing
// copy constructor
// IN: reference on the current BST object
// MODIFY: current BST is not modified, but the copy of current is created.
// OUT: none

template<typename T>
void testAssignmentOperator(const BST<T> &, T *, int);
// Create new BST, populate it with array values, assign current BST to new one,
// test the results of using assignment operator
// IN: reference on the BST object, reference on the array, size of the array
// MODIFY: newly created BST with the same data as current BST as a result
// OUT: none

int main() {
    string filename; // hold file name
    BST<int> tree1; // BST object of integers
    BST<string> tree2; // BST object of strings
    const int SIZE1 = 7; // size of the first array
    const int SIZE2 = 8; // size of second array
    int *intArr1; // pointer on the first array of integers
    intArr1 = new int[SIZE1]{40, 20, 10, 30, 60,
                             50, 70};

    int *intArr2; // pointer on the second array of integers
    intArr2 = new int[SIZE2]{20, 40, 10, 70,
                             99, -2, 59, 43};

    string *strArr1; // pointer on the first array of strings
    strArr1 = new string[SIZE1]{"mary", "gene", "bea", "jen",
                                "sue", "pat", "uma"};

    string *strArr2; // pointer on the second array of strings
    strArr2 = new string[SIZE2]{"gene", "mary", "bea",
                                "uma", "yan", "amy", "ron",
                                "opal"};

    displayGreetings();

    // Test integer BST
    displayIntTitle();
    displayEmptyBST(tree1);

    cout << "\nEnter integer file: ";
    getline(cin, filename);

    insertNumFromFile(tree1, filename);
    testTraversals(tree1);
    testLevelAncestors(tree1, intArr1, SIZE1);
    testContains(tree1, intArr2, SIZE2);
    testRemove(tree1, intArr2, SIZE2);
    testAddItems(tree1, intArr2, SIZE2);
    testCopyConstructor(tree1);
    testAssignmentOperator(tree1, intArr1, SIZE1);

    // Test string BST
    displayStrTitle();
    displayEmptyBST(tree2);

    cout << "\nEnter string file: ";
    getline(cin, filename);

    insertStrFromFile(tree2, filename);
    testTraversals(tree2);
    testLevelAncestors(tree2, strArr1, SIZE1);
    testContains(tree2, strArr2, SIZE2);
    testRemove(tree2, strArr2, SIZE2);
    testAddItems(tree2, strArr2, SIZE2);
    testCopyConstructor(tree2);
    testAssignmentOperator(tree2, strArr1, SIZE1);

    displayGoodbye();

    // Deallocate memory from the dynamic arrays
    delete[] intArr1;
    delete[] intArr2;
    delete[] strArr1;
    delete[] strArr2;

    return 0;
}


void displayGreetings() {
    cout << "\nWelcome to the BST driver program!" << endl;
    cout << "Program tests functionality of BST template class" << endl;
    cout << "on integers and strings.\n" << endl;
}


void displayGoodbye() {
    cout << "\nGoodbye!" << endl;
}


void displayIntTitle() {
    cout << "******************************" << endl;
    cout << "* INTEGER BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl;
}


void displayStrTitle() {
    cout << endl;
    cout << "******************************" << endl;
    cout << "* STRING BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl;
}


template<typename T>
void displayEmptyBST(const BST<T> &tree) {
    cout << endl;
    cout << "** CREATE BST **";
    displayStatistics(tree);
}


template<typename T>
void displayStatistics(const BST<T> &tree) {
    cout << "\n# of nodes:" << setw(3) << tree.size() << endl;
    cout << "# of leaves:" << setw(2) << tree.getLeafCount() << endl;
    cout << "BST height:" << setw(3) << tree.getHeight() << endl;
    cout << "BST empty?" << setw(3) << "" << boolalpha << tree.empty()
         << endl;
    cout << "BST width:" << setw(4) << tree.getWidth() << endl;
}


template<typename T>
void testTraversals(const BST<T> &tree) {
    cout << "\n** TEST TRAVERSALS **" << endl;
    getTraversals(tree);
}


template<typename T>
void getTraversals(const BST<T> &tree) {
    cout << "pre-order:   " << tree.getPreOrderTraversal() << endl;
    cout << "in-order:    " << tree.getInOrderTraversal() << endl;
    cout << "post-order:  " << tree.getPostOrderTraversal() << endl;
    cout << "level-level: " << tree.getLevelOrder() << endl;
}


template<typename T>
void insertNumFromFile(BST<T> &tree, string &filename) {
    ifstream inputFile; // create ifstream object to read from file
    string line; // hold line from file
    T num; // to insert integer into BST
    bool isValid = false; // validate the input file, control the loop

    do {
        inputFile.open(filename);
        if (inputFile) {
            isValid = true;

            cout << "\n** TEST INSERT **" << endl;
            cout << "Inserting in this order: ";

            while (getline(inputFile, line)) {
                cout << line << " ";
                stringstream ss(line);
                while (ss >> num)
                    tree.insert(num);
            }
        } else {
            cout << "Cannot open the file. Please try again!" << endl;
            cout << "Enter file name: ";
            getline(cin, filename);
        }
    } while (!isValid);

    inputFile.close();
    displayStatistics(tree);
}


template<typename T>
void insertStrFromFile(BST<T> &tree, string &filename) {
    ifstream inputFile; // create ifstream object to read from file
    string line; // hold line from file
    bool isValid = false; // validate the input file, control the loop

    do {
        inputFile.open(filename);
        if (inputFile) {
            isValid = true;

            cout << "\n** TEST INSERT **" << endl;
            cout << "Inserting in this order: ";

            while (getline(inputFile, line)) {
                line = getValidString(line);
                cout << line << " ";
                tree.insert(line);
            }
        } else {
            cout << "Cannot open the file. Please try again!" << endl;
            cout << "Enter file name: ";
            getline(cin, filename);
        }
    } while (!isValid);

    inputFile.close();
    displayStatistics(tree);
}


string getValidString(string &str) {
    string line; // hold verified line from file (no space)
    for (char s: str) {
        if (!isspace(s)) {
            line += s;
        }
    }
    return line;
}


template<typename T>
void testLevelAncestors(const BST<T> &tree, T *arr, int size) {
    int level; // level of BST item
    string ancestors; // ancestors of BST item

    cout << "\n** TEST LEVEL & ANCESTORS **" << endl;
    for (int i = 0; i < size; i++) {
        level = tree.getLevel(arr[i]);
        ancestors = tree.getAncestors(arr[i]);
        cout << "level(" << arr[i] << "): " << level
             << ", " << "ancestors(" << arr[i] << "): "
             << ancestors << endl;
    }
}


template<typename T>
void testContains(BST<T> &tree, T *arr, int size) {
    cout << "\n** TEST CONTAINS **" << endl;
    for (int i = 0; i < size; i++) {
        cout << "contains(" << arr[i] << "): " << boolalpha
             << tree.contains(arr[i]) << endl;
    }
}


template<typename T>
void testRemove(BST<T> &tree, T *arr, int size) {
    cout << "\n** TEST REMOVE **" << endl;
    cout << "Removing in this order: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
        tree.remove(arr[i]);
    }
    displayStatistics(tree);
    getTraversals(tree);
}


template<typename T>
void testAddItems(BST<T> &tree, T *arr, int size) {
    cout << "\n** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
        tree.insert(arr[i]);
    }
    displayStatistics(tree);
    getTraversals(tree);
}


template<typename T>
void testCopyConstructor(const BST<T> &tree) {
    BST<T> newTree(tree); // create new BST by using copy constructor
    cout << "\n** TEST COPY CONSTRUCTOR **" << endl;
    cout << "Copy current tree to a new one..." << endl;
    cout << "Current tree's values: "
         << tree.getPreOrderTraversal() << endl;
    cout << "New tree's values:     " << newTree.getPreOrderTraversal();
    displayStatistics(newTree);
}

template<typename T>
void testAssignmentOperator(const BST<T> &tree, T *arr, int size) {
    BST<T> newTree; // new BST object
    cout << "\n** TEST OVERLOADED ASSIGNMENT OPERATOR **" << endl;
    cout << "BEFORE ASSIGNMENT: " << endl;
    cout << "Current tree's values: "
         << tree.getPreOrderTraversal() << endl;

    for (int i = 0; i < size; i++) { // insert data in BST
        newTree.insert(arr[i]);
    }

    cout << "New tree's values:     " << newTree.getPreOrderTraversal()
         << endl;
    cout << "AFTER ASSIGNMENT: " << endl;
    newTree = tree; // assignment operator
    cout << "Current tree's values: "
         << tree.getPreOrderTraversal() << endl;
    cout << "New tree's values:     " << newTree.getPreOrderTraversal()
         << endl;
}



