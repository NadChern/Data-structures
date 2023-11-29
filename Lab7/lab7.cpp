// Author: Nadezhda Chernova
// File: lab7.cpp
// Date: 11/28/23
// Purpose: This program tests functionality of HuffmanTree class.
//          The program examines the source input file's contents and count
//          the number of occurrences of each character. Then places each char
//          and its frequency in each CharFreq object, and creates BST of nodes
//          with CharFreq objects. Then places all the nodes in sorted priority
//          queue. After that constructs HuffmanTree tree (by removing 2 nodes from
//          the queue and merging new node to queue). When the tree is
//          constructed, traverse the tree to discover the binary encodings
//          of each char. Re-examines the source file's contents, and for each
//          char, output the encoded binary version of that char to the
//          output file.
// Input:   Input and output file names to encode and decode data.
// Process: The program reads input file, creates HuffmanTree object to built
//          HuffmanTree tree, encodes chars to output file, decodes
//          chars, displays the results.
//          After entering the command the appropriate result is displayed.
// Output:  Displays prompts to enter filenames, results of decoding as well
//          as HuffmanTree tree char encoding map with chars, their frequencies,
//          ASCII values, and encoding.


// Analysis (extra credit)
//  1. Book from Project Gutenberg: [Alice's Adventures in Wonderland] by
//  [Lewis Carroll]
//  2. Encoded file size: [98 KB SIZE]
//     Original file size: [174 KB SIZE]
//     Percent savings: [44]% savings
//  3. gzip compressed book size: [62 KB SIZE]
//     The gzip compressed file is the [SMALLER] than the encoded book

#include "HuffmanTree.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char * argv[])
{
    HuffmanTree hc; // huffmanTree object
    string inputFile, outputFile; // input and output file names

    cout << "Please enter the input filename: ";
    cin >> inputFile;
    cout << "Please enter the output.txt file: ";
    cin >> outputFile;    

    // create code tree
    hc.createCodeTree(inputFile);

    // encode file
    hc.encodeFile(inputFile, outputFile);

    // decode file
    hc.decodeFile(outputFile);
        
    // print
    cout << hc;

    return 0;
}
