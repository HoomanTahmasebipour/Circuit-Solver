//
//  NodeList.hpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#ifndef NodeList_hpp
#define NodeList_hpp

#include <stdio.h>
#include <string>

#include "Node.hpp"

using namespace std;

class NodeList {
private:
    Node* head = NULL;
    int numUnsetNodes = 0;
public:
    NodeList(); // default constructor, does nothing
    ~NodeList(); // must follow head and delete what it points to (i think you only go in one level)
    // if above is true then this destructor MUST be called at the end of the program
    // do if (head != NULL) delete head
    void setHead (Node & next);
    
    Node* getHead();
    // returns true if a given node already exists
    bool FoundNode (int nodeID);
    // returns true if there is at least one node with a set voltage
    bool nodeWithSetVoltExists() const;
    // returns a pointer to a newly created node if it did not exist before, or returns a NULL
    // if the node did exist already
    Node* FindOrCreateNode (int nodeID);
    // returns a pointer to the resistor object if a given name already exists, false if it doesnt
    Resistor* FoundResistorLabel (string name);
    
    void setV(int nodeID, double volts);
    void unsetV (int nodeID);
    
    void modifyResistor (string name, double resValue);
    void insertNode(int nodeID);
    void insertResistor (string name, int nodeID1, int nodeID2, double resValue);
    void printNode (int nodeID);
    void printAllNodes();
    void deleteRes (string name);
    void deleteAllRes();
    void solve();
    
};

#endif /* NodeList_hpp */
