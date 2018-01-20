//
//  ResistorList.hpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//
#ifndef ResistorList_hpp
#define ResistorList_hpp

#include <stdio.h>
#include <string>
#include <iomanip>
#include <iostream>

#include "Resistor.hpp"

using namespace std;

class ResistorList {
private:
    Resistor* head = NULL;
    int numRes = 0;
public:
    ResistorList(); // set head to null
    ~ResistorList(); // deep deletion of resistors, ie do if (head != NULL) delete head
    
    void setHead (Resistor & next);
    
    Resistor* getHead() const;
    
    int getNumRes() const;
    
    void printResistors(int nodeID);
    
    void deleteRes(string name);
    void deleteAllResistors();
    void insertResistor(string name, int nodeID1, int nodeID2, double resValue);
    double equivalentR(int nodeID1, int nodeID2);
};

#endif /* ResistorList_hpp */
