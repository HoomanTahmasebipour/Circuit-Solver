//
//  Node.hpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "ResistorList.hpp"

using namespace std;

class Node {
private:
    int nodeId = 0;
    bool setVoltage = false;
    double voltage = 0.0;
    Node* next =NULL;
    ResistorList connectedResistors; 
public:
    Node(); // default constructor
    Node(int ID); // takes the nodeid and initializes it
    ~Node(); // must do deep deletion, ie if (next != NULL) delete next
    
    // Getter functions to allow access to private member types
    int getNodeID() const;
    Node* getNext();
    Resistor* getNextResistor() const;
    bool getIfSet() const;
    double getVoltage() const;
    
    // Mutators to allow modifications
    void setNext (Node* & newNode);
    void createNext (int nodeID);
    void setNewVoltage (double volts);
    void unsetV ();
    
    // invokes the printResistors member function for ResistorList object in node
    void printNode(int nodeID);
    // deletes everyresistor in the network, leaves the existing nodes untouched
    void deleteAllRes();
    // deletes a single resistor in the networ, and re-arranges resistors
    // to keep netwokr structure
    void deleteRes(string name);
    // inserts a resistor into the resistor list for a given node object
    void insertResistor(string name, int nodeID1, int nodeID2, double resValue);
    // solves for the node voltage for the object on which it is invoked
    void solve(Node* head);
};

#endif /* Node_hpp */
