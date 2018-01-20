//
//  Resistor.hpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#ifndef Resistor_hpp
#define Resistor_hpp

#include <stdio.h>
#include <string>


using namespace std;

class Resistor {
private:
    string label = "nada";
    int endpoints[2] = {0, 0};
    double resistance = 0.0;
    Resistor* next = NULL;
public:
    Resistor(); // default constructor, doesnt do SHIT
    Resistor (string name, int nodeID1, int nodeID2, double resValue);
    // second constructor, takes everything but next and intializes it. this is done because we want
    // to be able to set next case by case, and not be stuck with a universal implementaion of it
    ~Resistor(); // destructor must do deep deletion, ie do "if (next != NULL) delete next"
    
    // getter functions that allow us to access private data members
    Resistor* getNext() const;
    double getResistance() const;
    string getLabel() const;
    int getEndPoint1() const;
    int getEndPoint2() const;
    
    // mutator functions that allow us to modify existing objects
    void setLabel (string name);
    void setEndPoints (int ID1, int ID2);
    void createNext (string name, int nodeID1, int nodeID2, double resValue);
    void setNext(Resistor* & link);
    void setNextToNULL();
    void setResistance (double resValue);
};

#endif /* Resistor_hpp */
