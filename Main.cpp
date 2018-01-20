//  Parser.cpp
//  ece241_lab2_parser
//
//  Created by Hooman Tahmasebipour on September 26, 2017, 1:47 PM.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "Resistor.h"
#include "Node.h"
#include "Rparser.h"

#define MIN_NODE_NUMBER 0

using namespace std;

int main(int argc, char** argv) {
    string line, command, rest;
    cout << "> ";
    getline(cin, line);
    bool noInserts = true;
    
    while (!cin.eof()) {
        stringstream lineStream (line);
        lineStream >> command;
        if (command == "maxVal") {
            maxVal(lineStream, noInserts);
        }
        else if (command == "insertR") {
            insertR(lineStream, noInserts);
            noInserts = false;
        }
        else if (command == "modifyR") {
            modifyR(lineStream);
        }
        else if (command == "printR") {
            printR(lineStream);
        }
        else if (command == "printNode") {
            printNode(lineStream);
        }
        else if (command == "deleteR") {
            deleteR(lineStream);
        }
        else { // if the command matches none of the above, it is invalid
            cout << "Error: invalid command\n";
        }
        cout << "> ";
        getline(cin, line);
    }

    clearAtExit();
    
    return 0;
}


