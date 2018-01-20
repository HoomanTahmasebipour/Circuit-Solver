//
//  Rparser.hpp
//  ece244_lab3_inpt&store
//
//  Created by Hooman Tahmasebipour on 2017-10-16.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#ifndef Rparser_hpp
#define Rparser_hpp

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Resistor.h"
#include "Node.h"

#define MIN_NODE_NUMBER 0

using namespace std;

// functions from lab 2:vvvv
// checking if argument is valid
bool validArgument(stringstream & lineStream);
// checking if R has a negative value
bool validResistance (double resistance);
// making sure node ID is within defined range
bool nodeValWithinRange (int nodeid1, int nodeid2);
// making sure resistor name is not all
bool nameIsNotAll (string name);
// making sure nodes are different
bool differentNodes (int nodeid1, int nodeid2);
// checking if there are too few arguments
bool tooFewArgs (stringstream & lineStream);
// checking if there are too many arguments, and making sure trailing spaces/tabs are valid
bool tooManyArgs (stringstream & lineStream);
// checking if resistor name is in array
bool resExists (string name);
// checking if resistor array is filled
bool resArrayfull (int rescount);
// checking if node is empty
// TODO: this function is wrong!, fix after working with Node array
bool nodeHasSpace (Node & thisNode, int resCount);
// checking if resistor name is unique
bool uniqueResName (string name);
// checking if maxVal arguments are greater than 0
bool greaterThanZero(int maxNumber);

// inserts R if input stream is error free
void insertR(stringstream & lineStream, bool noInserts);
// modifies R if input stream is error free
void modifyR(stringstream & lineStream);
// prints R if input stream is error free
void printR(stringstream & lineStream);
// prints node if input stream is error free
void printNode(stringstream & lineStream);
// deletes R if input stream is error free
void deleteR(stringstream & lineStream);


// functions added in lab3:vvvv
// function stores the maximum number of nodes and resistors
void maxVal(stringstream & lineStream, bool noInserts);
// deletes when called upon by program
void deleteFunct(void);
// clears all allocated memory when exiting program
void clearAtExit(void);

#endif /* Rparser_hpp */
