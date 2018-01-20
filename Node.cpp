//
//  Node.cpp
//  ece244_lab3_inpt&store
//
//  Created by Hooman Tahmasebipour on 2017-10-15.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include "Node.h"

Node::Node() {
    // do nothing
}

Node::~Node() {
    // do nothing
}

bool Node::canAddResistor(int rIndex) {
    if (numRes < MAX_RESISTORS_PER_NODE) return true;
    return false;
}
void Node::addResistor (int rIndex){
    resIDArray[numRes] = rIndex;
    numRes++;
    isEmpty = false;
    return;
}
void Node::print (int nodeIndex) {
    
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)\n";
    
    return;
}

bool Node::isNodeEmpty() const {
    
    return isEmpty;
}

int* Node::getResIDArray() {
    
    return resIDArray;
}
