//
//  Resistor.hpp
//  ece244_lab3_inpt&store
//
//  Created by Hooman Tahmasebipour on 2017-10-15.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

class Resistor
{
private:
    int resIndex;
    double resistance=0.0; // resistance (in Ohms)
    string name = "nada"; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to
    
public:
    Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]);
    Resistor();
    // rIndex_ is the index of this resistor in the resistor array
    // endpoints_ holds the node indices to which this resistor connects
    
    ~Resistor();
    
    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    int getEndPoint1() const;
    int getEndPoint2() const;
    
    
    void setResistance (double resistance_);
    
    // you *may* create either of the below to print your resistor
    void print ();
    friend ostream& operator<<(ostream& os,const Resistor&);
};


/*
 
 */



ostream& operator<<(ostream&,const Resistor&);

#endif    /* RESISTOR_H */
