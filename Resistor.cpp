//
//  Resistor.cpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include "Resistor.hpp"

Resistor::Resistor() {
  // default constructor, doesnt do SHIT
}

Resistor::Resistor (string name, int nodeID1, int nodeID2, double resValue) {
    // second constructor, takes everything but next and intializes it. this is done because we want
    // to be able to set next case by case, and not be stuck with a universal implementaion of it
    label = name;
    endpoints[0] = nodeID1;
    endpoints[1] = nodeID2;
    resistance = resValue;
    next = NULL;
}

Resistor::~Resistor(){
    if (next != NULL) {
        delete next;
        next = NULL;
    }
} // destructor must do deep deletion, ie do "if (next != NULL) delete next"

Resistor* Resistor::getNext() const {
    return next;
}

double Resistor::getResistance() const {
    return resistance;
}

string Resistor::getLabel() const {
    return label;
}

int Resistor::getEndPoint1() const {
    return endpoints[0];
}

int Resistor::getEndPoint2() const {
    return endpoints[1];
}

void Resistor::setLabel (string name) {
    label = name;
}

void Resistor::setEndPoints (int ID1, int ID2) {
    endpoints[0] = ID1;
    endpoints[1] = ID2;
}

void Resistor::setResistance (double resValue){
    resistance = resValue;
}

void Resistor::createNext (string name, int nodeID1, int nodeID2, double resValue) {
    // pass in the necessary components of a resistor, and create this resistor
    next = new Resistor (name, nodeID1, nodeID2, resValue);
}

void Resistor::setNext (Resistor* & link) {
    next = link;
}

void Resistor::setNextToNULL() {
    next = NULL;
}
