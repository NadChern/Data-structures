// Author: Nadezhda Chernova
// File: MemberList.h
// Date: 10/10/23
// Specification file for the MemberList class.
// Purpose: The MemberList class includes private struct Member, that allows
// to keep track of members and their attributes (name, accountId, and
// login/logout status), consists of following functions (methods):
// constructors, destructor, overloaded = operator, copy constructor,
// add method (to add the member in the member list), to_string method
// (to represent member in string format), getMemberById method (to get member
// from the list), empty, size and resize methods as well as generateAccountId
// method, and methods to track login/logout status of the member.

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H

#include <string>
using namespace std;

class MemberList {

public:
    MemberList(int);
    // Constructor

    ~MemberList();
    // Destructor

    MemberList(const MemberList &);
    // Copy constructor

    MemberList &operator=(const MemberList &);
    // Overloaded = operator

    void add(const string &);
    // Add Member obj to array

    string to_string() const;
    // Convert Member obj to a string

    bool empty() const;
    // Check if the array is empty

    static int generateAccountId();
    //  Generate account ID

    int size() const;
    // Check the number of members

    string getMemberById(int) const;
    // Find member in array, return member in string format

   bool isLoggedIn(int) const;
   // Check for login/logout status

   void loginMember (int);
   // Change the status from logout to login

   void logoutMember(int);
   // Change the status from login to logout


private:
    struct Member {
        int accountId; // Account id of the member
        string name;  // Name of the member
        bool isLoggedIn; // Login/Logout status
        Member(); // Constructor
    };

    static int accountCount; // counter for account id
    Member *members; // pointer to the array of Book objects
    int numElements; // number of elements in the array
    int capacity; // capacity of the array

    void resize();
    // Resize array (when full)

};

#endif //P1_MEMBERLIST_H
