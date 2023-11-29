// Author: Nadezhda Chernova
// File: HuffmanTree.h
// Date: 11/28/23
// Specification for the HuffmanTree class, specification and implementation
// for CharFreq class
// Purpose: HuffmanTree class extends functionality of the BST class for the
// purpose of HuffmanTree encoding. Class uses BST to build and manipulate HuffmanTree
// tree for encoding and decoding. CharFreq class is responsible for storing
// and tracking chars, counting frequency and encoding.


#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <bitset>
#include "BST.h"

using namespace std;

class CharFreq {
public:

    CharFreq() : letter('\0'), frequency(0), encoding("") {}
    // Default constructor
    // IN: none
    // MODIFY: properties assigned default values
    // OUT: none

    CharFreq(unsigned char l, float f) : letter(l), frequency(f),
                                         encoding("") {}
    // Constructor
    // IN: provided letter and frequency values
    // MODIFY: initializes letter and frequency with provided values,
    // set encoding to empty string
    // OUT: none

    unsigned char letter; // store char
    float frequency; // store frequency of char
    string encoding; // store HuffmanTree encoding for char


    bool operator>(const CharFreq &rhs) const {
        return frequency > rhs.frequency;
    }
    // Overloaded operator - allows to compare obj on frequency
    // IN: reference to right side CharFreq object
    // MODIFY: none
    // OUT: true if the frequency of the left side ChatFreq(the one from which
    // the function is called) is greater, otherwise false
};

class HuffmanTree : BST<CharFreq> {
public:

    HuffmanTree() {}
    // Default constructor
    // IN: none
    // MODIFY: none
    // OUT: none

    bool createCodeTree(string filename);
    // Create HuffmanTree tree based on chars frequencies in the file
    // IN: file name
    // MODIFY: filename with chars is not modified, but huffmanTree object
    // by calling this function will be modified
    // (from default values to populated with data)
    // OUT: true if huffman tree was built successfully, otherwise false

    bool encodeFile(string originalFilename, string outputFilename);
    // Encode file using HuffmanTree tree, write encoded data to output file
    // IN: file with original data, file for encoded data
    // MODIFY: output file will be filled with encoded data
    // OUT: true if file is successfully encoded, and encoded data is written
    // to output file.

    bool decodeFile(string filename);
    // Decode encoded file (with help of traverseAndPrint func)
    // IN: file name to decode
    // MODIFY: none
    // OUT: true if the file is decoded, otherwise false

    void displayCode(ostream &out);
    // Display code in a specified format
    // IN: reference to output stream
    // MODIFY: output steam with huffman code in it
    // OUT: none

private:
    inline int traverseAndPrint(string &bits, int i) {
        return traverseAndPrint(bits, i, root);
    }
    // Helper function for decodeFile function, decode HuffmanTree encoded data
    // IN: reference to bit string (encoded data), current location from where
    // start to decode (starts from 0 index)
    // MODIFY: none
    // OUT: new position in the bit string

    int traverseAndPrint(string &bits, int i, BSTNode *cur);
    // Helper function for decoding for traverseAndPrint func
    // IN: reference to bit string (encoded data), current location from where
    // start to decode (starts from 0 index), root node
    // MODIFY: none
    // OUT: new position in the bit string

    void encodeBSTNodes(BSTNode *cur, const string &code);
    // Traverse huffman tree, assign a unique HuffmanTree code to each leaf node
    // IN: pointer to the root, reference to string (which will store
    // accumulated binary code)
    // start to decode (starts from 0 index), root node
    // MODIFY: none
    // OUT: none

    void displayCodeHelper(ostream &out, BSTNode *node, string code);
    // Helper function for displayCode function
    // Traverse huffman tree, output chars, frequency, huffman encoding,
    // ASCII values
    // IN: reference to output stream, root node pointer, empty string
    // MODIFY: none
    // OUT: none

    string getEncoding(char ch);
    // Helper function for encodeFile function
    // Find and return encoding for a given char
    // IN: provided chat to encode
    // MODIFY: none
    // OUT: encoding for given char or empty string (if not found)

    bool getEncodingHelper(BSTNode *node, char ch, string &code);
    // Helper function for getEncoding function
    // Find and return encoding for a given char
    // IN: pointer to the root, char to encode, reference to empty string
    // (to fill it with encoding)
    // MODIFY: none
    // OUT: true, if char was found, otherwise false
};

ostream &operator<<(ostream &out, HuffmanTree &code);
// Overloaded operator - to output HuffmanTree  obj to output streams
// IN: reference to output stream, reference to HuffmanTree obj whose data will
// be output
// MODIFY: output stream with huffman tree data,
// OUT: none

#endif 
