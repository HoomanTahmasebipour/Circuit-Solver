//
//  Parser.cpp
//  ece241_lab2_parser
//
//  Created by Hooman Tahmasebipour on September 26, 2017, 1:47 PM.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#define MAX_NODE_NUMBER 5000
#define MIN_NODE_NUMBER 0

using namespace std;

bool validInput(stringstream & lineStream, int errorCase, string name, double resistance, int nodeid1, int nodeid2);
void insertR(stringstream & lineStream);
void modifyR(stringstream & lineStream);
void printR(stringstream & lineStream);
void printNode(stringstream & lineStream);
void deleteR(stringstream & lineStream);

int main(int argc, char** argv) {
    string line, command, rest;
    cout << "> ";
    getline(cin, line);
    while (!cin.eof()) {
        stringstream lineStream (line);
        lineStream >> command;
            if (command == "insertR") {
                insertR(lineStream);
            }
            else if (command == "modifyR") {
                modifyR(lineStream);
            }
            else if (command == "printR") {
                printR(lineStream);
            }
            else if (command == "printNode") {
                printNode(lineStream);
            }
            else if (command == "deleteR") {
                deleteR(lineStream);
            }
            else {
                cout << "Error: invalid command\n";
            }
        cout << "> ";
        getline(cin, line);
        }
    
    return 0;
}

void insertR (stringstream & lineStream) {
    string name = "empty";
    double resistance = 0;
    int nodeid1 = 0, nodeid2 = 0;
    bool valid = true;
    
    lineStream >> name;
    if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
    else
        if (!(validInput(lineStream, 5, name, resistance, nodeid1, nodeid2))) valid = false;
        else
            if (!(validInput(lineStream, 7, name, resistance, nodeid1, nodeid2))) valid = false;
    if (valid) {
        lineStream >> resistance;
        if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
        else
            if (!(validInput(lineStream, 3, name, resistance, nodeid1, nodeid2))) valid = false;
            else
                if (!(validInput(lineStream, 7, name, resistance, nodeid1, nodeid2))) valid = false;
    }
    if (valid) {
        lineStream >> nodeid1;
        if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
            else
                if (!(validInput(lineStream, 4, name, resistance, nodeid1, nodeid2))) valid = false;
                else
                    if (!(validInput(lineStream, 7, name, resistance, nodeid1, nodeid2))) valid = false;
    }
    if (valid) {
        lineStream >> nodeid2;
        if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
            else
                if (!(validInput(lineStream, 4, name, resistance, nodeid1, nodeid2))) valid = false;
                else
                    if (!(validInput(lineStream, 6, name, resistance, nodeid1, nodeid2))) valid = false;
                    else
                            if (!(validInput(lineStream, 8, name, resistance, nodeid1, nodeid2))) valid = false;
                            else cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed
                                      << resistance << " Ohms " << nodeid1 << " -> " << nodeid2 << endl;
    }
    return;
}

void modifyR(stringstream & lineStream) {
    string name = "empty";
    double resistance = 0;
    int nodeid1 = 0, nodeid2 = 0;
    bool valid = true;
    
    if (validInput(lineStream, 7, name, resistance, nodeid1, nodeid2)) {
    lineStream >> name;
    if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
    else
        if (!(validInput(lineStream, 5, name, resistance, nodeid1, nodeid2))) valid = false;
        else
            if (!(validInput(lineStream, 7, name, resistance, nodeid1, nodeid2))) valid = false;
    if (valid) {
        lineStream >> resistance;
        if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
        else
            if (!(validInput(lineStream, 3, name, resistance, nodeid1, nodeid2))) valid = false;
            else
                if (!(validInput(lineStream, 8, name, resistance, nodeid1, nodeid2))) valid = false;
                else cout << "Modified: resistor " << name << " to " << setprecision(2) << fixed
                          << resistance << " Ohms\n";
    }
    }
    return;
}

void printR(stringstream & lineStream) {
    string name = "empty";
    double resistance = 0;
    int nodeid1 = 0, nodeid2 = 0;
    bool valid = true;
    if (validInput(lineStream, 7, name, resistance, nodeid1, nodeid2)) {
    lineStream >> name;
        if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
        else
            if (!(validInput(lineStream, 8, name, resistance, nodeid1, nodeid2))) valid = false;
            else
                if (name == "all") cout << "Print: all resistors\n";
                else cout << "Print: resistor " << name << endl;
    }
    return;
}

void printNode(stringstream & lineStream) {
    string name = "empty";
    double resistance = 0;
    int nodeid2 = 0;
    bool valid = true;
    
    if ((validInput(lineStream, 7, name, resistance, MIN_NODE_NUMBER, nodeid2))) {
        lineStream >> nodeid2;
        if (!lineStream.fail()) {
            if (!(validInput(lineStream, 2, name, resistance, MIN_NODE_NUMBER, nodeid2))) valid = false;
            else
                if (!(validInput(lineStream, 4, name, resistance, MIN_NODE_NUMBER, nodeid2))) valid = false;
                    else
                        if (!(validInput(lineStream, 8, name, resistance, MIN_NODE_NUMBER, nodeid2))) valid = false;
                        else cout << "Print: node " << nodeid2 << endl;
        }
        else {
            lineStream.clear();
            lineStream >> name;
            if (!(validInput(lineStream, 2, name, resistance, MIN_NODE_NUMBER, nodeid2))) valid = false;
            else
                if (name != "all") cout << "Error: invalid argument";
                else
                    if (!(validInput(lineStream, 8, name, resistance, MIN_NODE_NUMBER, nodeid2))) valid = false;
                    else cout << "Print: all nodes\n";
        }
    }
    return;
}


void deleteR(stringstream & lineStream) {
    string name = "empty";
    double resistance = 0;
    int nodeid1 = 0, nodeid2 = 0;
    bool valid = true;
    if ((validInput(lineStream, 7, name, resistance, nodeid1, nodeid2))){
        lineStream >> name;
        if (!(validInput(lineStream, 2, name, resistance, nodeid1, nodeid2))) valid = false;
        else
            if (!(validInput(lineStream, 8, name, resistance, nodeid1, nodeid2))) valid = false;
            else
                if (name == "all") cout << "Deleted: all resistors\n";
                else cout << "Deleted: resistor " << name << endl;
    }
    return;
}

bool validInput(stringstream & lineStream, int errorCase, string name, double resistance, int nodeid1, int nodeid2) {
    bool valid = true;
    string restOfStream;
    switch(errorCase) {
        case 2: // argument of correct type
            if (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof()) {
                    cout << "Error: invalid argument\n";
                    lineStream.clear();
                    valid = false;
            }
            else if (lineStream.fail() && !lineStream.eof()){
                valid = false;
                lineStream.clear();
                cout << "Error: invalid argument\n";
            }
            break;
        
        case 3: // negative R value
            if (resistance < 0) {
                cout << "Error: negative resistance\n";
                valid = false;
            }
            break;
        
        case 4: // nodeid is out of range
            if (nodeid1 < MIN_NODE_NUMBER || nodeid1 > MAX_NODE_NUMBER) {
                cout << "Error: node " << nodeid1 << "is out of permitted range " << MIN_NODE_NUMBER << "-" << MAX_NODE_NUMBER << endl;
                valid = false;
            }
            else if (nodeid2 < MIN_NODE_NUMBER || nodeid2 > MAX_NODE_NUMBER) {
                cout << "Error: node " << nodeid2 << " is out of permitted range " << MIN_NODE_NUMBER << "-" << MAX_NODE_NUMBER << endl;
                valid = false;
            }
            break;
        
        case 5: // resistor name is all
            if (name == "all") {
                cout << "Error: resistor name cannot be the keyword “all”\n";
                valid = false;
            }
            break;
        
        case 6: // same node connection
            if (nodeid1 == nodeid2) {
                cout << "Error: both terminals of resistor connect to node " << nodeid1 << endl;
                valid = false;
            }
            break;
        
        case 7: // too few args
            if ((lineStream>>ws).eof()) {
                cout << "Error: too few arguments\n";
                valid = false;
            }
            else if (lineStream.eof()) {
                cout << "Error: too few arguments\n";
                valid = false;
            }
            break;
        
        case 8: // too many args
            if (!(lineStream>>ws).eof()) {
                // ws is a C++ function that ignores all whitespace until reaching a
                // character that is a different character, in the iomanip file
                cout << "Error: too many arguments\n";
                valid = false;
            }
            break;
        default:
            break;
            
    }

    return valid;
}
