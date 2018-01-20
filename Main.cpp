//
//  Main.cpp
//  ece244_lab4
//
//  Created by Hooman Tahmasebipour on 2017-11-07.
//  Copyright © 2017 Hooman Tahmasebipour. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "Resistor.hpp"
#include "ResistorList.hpp"
#include "Node.hpp"
#include "NodeList.hpp"
#include "Rparser.hpp"

using namespace std;

int main(int argc, char** argv) {
    string line, command, rest;
    NodeList network;
    
    cout << "> ";
    getline(cin, line);
    
    while (!cin.eof()) {
        stringstream lineStream (line);
        lineStream >> command;
        if (command == "insertR") {
            insertR(lineStream, network);
        }
        else if (command == "modifyR") {
            modifyR(lineStream, network);
        }
        else if (command == "printR") {
            printR(lineStream, network);
        }
        else if (command == "printNode") {
            printNode(lineStream, network);
        }
        else if (command == "deleteR") {
            deleteR(lineStream, network);
        }
        else if (command == "setV") {
            setV(lineStream, network);
        }
        else if (command == "unsetV") {
            unsetV(lineStream, network);
        }
        else if (command == "solve") {
            solve(network);
        }
        else { // if the command matches none of the above, it is invalid
            cout << "Error: invalid command\n";
        }
        cout << "> ";
        getline(cin, line);
    }
    
    return 0;
}



