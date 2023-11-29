// Author: Nadezhda Chernova
// File: BST.h
// Date: 11/28/23
// Specification and implementation file for the template BST class with "TYPE"
// as template parameter with nested BSTNode and FrequencyCompare classes.
// Purpose: BST class is responsible for storing and managing data of
// generic type, includes BSTNode class - responsible for nodes in BST, and
// FrequencyCompare class to compare nodes in BSTNode class, and sort them
// using STL priority queue.
// The class includes constructor and destructor for BST class, pointer
// to the root of BST, constructors for BSTNode, pointers to the left, right
// children of the node, FrequencyCompare class has constructor and
// overloaded operator for comparing BSTNode objects.

#ifndef BST_h
#define BST_h

template<typename TYPE>
class BST {
protected :
public:
    class BSTNode {
    public:
        TYPE data; // node's value

        BSTNode(TYPE cf) : data(cf), left(nullptr), right(nullptr) {}
        // Constructor
        // IN: provided data
        // MODIFY: initializes node with data, set left, right ptr to nullptr
        // OUT: none

        BSTNode(BSTNode *l, BSTNode *r, TYPE cf) : data(cf), left(l),
                                                   right(r) {}
        // Constructor
        // IN: left, right pointers, data
        // MODIFY: initializes node with specific left, right children and data
        // OUT: none

        BSTNode *left, *right; // pointers to left and right children of node
    };

    class FrequencyCompare {
    public:

        FrequencyCompare() {}
        // Constructor to create FrequencyCompare objects
        // IN: none
        // MODIFY: none
        // OUT: none

        bool operator()(const BSTNode *lhs, const BSTNode *rhs) const {
            // Changing the comparison will change the priority queue ordering
            // (min vs max)
            return lhs->data >
                   rhs->data;
        }
        // Overloaded operator - compares data of left and right children
        // IN: pointers to left and right side nodes
        // MODIFY: none
        // OUT: true if left node is greater than right node, otherwise false
        // (it's min-heap, values with small data in higher priority)

    };

    BSTNode *root; // pointer to the root of BST

    void eraseTree(BSTNode *cur) {
        if (cur != nullptr) {
            eraseTree(cur->left);
            eraseTree(cur->right);
            delete cur;
        }
    }
    // Delete nodes in BST (post-order travers)
    // IN: root of BST
    // MODIFY: delete BST tree
    // OUT: none


public:

    BST() : root(nullptr) {}
    // Constructor
    // IN: none
    // MODIFY: set root to null - empty tree
    // OUT: none

    virtual ~BST() { eraseTree(root); }
    // Destructor (calls helper function eraseTree to delete nodes in BST)
    // IN: none
    // MODIFY: delete BST tree
    // OUT: none

};

#endif
