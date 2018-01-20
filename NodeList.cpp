//
//  NodeList.cpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//
#define MIN_ITERATION_CHANGE 0.0001

#include <iostream>

using namespace std;

#include "NodeList.hpp"

NodeList::NodeList() {
  // default constructor, does nothing
}
NodeList::~NodeList(){
    if (head != NULL) {
        delete head;
        head = NULL;
    }
} // must follow head and delete what it points to (i think you only go in one level)
// if above is true then this destructor MUST be called at the end of the program
// do if (head != NULL) delete head

void NodeList::setHead (Node & next) {
    // pass in, by refference, a newly created object of class type Node, after having initialized its values
    // to desired state, then set the contents of head equal to this new object.
    *head = next;
}

Node* NodeList::getHead() {
    if (head != NULL) return head;
    return NULL;
}

bool NodeList::FoundNode (int nodeID) {
    Node* current = head;
    
    while (current != NULL) {
        if (current != NULL && current->getNodeID() == nodeID) return true;
        else current = current->getNext();
    }
    
    return false;
}

bool NodeList::nodeWithSetVoltExists() const {
    Node* current = head;
    
    while (current != NULL) {
        if (current->getIfSet()) return true;
        current = current -> getNext();
    }
    
    return false;
}

void NodeList::solve() {
    bool converged = false;
    bool nodeConverged[numUnsetNodes];
    double oldVoltage = 0;
    int numUnSet = 0;
    Node* current = head;
    
    while (!converged) {
        current = head;
        while (current != NULL) {
            if (!current->getIfSet()) {
                // storing old voltage value
                oldVoltage = current->getVoltage();
                // calling the solve function for a given node now that pengion is more powerful than before
                current->solve(head);
                if ((current->getVoltage() - oldVoltage <= MIN_ITERATION_CHANGE) && ((oldVoltage - current->getVoltage() <= MIN_ITERATION_CHANGE)))
                    // if the absolute value node voltage is less than the predfined
                    // constant, then this node voltage is converging
                    nodeConverged[numUnSet] = true;
                else nodeConverged[numUnSet] = false;
                numUnSet = numUnSet + 1;
            }
            current = current->getNext();
        }
        for (int i = 0; i < numUnSet; ++i) {
            if (nodeConverged[i])
                // if the cell containts true, set converged to true;
                converged = true;
            else {
                converged = false;
                // as soon as you find a false, stop checking the rest of the nodes
                break;
            }
        }
        numUnSet = 0;
    }
    current = head;
    cout << "Solve: \n";
    while (current != NULL) {
        cout << "  ";
        cout << "Node " << current->getNodeID() << ": " << current->getVoltage() << " V\n";
        current = current->getNext();
    }
}

Resistor* NodeList::FoundResistorLabel (string name) {
    Node* thisNode = head;
    if (thisNode == NULL) return NULL;
    
    while (thisNode != NULL) {
        Resistor* thisResistor = thisNode->getNextResistor();
        while (thisResistor != NULL) {
            if (thisResistor->getLabel() == name) {
                return thisResistor;
            }
            else thisResistor = thisResistor->getNext();
        }
        thisNode = thisNode->getNext();
    }
    
    return NULL;
}

void NodeList::modifyResistor (string name, double resValue) {
    Node* thisNode = head;
    double resistance_old = 0;
    
    while (thisNode != NULL) {
        Resistor* thisResistor = thisNode->getNextResistor();
        while (thisResistor != NULL) {
            if (thisResistor->getLabel() == name) {
                resistance_old = thisResistor->getResistance();
                thisResistor->setResistance(resValue);
            }
            thisResistor = thisResistor->getNext();
        }
        thisNode = thisNode->getNext();
    }
    
    cout << "Modified: resistor " << name << " from " << resistance_old << " Ohms"
         << " to " << resValue << " Ohms\n";
    
    return;
}
/* Delete resistor by name, if DNE return failure message...Delete ALL resistors in resistor list
 should these be in this class? TODO: work on in when u get to delete*/

void NodeList::deleteRes (string name) {
    Node* thisNode = head;
    
    while (thisNode != NULL) {
        thisNode->deleteRes(name);
        thisNode = thisNode->getNext();
    }
}

void NodeList::deleteAllRes() {
    Node* current = head;
    
    while (current != NULL) {
        current->deleteAllRes();
        current = current->getNext();
    }
}

void NodeList::insertNode(int nodeID) {
    Node* current = head;
    Node* previous = NULL;
    
    if (current == NULL) {
        head = new Node(nodeID);
        numUnsetNodes = numUnsetNodes + 1;
        return;
    }
    
    while (current != NULL && nodeID > current->getNodeID()) {
        previous = current;
        current = current->getNext();
    }
    if (current == head) {
        previous = current;
        head = new Node(nodeID);
        head->setNext(previous);
        numUnsetNodes = numUnsetNodes + 1;
        return;
    }
    previous->createNext(nodeID);
    previous = previous->getNext();
    previous->setNext(current);
    numUnsetNodes = numUnsetNodes + 1;
    return;
}

void NodeList::insertResistor (string name, int nodeID1, int nodeID2, double resValue) {
    Node* current = head;
    
    while (current != NULL) {
        if (current->getNodeID() == nodeID1 || current->getNodeID() == nodeID2) {
            current->insertResistor(name, nodeID1, nodeID2, resValue);
        }
        current = current->getNext();
    }
    return;
}

void NodeList::printNode(int nodeID) {
    Node* current = head;
    
    while (current != NULL) {
        if (current->getNodeID() == nodeID) {
            current->printNode(nodeID);
        }
        current = current->getNext();
    }
}

void NodeList::printAllNodes() {
    Node* current = head;
    
    while (current != NULL) {
        current->printNode(current->getNodeID());
        current = current->getNext();
    }
}

void NodeList::setV(int nodeID, double volts) {
    Node* current = head;
    
    while (current != NULL) {
        if (current->getNodeID() == nodeID) {
            current->setNewVoltage(volts);
        }
        current = current->getNext();
    }
    numUnsetNodes = numUnsetNodes - 1;
}

void NodeList::unsetV(int nodeID) {
        Node* current = head;
    
    while (current != NULL) {
        if (current->getNodeID() == nodeID) {
            current->unsetV();
        }
        current = current->getNext();
    }
    numUnsetNodes = numUnsetNodes + 1;
}
