//
//  Node.cpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include "Node.hpp"

Node::Node() {
    // default constructor, does not do SHITE
}

Node::Node(int ID) {
    nodeId = ID;
    next = NULL;
} // takes the nodeid and initializes it

Node::~Node() {
    if (next != NULL) {
        delete next;
        next = NULL;
    }
} // must do deep deletion, ie if (next != NULL) delete next

int Node::getNodeID() const {
    
    return nodeId;
}

Node* Node::getNext() {
    return next;
}

double Node::getVoltage() const{
    return voltage;
}

Resistor* Node::getNextResistor() const {
    Resistor* temp = connectedResistors.getHead();
    return temp;
}

bool Node::getIfSet() const {
    return setVoltage;
}

void Node::setNext (Node* & newNode) {
    // pass in, by reference, the pre-existing node object that will be moved
    next = newNode;
}

void Node::setNewVoltage (double volts) {
    voltage = volts;
    setVoltage = true;
}

void Node::unsetV() {
    voltage = 0.0;
    setVoltage = false;
}

void Node::createNext (int nodeID) {
    // pass in the nodeID for the new object to be created, and dynamically create the object
    next = new Node(nodeID);
}

void Node::printNode(int nodeID) {
    connectedResistors.printResistors(nodeID);
}

void Node::insertResistor(string name, int nodeID1, int nodeID2, double resValue) {
    connectedResistors.insertResistor(name, nodeID1, nodeID2, resValue);
}

void Node::deleteAllRes() {
    connectedResistors.deleteAllResistors();
}

void Node::deleteRes(string name) {
    connectedResistors.deleteRes(name);
}

void Node::solve(Node* head) {
    Node* current = head;
    double equivR = 0.0;
    double leftTermDenom = 0.0;
    double rightTerm = 0.0;
    
    while (current != NULL) {
        equivR = connectedResistors.equivalentR(nodeId, current->getNodeID());
        if (equivR == 0) {
            leftTermDenom = leftTermDenom;
            rightTerm = rightTerm;
        }
        else {
            leftTermDenom = leftTermDenom + (1.0 / equivR);
            rightTerm = rightTerm + (current->getVoltage() / equivR);
        }
        
        current = current->getNext();
    }
    
    voltage = (1.0 / leftTermDenom) * rightTerm;
}


