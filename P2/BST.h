// Author: Nadezhda Chernova
// File: BST.h
// Date: 10/31/23
// Specification and implementation file for the template BST class.
// Purpose: The BST template class includes private struct Node, pointers to
// the root of the tree as well as right and left subtrees, private helper
// functions for public functions (methods).
// The following public functions are defined in the BST template class:
// constructor, destructor, copy constructor, assignment operator, insert,
// contains, remove, empty, size, getLeafCount, getHeight, getLevel,
// getInOrderTraversal, getPreOrderTraversal, getPostOrderTraversal,
// getAncestors.


#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

template<typename T>
class BST {

public:
    BST();
    // Constructor
    // IN: none
    // MODIFY: root is assigned to nullptr
    // OUT: none

    ~BST();
    // Destructor
    // IN: none
    // MODIFY: deleted tree from the heap
    // OUT: none

    BST(const BST<T> &);
    //  Copy constructor (create a copy of the BST passed in as a parameter)
    //  IN: reference on the BST object
    //  MODIFY: current BST is not modified,
    //  but the copy of current is created
    //  OUT: none

    BST &operator=(const BST&);
    // Overloaded assignment operator
    // Assign the BST passed in as a parameter to an existing BST
    // IN: reference on the BST object
    // MODIFY: existing BST with values from passed BST as a result
    // OUT: reference on the existing BST

    void insert(T);
    // Insert the element passed in as a parameter into the BST
    // IN: item to insert
    // MODIFY: BST object with inserted item as a result
    // OUT: none

    bool contains(T);
    // Search the BST to determine if a given value is present
    // IN: item to search
    // MODIFY: none
    // OUT: return true if item is found, else false

    void remove(T);
    // Removes the specified value from the BST
    // IN: item to remove
    // MODIFY: BST without item that was removed as a result
    // OUT: none

    bool empty() const;
    // Determines if BST is empty
    // IN: none
    // MODIFY: none
    // OUT: return true if empty, else false.

    int size() const;
    // Count the number of nodes in the tree
    // IN: none
    // MODIFY: none
    // OUT: return the count of nodes in the BST

    int getLeafCount() const;
    // Count the number of nodes in the BST that do not have any children
    // IN: none
    // MODIFY: none
    // OUT: return the count of leaf nodes

    int getHeight() const;
    // Count the height of the BST (empty BST has a height of -1,
    // BST with 1 element has the height of 0)
    // IN: none
    // MODIFY: none
    // OUT: return height of the tree

    int getLevel(const T &) const;
    // Define the level of the node with value passed in as a parameter
    // IN: value of the node
    // MODIFY: none
    // OUT: return the level of a node in the BST.
    // If the node with the given value is not present in the BST, returns -1

    string getPreOrderTraversal() const;
    // Traverse elements of BST in pre-order traversal
    // IN: none
    // MODIFY: none
    // OUT: return a string of elements in the order specified by the pre-order
    // traversal of the BST

    string getInOrderTraversal() const;
    // Traverse elements of BST in in-order traversal
    // IN: none
    // MODIFY: none
    // OUT: return a string of elements in the order specified by the in-order
    // traversal of the BST

    string getPostOrderTraversal() const;
    // Traverse elements of BST in post-order traversal
    // IN: none
    // MODIFY: none
    // OUT: return a string of elements in the order specified by the
    // post-order traversal of the BST

    string getAncestors(const T &) const;
    // Get ancestors of the given node, which value passed in as a parameter
    // IN: value of the node
    // MODIFY: none
    // OUT: return a string of elements that are the ancestor(s)
    // of the given node. If the value is not present in the BST,
    // returns an empty string.

private:
    struct Node {
        T data; // data of the node
        Node *left; // pointer to the left subtree
        Node *right; // pointer to the right subtree
    };
    Node *root; // pointer to the root of the tree

    void insert(Node *&, Node *&);
    // Helper function for public function insert
    // IN: references on pointers of new inserting node, root(current node)
    // MODIFY: BST object with inserted item as a result
    // OUT: none

    void remove(Node *&, T);
    // Helper function for public function remove
    // IN: reference on pointer of the root(current node), item to remove
    // MODIFY: BST without item that was removed as a result
    // OUT: none

    void makeDeletion(Node *&);
    // Helper function for private remove function
    // IN: reference on pointer of the root(current node), item to remove
    // MODIFY: BST without item that was removed as a result
    // OUT: none

    void destroyTree(Node *&);
    // Helper function for destructor
    // IN: reference on pointer of the root node
    // MODIFY: BST deleted from the heap
    // OUT: none

    void copyTree(Node *&, const Node *);
    // Helper function for copy constructor, assignment operator
    // IN: reference on pointer of the new tree (root), pointer to the current
    // tree (root)
    // MODIFY: new tree with values of the current tree as a result
    // OUT: none

    void getPreOrderTraversal(Node *, stringstream &) const;
    // Helper function for thr public getPreOrderTraversal
    // IN: pointer to the root(current node), stream object to capture
    // string traversal
    // MODIFY: none
    // OUT: none

    void getPostOrderTraversal(Node *, stringstream &) const;
    // Helper function for thr public getPostOrderTraversal
    // IN: pointer to the root(current node), stream object to capture
    // string traversal
    // MODIFY: none
    // OUT: none

    void getInOrderTraversal(Node *, stringstream &) const;
    // Helper function for thr public getInOrderTraversal
    // IN: pointer to the root(current node), stream object to capture
    // string traversal
    // MODIFY: none
    // OUT: none

    int size(Node *) const;
    // Helper function for public size function
    // IN: pointer to the root (current node)
    // MODIFY: none
    // OUT: return the count of nodes in the BST

    int getLeafCount(Node *) const;
    // Helper function for public getLeafCount function
    // IN: pointer to the root (current node)
    // MODIFY: none
    // OUT: return the count of leaf nodes

    int getHeight(Node *) const;
    // Helper function for public getHeight function
    // IN: pointer to the root (current node)
    // MODIFY: none
    // OUT: return height of the tree

    int getLevel(Node *, const T &, int) const;
    // Helper function for public getLevel function
    // IN: pointer to the root(current node), reference on the item, starting
    // level
    // MODIFY: none
    // OUT: return the level of a node in the BST

    void getAncestors(Node *, const T &, stringstream &) const;
    // Helper function for public getAncestors function
    // IN: pointer to the root(current node), reference on the item, stream
    // object to capture string of ancestors
    // MODIFY: none
    // OUT: return a string of elements that are the ancestor(s)
    // of the given node.

    bool contains(Node *, T &);
    // Helper function for public contains function
    // IN: pointer to the root(current node), reference on the item
    // MODIFY: none
    // OUT: return true if item is found, else false

};


template<typename T>
BST<T>::BST() {
    root = nullptr;
}


template<typename T>
BST<T>::~BST() {
    destroyTree(root);
}


template<typename T>
void BST<T>::destroyTree(Node *&ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}


template<typename T>
BST<T>::BST(const BST<T> &obj) {
    root = nullptr;
    copyTree(root, obj.root);

}


template<typename T>
void BST<T>::copyTree(Node *&newTree, const Node *currTree) {
    if (currTree == nullptr) {
        newTree = nullptr;
    } else {
        newTree = new Node; // create new node of BST in the heap
        newTree->data = currTree->data;
        newTree->left = newTree->right = nullptr;
        copyTree(newTree->left, currTree->left);
        copyTree(newTree->right, currTree->right);
    }
}


template<typename T>
BST<T> & BST<T>::operator=(const BST<T> & obj) {
    if(this != &obj) {
        destroyTree(root);
        copyTree(root, obj.root);
    }
    return *this;
}


template<typename T>
int BST<T>::size() const {
    return size(root);
}


template<typename T>
int BST<T>::size(Node *ptr) const {
    int leftSum; // hold number of left nodes
    int rightSum; // hold number of right nodes

    if (ptr != nullptr) {
        leftSum = size(ptr->left);
        rightSum = size(ptr->right);
        return 1 + leftSum + rightSum;
    }
    return 0;
}


template<typename T>
bool BST<T>::empty() const {
    return root == nullptr;
}


template<typename T>
int BST<T>::getLeafCount() const {
    if (empty()) {
        return 0;
    }
    return getLeafCount(root);
}


template<typename T>
int BST<T>::getLeafCount(Node *ptr) const {
    if (ptr == nullptr) {
        return 0;
    }
    if (ptr->left == nullptr && ptr->right == nullptr) {
        return 1;
    }
    return getLeafCount(ptr->left) + getLeafCount(ptr->right);
}


template<typename T>
int BST<T>::getHeight() const {
    return getHeight(root);
}


template<typename T>
int BST<T>::getHeight(Node *ptr) const {
    if (ptr == nullptr) {
        return -1;
    } else {
        return 1 + max(getHeight(ptr->left), getHeight(ptr->right));
    }
}


template<typename T>
int BST<T>::getLevel(const T &item) const {
    return getLevel(root, item, 0);
}


template<typename T>
int BST<T>::getLevel(Node *ptr, const T &item, int level) const {
    if (ptr == nullptr) {
        return -1;
    }
    if (ptr->data == item) {
        return level;
    } else if (ptr->data > item) {
        return getLevel(ptr->left, item, level + 1);
    } else {
        return getLevel(ptr->right, item, level + 1);
    }
}


template<typename T>
string BST<T>::getAncestors(const T &item) const {
    if (empty()) {
        return "";
    }
    if (root->data == item) {
        return "";
    }
    stringstream ss;
    getAncestors(root, item, ss);
    return ss.str();
}


template<typename T>
void BST<T>::getAncestors(Node *ptr, const T &item, stringstream &ss) const {
    if (ptr == nullptr) {
        return;
    }
    if (ptr->data == item) {
        return;
    }

    if (ptr->data > item) {
        getAncestors(ptr->left, item, ss);
    } else {
        getAncestors(ptr->right, item, ss);
    }
    ss << ptr->data << " ";
}



template<typename T>
bool BST<T>::contains(T item) {
    return contains(root, item);
}


template<typename T>
bool BST<T>::contains(Node *ptr,T &item) {
    if (ptr == nullptr) {
        return false;
    }
    if (ptr->data == item) {
        return true;
    }

    if (ptr->data > item) {
        return contains(ptr->left, item);
    } else {
        return contains(ptr->right, item);
    }
}


template<typename T>
void BST<T>::insert(T item) {
    Node *newNode = new Node; // create new node
    newNode->data = item;
    newNode->left = newNode->right = nullptr;
    insert(root, newNode);
}


template<typename T>
void BST<T>::insert(Node *&ptr, Node *&newNode) {
    if (ptr == nullptr) {
        ptr = newNode;
    } else if (ptr->data > newNode->data) {
        insert(ptr->left, newNode);
    } else {
        insert(ptr->right, newNode);
    }
}


template<typename T>
void BST<T>::remove(T item) {
    remove(root, item);
}


template<typename T>
void BST<T>::remove(Node *&ptr, T item) {
    if (ptr != nullptr) {
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr);
    }
}


template<typename T>
void BST<T>::makeDeletion(Node *&ptr) {
    Node *curr = nullptr; // create temp node for deletion
    if (ptr != nullptr) {
        if (ptr->left == nullptr) {
            curr = ptr;
            ptr = ptr->right;
            delete curr;
        } else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr;
        } else {
            curr = ptr->right;
            while (curr->left != nullptr)
                curr = curr->left;
            ptr->data = curr->data;
            remove(ptr->right, curr->data);
        }
    }
}


template<typename T>
string BST<T>::getPreOrderTraversal() const {
    stringstream ss; // create stream object
    getPreOrderTraversal(root, ss);
    return ss.str();
}


template<typename T>
void BST<T>::getPreOrderTraversal(Node *ptr, stringstream &ss) const {
    if (ptr != nullptr) {
        ss << ptr->data << " ";
        getPreOrderTraversal(ptr->left, ss);
        getPreOrderTraversal(ptr->right, ss);
    }
}


template<typename T>
string BST<T>::getPostOrderTraversal() const {
    stringstream ss; // create stream object
    getPostOrderTraversal(root, ss);
    return ss.str();
}

template<typename T>
void BST<T>::getPostOrderTraversal(Node *ptr, stringstream &ss) const {
    if (ptr != nullptr) {
        getPostOrderTraversal(ptr->left, ss);
        getPostOrderTraversal(ptr->right, ss);
        ss << ptr->data << " ";
    }
}


template<typename T>
string BST<T>::getInOrderTraversal() const {
    stringstream ss; // create stream object
    getInOrderTraversal(root, ss);
    return ss.str();
}

template<typename T>
void BST<T>::getInOrderTraversal(Node *ptr, stringstream &ss) const {
    if (ptr != nullptr) {
        getInOrderTraversal(ptr->left, ss);
        ss << ptr->data << " ";
        getInOrderTraversal(ptr->right, ss);
    }
}


#endif // BST_H