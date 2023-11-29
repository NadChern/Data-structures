// Author: Nadezhda Chernova
// File: HuffmanTree.cpp
// Date: 11/28/23
// Implementation for the HuffmanTree Class
// Functionality of the HuffmanTree Class includes creating HuffmanTree tree,
// encoding and decoding files, displaying the results in a specified format.


#include "HuffmanTree.h"
#include <vector>
#include <queue>
#include <algorithm>
#include "BST.h"

bool HuffmanTree::createCodeTree(string filename) {
    std::priority_queue<
            BST<CharFreq>::BSTNode *, // pointer to BSTNode
            std::vector<BST<CharFreq>::BSTNode *>, // array of nodes -
            // container for priority queue
            BST<CharFreq>::FrequencyCompare // ordering in priority queue
    > myPriorityQ;  // create priority queue
    string str;     // temp var, to store lines of chars from file
    string allText = ""; // store chars from file
    ifstream infile;     // ifstream object to read from file
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        cout << "ERROR loading file!\n";
        return false;
    }

    while (!infile.eof()) {          // get all the lines
        getline(infile, str); // saves the line in string
        allText += str + "\n";
    }
    infile.close();

    // Denote each char and its frequency
    vector<CharFreq> arr; // store CharFreq objects with chars and freq
    float count = 1; // counter of frequency

    sort(allText.begin(), allText.end());
    for (size_t i = 0; i < allText.length(); i++) {
        if (i < allText.length() - 1 && allText[i] == allText[i + 1]) {
            count++;
        } else {
            arr.push_back(CharFreq(allText[i], count));
            count = 1;
        }
    }

    // Create priority queue of nodes
    for (size_t i = 0; i < arr.size(); i++) {
        myPriorityQ.push(new BSTNode(arr[i]));
    }

    // HuffmanTree tree construction from priority queue
    // Remove and merge until 1 left
    while (myPriorityQ.size() > 1) {

        // Remove 2 nodes
        BSTNode *leftChild = myPriorityQ.top(); // first removed node
        myPriorityQ.pop();
        BSTNode *rightChild = myPriorityQ.top(); // second removed node
        myPriorityQ.pop();
        CharFreq removedNodes('\0', leftChild->data.frequency +
                                    rightChild->data.frequency);

        // Create new node that will have removed nodes and sum of their freq
        BSTNode *subtree = new BSTNode(removedNodes); // node for removed n
        subtree->left = leftChild;
        subtree->right = rightChild;
        myPriorityQ.push(subtree);
    }

    root = myPriorityQ.top();

    // Encode each node in the tree
    encodeBSTNodes(root, "");

    return true;
}

void HuffmanTree::encodeBSTNodes(BSTNode *cur, const string &code) {
    if (cur == nullptr) {
        return;
    }
    if (cur->left == nullptr && cur->right == nullptr) {
        cur->data.encoding = code;
        return;
    }
    encodeBSTNodes(cur->left, code + "0");
    encodeBSTNodes(cur->right, code + "1");
}


bool HuffmanTree::encodeFile(string originalFilename, string outputFilename) {
    string str; // temp var, to store lines of chars from file
    string allText = ""; // all chars read from file
    string currentStream = ""; // huffman code (bits)
    ifstream infile; // ifstream object to read from file
    const int WRITE_SIZE = 8; // size of each part of data

    infile.open(originalFilename.c_str());
    if (!infile.is_open()) {
        cout << "ERROR loading file!\n";
        return false;
    }

    while (!infile.eof()) {        // To get you all the lines.
        getline(infile, str);   // Saves the line in string.
        allText += str + "\n";
    }

    infile.close();

    std::ofstream outStream(outputFilename.c_str(), std::ios::binary);
    if (!outStream.is_open()) {
        cout << "ERROR creating output.txt file!\n";
        return false;
    }

    for (int i = 0; i < (int) allText.length(); i++) {
        char ch = allText[i]; // each char from allText
        string code = getEncoding(ch); // huffman code for each char
        currentStream += code; // accumulated binary code

        while ((int) currentStream.length() > WRITE_SIZE) {
            string byte = currentStream.substr(0, WRITE_SIZE);
            // substring of current stream
            bitset<8> set(byte);
            const char toWrite = (unsigned char) ((unsigned int) set.to_ulong());
            // represents bitset
            outStream.write(&toWrite, sizeof(char));
            currentStream = currentStream.substr(WRITE_SIZE,
                                                 currentStream.length() -
                                                 WRITE_SIZE);
        }
    }
    outStream.close();
    return true;
}

string HuffmanTree::getEncoding(char ch) {
    string code; // empty string to store encoding
    if (!getEncodingHelper(root, ch, code)) {
        return "";
    }
    return code;
}


bool HuffmanTree::getEncodingHelper(BSTNode *node, char ch, string &code) {
    if (node == nullptr) {
        return false;
    }

    if (node->left == nullptr && node->right == nullptr) {
        if (node->data.letter == ch) {
            return true;
        }
        return false;
    }

    // Search left subtree
    code.push_back('0');
    if (getEncodingHelper(node->left, ch, code)) {
        return true;
    }
    code.pop_back();

    // Search right subtree
    code.push_back('1');
    if (getEncodingHelper(node->right, ch, code)) {
        return true;
    }
    code.pop_back();
    return false;
}

bool HuffmanTree::decodeFile(string filename) {
    int i = 0; // position in the bit string to start traversing
    string bitStream = ""; // store binary code
    ifstream encodedfile; // ifstream object to read from file

    // Open encoded file in binary mode
    encodedfile.open(filename.c_str(), ios::binary);
    if (!encodedfile.is_open()) {
        cout << "ERROR opening encoded file!\n";
        return false;
    }

    // Set stream to read white spaces
    encodedfile >> std::noskipws;

    // Read each byte from file until EOF
    while (!encodedfile.eof()) {
        unsigned char readMe; // byte (char) to read
        encodedfile >> readMe;
        // convert each byte to bitset
        bitset<8> set((unsigned long) readMe);
        bitStream += set.to_string();
    }

    encodedfile.close();
    bitStream.erase(bitStream.length() - 8, 8);

    // Traverse and decode data (stats at position i = 0)
    while (i != -1)
        i = traverseAndPrint(bitStream, i);
    return true;
}

int HuffmanTree::traverseAndPrint(string &bits, int i, BSTNode *cur) {
    if (i >= (int) bits.length())
        return -1;

    // If leaf node, print the char
    if (cur->left == nullptr && cur->right == nullptr) {
        cout << cur->data.letter;
        return i;
    }

    if (bits[i] == '0') {
        return traverseAndPrint(bits, i + 1, cur->left);
    } else {
        return traverseAndPrint(bits, i + 1, cur->right);
    }
}

void HuffmanTree::displayCode(ostream &out) {
    cout << "\n" << endl;
    cout
            << "***************************************************************"
               "********************"
            << endl;
    cout
            << "*                       HuffmanTree Tree Character Encoding Map                       *"
            << endl;
    cout
            << "*                 (EON == Extended ASCII Or Non-ASCII Character)                  *"
            << endl;
    cout
            << "***************************************************************"
               "********************"
            << endl;
    displayCodeHelper(out, root, "");
}

ostream &operator<<(ostream &out, HuffmanTree &code) {
    code.displayCode(out); // call displayCode on HuffmanTree obj
    return out;
}

void HuffmanTree::displayCodeHelper(ostream &out, BSTNode *cur, string code) {
    if (cur == nullptr) {
        return;
    }
    // Traverse HuffmanTree tree
    if (cur->left == nullptr && cur->right == nullptr) {
        out << "Character: ";
        if (cur->data.letter >= 128 && cur->data.letter < 255) {
            out << "EON\t";
        } else if (cur->data.letter == ' ') {
            out << "SPC\t";
        } else if (cur->data.letter == '\n') {
            out << "LF\t";
        } else {
            out << cur->data.letter << "\t";
        }
        out << "\tASCII Value: " << static_cast<int>(cur->data.letter)
            << "   \t"
            << "\tFrequency: " << cur->data.frequency << "\t"
            << "\tEncoding: " << code << endl;
    }
    displayCodeHelper(out, cur->left, code + "0");
    displayCodeHelper(out, cur->right, code + "1");
}