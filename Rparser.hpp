//
//  Rparser.hpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#ifndef Rparser_hpp
#define Rparser_hpp

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "Resistor.hpp"
#include "ResistorList.hpp"
#include "Node.hpp"
#include "NodeList.hpp"
// checks to make sure the entered nodeIDs are different
bool differentNodes (int nodeid1, int nodeid2);

// inserting a new resistor into network
void insertR (stringstream & lineStream, NodeList & network);
// modifying a pre-existing resistor
void modifyR (stringstream & lineStream, NodeList & network);
// print a specific resistor
void printR (stringstream & lineStream, NodeList & network);
// print a specific node or all nodes
void printNode (stringstream & lineStream, NodeList & network);
// delete a specific resistor or all resistors, while leaving nodes untouched
void deleteR (stringstream & lineStream, NodeList & network);
// setting the voltage of a node to a value
void setV (stringstream & lineStream, NodeList & network);
// undoing the actions of setV
void unsetV (stringstream & lineStream, NodeList & network);
// solves the whole network by iterating through each node and solving for
// the node voltages at each objects. Iteration stops when the change in node voltages
// becomes less than a predefined constant
void solve (NodeList & network);


#endif /* Rparser_hpp */
