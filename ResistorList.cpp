//
//  ResistorList.cpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include "ResistorList.hpp"

using namespace std;

ResistorList::ResistorList(){
    head = NULL;
    
} // set head to null

ResistorList::~ResistorList() {
    if (head != NULL) {
        delete head;
        head = NULL;
    }
} // deep deletion of resistors, ie do if (head != NULL) delete head

void ResistorList::setHead (Resistor & next) {
    // pass in, by refference, a newly created object of class type Node, after having initialized its values
    // to desired state, then set the contents of head equal to this new object.
    *head = next;
}

Resistor* ResistorList::getHead() const {
    if (head != NULL) return head;
    return NULL;
}

int ResistorList::getNumRes() const {
    return numRes;
}

void ResistorList::insertResistor (string name, int nodeID1, int nodeID2, double resValue) {
    Resistor* current = head;
    
    numRes = numRes + 1;
    
    if (current == NULL) {
        head = new Resistor(name, nodeID1, nodeID2, resValue);
        return;
    }
    while (current->getNext() != NULL) {
        current = current->getNext();
    }
    
    current->createNext(name, nodeID1, nodeID2, resValue);
}

void ResistorList::printResistors(int nodeID) {
    Resistor* current = head;
    if (numRes > 0) cout << "Connections at node " 
                         << nodeID << ": " << numRes << " resistor(s)\n";
    while (current != NULL) {
        cout << "  ";
        cout.width(20);
        cout << left << current->getLabel();
        cout.width(8);
        cout << right << current->getResistance() << " Ohms " << current->getEndPoint1()
             << " -> " << current->getEndPoint2() << endl;
        
        current = current->getNext();
    }
}

void ResistorList::deleteAllResistors() {
    Resistor* current = head;
    if (current != NULL) {
        delete head;
        head = NULL;
        numRes = 0;
    }
}

void ResistorList::deleteRes(string name) {
    Resistor* thisRes = head;
    Resistor* prevRes = NULL;
    
    while (thisRes != NULL) {
        if (thisRes->getLabel() == name) break;
        prevRes = thisRes;
        thisRes = thisRes->getNext();
    }
    if (thisRes == NULL) return;
    if (thisRes == head) {
        head = head->getNext();
        thisRes->setNextToNULL();
        delete thisRes;
        thisRes = NULL;
        numRes = numRes - 1;
        return;
    }
    Resistor* temp = thisRes->getNext();
    if (prevRes != NULL) prevRes->setNext(temp);
    thisRes->setNextToNULL();
    delete thisRes;
    thisRes = NULL;
    numRes = numRes - 1;
}

double ResistorList::equivalentR (int nodeID1, int nodeID2) {
    Resistor* current = head;
    double equivalentResDenom = 0.0;
    
    while (current != NULL) {
        if ((current->getEndPoint1() == nodeID1 && current->getEndPoint2() == nodeID2) ||
                (current->getEndPoint1() == nodeID2 && current->getEndPoint2() == nodeID1)) {
            // if the nodeIDs for this resistor are the same as those that are passed in,
            // then update equivalentResDenom;
            equivalentResDenom = equivalentResDenom + (1.0 / current->getResistance());
        }
        current = current->getNext(); 
    }
    if (equivalentResDenom == 0.0) return 0;
    else return (1.0 / equivalentResDenom);
}
