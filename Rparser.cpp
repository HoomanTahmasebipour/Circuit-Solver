//
//  Rparser.cpp
//  ece244_lab3_inpt&store
//
//  Created by Hooman Tahmasebipour on 2017-10-16.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include "Rparser.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#define MIN_NODE_NUMBER 0

using namespace std;

int maxNodeNumber = 0;
int maxResistors = 0;
int resIndex = 0;
int nodeIndex = 0;
Resistor** ResArray = NULL;
Node* NodeArray = NULL;

void maxVal(stringstream & lineStream, bool noInserts) {
    string name = "empty";
    bool valid = true;
    
    lineStream >> maxNodeNumber;
    if (!(validArgument(lineStream))) valid = false;
    else
        if (!(tooFewArgs (lineStream))) valid = false;
        else
            if (!(greaterThanZero(maxNodeNumber))) valid = false;
    
    if(valid) {
        lineStream >> maxResistors;
        if (!(validArgument(lineStream))) valid = false;
        else
            if (!(tooManyArgs (lineStream))) valid = false;
            else
                if (!(greaterThanZero(maxNodeNumber))) valid = false;
                else {
                    if (!noInserts) {
                        deleteFunct();
                        delete [] ResArray;
                        ResArray = NULL;
                    }
                    cout << "New network: max node number is " << maxNodeNumber
                          << "; max resistors is " << maxResistors << endl;
                    NodeArray = new Node[maxNodeNumber + 1];
                    ResArray = new Resistor*[maxResistors];
                    for (int j = 0; j < maxResistors; j++) {
                        ResArray[j] = NULL;
                    }
                }
    }
    return;
}

void insertR (stringstream & lineStream, bool noInserts) {
    string name = "empty";
    double resistance = 0;
    int nodeid[2] = {0, 0};
    bool valid = true;
    
    lineStream >> name;
    // checking if resistor array is full

    if (!(validArgument(lineStream))) valid = false;
    // First checking if argument is valid
    else
        if (!nameIsNotAll (name)) valid = false;
        // if the argument is valid, then we check that it's not all
        else
            if (!(tooFewArgs (lineStream))) valid = false;
            // we make sure there are enough arguments for the command
    if (valid) {
        // only checks the rest of the stream if the previous argument passed all tests
        lineStream >> resistance;
        if (!(validArgument(lineStream))) valid = false;
        else
            if (!(validResistance (resistance))) valid = false;
        // making sure the resistance value is positive
            else
                if (!(tooFewArgs (lineStream))) valid = false;
                // making sure there are still enough arguments for the command
    }
    if (valid) {
        // only checks the rest of the stream if the previous arguments passed all tests
        lineStream >> nodeid[0];
        if (!(validArgument(lineStream))) valid = false;
        // First checking if argument is valid
            else
                if (!(tooFewArgs (lineStream))) valid = false;
                // making sure there are enough arguments for the command
    }
    if (valid) {
        lineStream >> nodeid[1];
        // only checks the rest of the stream if the previous arguments passed all tests
        if (!(validArgument(lineStream))) valid = false;
        // First checking if argument is valid
        else
            if (!(nodeValWithinRange (nodeid[0], nodeid[1]))) valid = false;
        // making sure the node ID is within the pre-defined bounds
            else
                if (!(tooManyArgs (lineStream))) valid = false;
                // making sure this is the last argument
    }
    if (valid) {
        // making sure the node ID is within the pre-defined bounds
        if (!(nodeValWithinRange (nodeid[0], nodeid[1]))) valid = false;
        else
            // making sure resistor array is not filled
            if ((resArrayfull(resIndex))) valid = false;
            else
                // making sure the node has not been filled
                if (!(nodeHasSpace (NodeArray[nodeid[0]], resIndex) && nodeHasSpace(NodeArray[nodeid[1]], resIndex))) valid = false;
                else
                    // making sure the resistor name is unique
                    if (!noInserts && !(uniqueResName(name))) valid = false;
                    else
                        // making sure resistor is connected to different terminals
                        if (!differentNodes (nodeid[0], nodeid[1])) valid = false;
                        else {
                            cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed
                            << resistance << " Ohms " << nodeid[0] << " -> " << nodeid[1] << endl;
                            ResArray[resIndex] = new Resistor(resIndex, name, resistance, nodeid);
                            if (NodeArray[nodeid[0]].isNodeEmpty()) nodeIndex++;
                            if (NodeArray[nodeid[1]].isNodeEmpty()) nodeIndex++;
                            NodeArray[nodeid[0]].addResistor(resIndex);
                            NodeArray[nodeid[1]].addResistor(resIndex);
                            resIndex++;
                        }
    }
    return;
}

void modifyR(stringstream & lineStream) {
    string name = "empty";
    double resistance = 0;
    bool valid = true;
    
    if (tooFewArgs (lineStream)) {
        // first we check if there are more arguments after command
        lineStream >> name;
        if (!(validArgument(lineStream))) valid = false;
        // making sure argument is valid
        else
            if (!nameIsNotAll (name)) valid = false;
        // making sure resistor name is not "all"
            else
                if (!(tooFewArgs (lineStream))) valid = false;
        // making sure there are more arguments after name
        if (valid) { // if previous argument passed all tests, we continue
            lineStream >> resistance;
            if (!(validArgument(lineStream))) valid = false;
            // making sure the entered argument is valid
            else
                if (!(validResistance (resistance))) valid = false;
            // making sure the resistance value is positive
                else
                    if (!(tooManyArgs (lineStream))) valid = false;
            // making sure this is the last argument
                    else
                        if (!(resExists(name))) valid = false;
                        else {
                            for (int i = 0; i < resIndex; i++) {
                                if (ResArray[i]->getName() == name) {
                                    double oldResistance = ResArray[i]->getResistance();
                                    ResArray[i]->setResistance(resistance);
                                    cout << "Modified: " << "resistor " << ResArray[i]->getName() << " from "
                                    << oldResistance << " Ohms to " << ResArray[i]->getResistance() << " Ohms\n";
                                }
                            }
                        }
        }
    }
    return;
}

void printR(stringstream & lineStream) {
    string name = "empty";
    bool valid = true;
    if (tooFewArgs (lineStream)) {
        // first checking there are more arguments after command
        lineStream >> name;
        if (!(validArgument(lineStream))) valid = false;
        // making sure the entered argument is valid
        else
            if (!(tooManyArgs (lineStream))) valid = false;
        // making sure its the last argument
            else
                if (name == "all") {
                    cout << "Print: \n";
                    for (int i = 0; i < resIndex; i++) {
                        cout.width(20);
                        cout << left << ResArray[i]->getName();
                        cout.width(8);
                        cout << right << ResArray[i]->getResistance() << " Ohms " << ResArray[i]->getEndPoint1()
                        << " -> " << ResArray[i]->getEndPoint2() << endl;
                    }
                }
                else {
                    if (!(resExists(name))) valid = false;
                    else {
                        for (int i = 0; i < resIndex; i++) {
                            if (ResArray[i]->getName() == name) {
                                cout << "Print:\n";
                                cout.width(20);
                                cout << left << ResArray[i]->getName();
                                cout.width(8);
                                cout << right << ResArray[i]->getResistance() << " Ohms " << ResArray[i]->getEndPoint1()
                                << " -> " << ResArray[i]->getEndPoint2() << endl;
                            }
                        }
                    }
                }
    }
    return;
}

void printNode(stringstream & lineStream) {
    string name = "empty";
    int nodeid[2] = {0, 0};
    bool valid = true;
    
    if ((tooFewArgs (lineStream))) {
        // first checking if there are more arguments past command
        lineStream >> nodeid[1];
        if (!lineStream.fail()) {
            // checking if input is integer. If the fail flag is NOT raised, then the argument is an integer
            if (!(validArgument(lineStream))) valid = false;
            // checking if argument is valid
            else
                if (!(nodeValWithinRange (nodeid[0], nodeid[1]))) valid = false;
            // making sure node ID is within defined range
                else
                    if (!(tooManyArgs (lineStream))) valid = false;
            // making sure this is the last argument
                    else{
                        cout << "Print:\n";
                        NodeArray[nodeid[1]].print(nodeid[1]);
			for (int i = 0; i < resIndex; i++) {
                            if (ResArray[i]->getEndPoint1() == nodeid[1] || ResArray[i]->getEndPoint2() == nodeid[1]) {
                                cout << "  ";
                                cout.width(20);
                                cout << left << ResArray[i]->getName();
                                cout.width(8);
                                cout << right << ResArray[i]->getResistance() << " Ohms " << ResArray[i]->getEndPoint1()
                                     << " -> " << ResArray[i]->getEndPoint2() << endl;
                            }
                        }
                    }
        }
        else {
            // since the flag was raised, we know that the input is a string
            lineStream.clear();
            // first we clear all flags
            lineStream >> name;
            // now we process the stream into name
            if (!(validArgument(lineStream))) valid = false;
            // making sure argument is valid
            else
                if (name != "all") cout << "Error: invalid argument\n";
            // if the string is anything but all, give above message
                else
                    if (!(tooManyArgs (lineStream))) valid = false;
                    // make sure this is the last argument, if it is give the below message
                    else {
                        cout << "Print:\n";
			for (int j = 0; j <= maxNodeNumber; j++) {
                            int* resIDArray = NodeArray[j].getResIDArray();
                            NodeArray[j].print(j);
                            if (resIDArray[0] != -1) {
                                cout << "  ";
                                cout.width(20);
                                cout << left << ResArray[resIDArray[0]]->getName();
                                cout.width(8);
                                cout << right << ResArray[resIDArray[0]]->getResistance() << " Ohms "
                                     << ResArray[resIDArray[0]]->getEndPoint1() << " -> "
                                     << ResArray[resIDArray[0]]->getEndPoint2() << endl;
                            }
                            if (resIDArray[1] != -1) {
                                cout << "  ";
                                cout.width(20);
                                cout << left << ResArray[resIDArray[1]]->getName();
                                cout.width(8);
                                cout << right << ResArray[resIDArray[1]]->getResistance() << " Ohms "
                                << ResArray[resIDArray[1]]->getEndPoint1() << " -> "
                                << ResArray[resIDArray[1]]->getEndPoint2() << endl;
                            }
                            if (resIDArray[2] != -1) {
                                cout << "  ";
                                cout.width(20);
                                cout << left << ResArray[resIDArray[2]]->getName();
                                cout.width(8);
                                cout << right << ResArray[resIDArray[2]]->getResistance() << " Ohms "
                                << ResArray[resIDArray[2]]->getEndPoint1() << " -> "
                                << ResArray[resIDArray[2]]->getEndPoint2() << endl;
                            }
                            if (resIDArray[3] != -1) {
                                cout << "  ";
                                cout.width(20);
                                cout << left << ResArray[resIDArray[3]]->getName();
                                cout.width(8);
                                cout << right << ResArray[resIDArray[3]]->getResistance() << " Ohms "
                                << ResArray[resIDArray[3]]->getEndPoint1() << " -> "
                                << ResArray[resIDArray[3]]->getEndPoint2() << endl;
                            }
                            if (resIDArray[4] != -1) {
                                cout << "  ";
                                cout.width(20);
                                cout << left << ResArray[resIDArray[4]]->getName();
                                cout.width(8);
                                cout << right << ResArray[resIDArray[4]]->getResistance() << " Ohms "
                                << ResArray[resIDArray[4]]->getEndPoint1() << " -> "
                                << ResArray[resIDArray[4]]->getEndPoint2() << endl;
                            }
                        }
                    }
            
        }
    }
    return;
}


void deleteR(stringstream & lineStream) {
    string name = "empty";
    bool valid = true;
    if (tooFewArgs(lineStream)){
        // making sure there are more arguments after command
        lineStream >> name;
        if (!(validArgument(lineStream))) valid = false;
        // making sure the argument is valid
        else
            if (!(tooManyArgs (lineStream))) valid = false;
        // making sure this is the last argument
            else
                if (name == "all") {
                    cout << "Deleted: all resistors\n";
                    deleteFunct();
                    delete [] ResArray;
                    NodeArray = new Node[maxNodeNumber + 1];
                    ResArray = new Resistor*[maxResistors];
                    for (int j = 0; j < maxResistors; j++) {
                        ResArray[j] = NULL;
                    }
                }
    }
    return;
}

// deletes whatever necessary when called upon
void deleteFunct() {
    if (ResArray != NULL) {
        for (int i = 0; i < resIndex; i++) {
            delete (ResArray[i]);
            ResArray[i] = NULL;
        }
    }
    if (NodeArray != NULL) {
        delete [] NodeArray;
        NodeArray = NULL;
    }
    resIndex = 0;
    //nodeIndex = 0;
    return;
}

void clearAtExit(void) {
    if (ResArray != NULL && NodeArray !=NULL) {
        deleteFunct();
        delete [] ResArray;
        ResArray = NULL;
    }
    return;
}
// checking if argument is of correct type
bool validArgument(stringstream & lineStream){
    if (lineStream.peek() != ' ' && lineStream.peek() != '\t' && !lineStream.eof()) {
        // ignoring spaces, tabs, and eof flags
        cout << "Error: invalid argument\n";
        lineStream.clear();
        // clearing all fail & eof flags
        return false;
    }
    else if (lineStream.fail() && !lineStream.eof()){
        // making sure lineStream fails because of the type, not because its reached the end of file
        lineStream.clear();
        // clearing all fail and eof flags
        cout << "Error: invalid argument\n";
        return false;
    }
    else return true;
}

// checking if R has a negative value
bool validResistance (double resistance) {
    if (resistance < 0) {
        cout << "Error: negative resistance\n";
        return false;
    } else return true;
}

// making sure node ID is within defined range
bool nodeValWithinRange (int nodeid1, int nodeid2) {
    if (nodeid1 < MIN_NODE_NUMBER || nodeid1 > maxNodeNumber) {
        cout << "Error: node " << nodeid1 << " is out of permitted range " << MIN_NODE_NUMBER << "-" << maxNodeNumber << endl;
        return false;
    }
    else if (nodeid2 < MIN_NODE_NUMBER || nodeid2 > maxNodeNumber) {
        cout << "Error: node " << nodeid2 << " is out of permitted range " << MIN_NODE_NUMBER << "-" << maxNodeNumber << endl;
        return false;
    }
    else return true;
}

// making sure resistor name is not all
bool nameIsNotAll (string name) {
    if (name == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\"\n";
        return false;
    } else return true;
}

// making sure nodes are different
bool differentNodes (int nodeid1, int nodeid2) {
    if (nodeid1 == nodeid2) {
        cout << "Error: both terminals of resistor connect to node " << nodeid1 << endl;
        return false;
    } else return true;
}
// checking if there are too few arguments
bool tooFewArgs (stringstream & lineStream) {
    if ((lineStream>>ws).eof()) {
        // ws is a C++ function that ignores all whitespace until reaching a
        // character that is a different character, in the iomanip file
        // asking lineStream to skip all white spaces until it reaches a non space character.
        // If we skip and result in an end of file, then there are too few arguments
        cout << "Error: too few arguments\n";
        return false;
    }
    else if (lineStream.eof()) {
        cout << "Error: too few arguments\n";
        return false;
    } else return true;
}

// checking if there are too many arguments, and making sure trailing spaces/tabs are valid
bool tooManyArgs (stringstream & lineStream) {
    if (!(lineStream>>ws).eof()) {
        // ws is a C++ function that ignores all whitespace until reaching a
        // character that is a different character, in the iomanip file
        // asking lineStream to skip all white spaces until it reaches a non space character.
        // If we skip and result in an end of file, then there are too few argument
        cout << "Error: too many arguments\n";
        return false;
    } else return true;
}

bool greaterThanZero(int maxNumber) {
    if (maxNumber <= 0) {
        cout << "Error: maxVal arguments must be greater than 0 \n";
        return false;
    }
    return true;
}

// checking if resistor name is in array
bool resExists (string name) {
    for (int i = 0; i < resIndex; i++) {
        if (ResArray[i]->getName() == name) {
            return true;
        }
    }
    cout << "Error: resistor " << name << " not found\n";
    return false;
}

// checking if resistor array is filled
bool resArrayfull (int resIndex) {
    if (resIndex < maxResistors) return false;
    else {
        cout << "Error: resistor array is full\n";
        return true;
    }
}

// checking if node is empty
bool nodeHasSpace (Node & thisNode, int resIndex) {
    if (!(thisNode.canAddResistor(resIndex))) {
        cout << "Error: node is full\n";
        return false;
    } else return true;
}

// checking if resistor name is unique
bool uniqueResName (string name) {
    for (int i = 0; i < resIndex; i++) {
        if (ResArray[i]->getName() == name) {
            cout << "Error: resistor " << name << " already exists\n";
            return false;
        }
    }
    return true;
}
/*
void allocateResArray(Resistor** & ResArray) {
    ResArray = new Resistor*[maxResistors];
    
    for (int j = 0; j < maxResistors; j++) {
            ResArray[j] = NULL;
    }
    return;
}

void allocateNodeArray(Node* & NodeArray) {
    NodeArray = new Node[maxNodeNumber + 1];
    
    return;
}
*/
