// Author: Nadezhda Chernova
// File: p3.cpp
// Date: 11/14/23
// Purpose: This program simulates hospital triage system
//          (priority queue for emergency room), where patient's
//          priority is based on urgency level. The interface of the program
//          is a command-line prompt, that supports following commands: add
//          (adds patient's name and urgency level), peek (displays the patient
//          that is next in line), next (removes the waiting patient from the
//          priority system and announces the name), list (shows all patients
//          in waiting line), load (file), help (displays) help information
//          about program), quit.
// Input:   Prompts (add, next, peek, list, load, help, quit),
//          as well as filename with patients to test program.
// Process: The program uses Patient and PatientPriorityQueue classes to create
//          the hospital triage system. All patients are Patient objects,
//          stored in heap order (min heap is used here).
//          After entering the command the appropriate result is displayed.
// Output:  Displays introduction and goodbye messages, prompts to enter
//          commands, results of the prompts, error messages if something
//          went wrong.


#include "PatientPriorityQueue.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


void welcome();
// Prints welcome message.
// IN: none
// MODIFY:none
// OUT: none

void goodbye();
// Prints goodbye message.
// IN: none
// MODIFY:none
// OUT: none

void help();
// Prints help menu.
// IN: none
// MODIFY:none
// OUT: none

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.
// IN: user's input (command + data), reference on PatientPriorityQueue obj
// MODIFY: line split to command and data (filename/patient's name, priority)
// OUT: false if command "quit" or no command given, otherwise true

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.
// IN: user's input (command + data), reference on PatientPriorityQueue obj
// MODIFY: line split to command and data (patient's name, priority),
// added Patient obj to PatientPriorityQueue obj.
// OUT: none

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.
// IN: reference on PatientPriorityQueue obj
// MODIFY: none
// OUT: none

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.
// IN: reference on PatientPriorityQueue obj
// MODIFY: removed Patient obj from PatientPriorityQueue obj (vector<Patient>)
// OUT: none

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.
// IN: reference on PatientPriorityQueue obj
// MODIFY: none
// OUT: none

void execCommandsFromFileCmd(string, PatientPriorityQueue &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
// IN: filename, reference on PatientPriorityQueue obj
// MODIFY: none (indirectly can modify by calling processLine and
// depends on the commands from file)
// OUT: none

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.
// IN: string from the user
// MODIFY: split string (if there is space) into 2 parts: part before the space
// and part after the space (leaves in origin string, modifying it)
// OUT: part of the string before the space

string trim(string &);
// Remove leading/trailing spaces from the string
// IN: string from the user (name, priority)
// MODIFY: removed leading/trailing spaces in the string
// OUT: string with no spaces in the beginning/end of the string

int main() {
    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueue priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
    // get command
    string cmd = delimitBySpace(line); // hold command from user
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;
    return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority; // patient's priority
    string name; // patient's name

    // get priority and name
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    // remove leading/trailing spaces
    priority = trim(priority);
    name = trim(name);

    // validate priority is between 1 and 4
    if (!(priority == "immediate" || priority == "emergency" ||
          priority == "urgent" || priority == "minimal")) {
        cout << "Error: invalid priority level indicated. ";
        return;
    }

    // add patient
    Patient patient(name, priority); // patient with certain attributes
    priQueue.add(patient);
    cout << "Added patient \"" << name << "\" to the priority system\n";
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
    // shows next patient to be seen
    try {
        Patient patient = priQueue.peek(); // patient with the highest priority
        cout << "Highest priority patient to be called next: ";
        cout << patient.getName() << endl;
    } catch (const runtime_error &e) {
        cout << e.what() << endl;
    }
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
    // removes and shows next patient to be seen
    try {
        Patient patient = priQueue.remove(); // hold removed patient
        cout << "This patient will now be seen: ";
        cout << patient.getName() << endl;
    } catch (const runtime_error &e) {
        cout << e.what() << endl;
    }
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    // shows patient detail in heap order
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
    ifstream infile; // input file stream, to read data from file
    string line; // hold each line from the file

    // open and read from file
    infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage> " << line;
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

string delimitBySpace(string &s) {
    const char SPACE = ' '; // space character (delimiter)
    size_t pos = 0; // position of the first space char in string
    string result = ""; // part of the string before first space

    pos = s.find(SPACE);
    if (pos == string::npos) // if no space char found return origin string
        return s;

    result = s.substr(0, pos); // substring from pos 0 to space char
    s.erase(0, pos + 1); // delete from the string part before space
    return result;
}

void welcome() {
    cout << "Welcome to the hospital triage system.\n";
}

void goodbye() {
    cout << "Thank you for using the hospital triage system. Goodbye!\n";
}

void help() {
    cout << "add <priority-code> <patient-name>\n"
         << "            Adds the patient to the triage system.\n"
         << "            <priority-code> must be one of the 4 accepted "
            "priority codes:\n"
         << "                1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "            <patient-name>: patient's full legal name "
            "(may contain spaces)\n"
         << "next        Announces the patient to be seen next. "
            "Takes into account the\n"
         << "            type of emergency and the patient's arrival order.\n"
         << "peek        Displays the patient that is next in line, but keeps "
            "in queue\n"
         << "list        Displays the list of all patients that are still "
            "waiting\n"
         << "            in the order that they have arrived.\n"
         << "load <file> Reads the file and executes the command on each line\n"
         << "help        Displays this menu\n"
         << "quit        Exits the program\n";
}

string trim(string &str) {
    // find index of first char that is not a space
    size_t first = str.find_first_not_of(' '); // index of first char
    if (first == string::npos) {
        return "";
    }
    // find index of last char that is not a space
    size_t last = str.find_last_not_of(' '); // index of last char

    // return trimmed string
    return str.substr(first, (last - first + 1));
}

