//
//  Resistor.cpp
//  ece244_lab3_inpt&store
//
//  Created by Hooman Tahmasebipour on 2017-10-15.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include "Resistor.h"
#include "Rparser.h"

Resistor::Resistor() {
    // do nothing
}

Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]) {
    resIndex = rIndex_;
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
}

Resistor::~Resistor() {
    // do nothing
}

string Resistor::getName() const{
    
    return name;
}

double Resistor::getResistance() const{
    
    return resistance;
}

int Resistor::getEndPoint1() const {
    
    return endpointNodeIDs[0];
}

int Resistor::getEndPoint2() const {
    
    return endpointNodeIDs[1];
}

void Resistor::setResistance (double resistance_) {
    resistance = resistance_;
    
    return;
}






