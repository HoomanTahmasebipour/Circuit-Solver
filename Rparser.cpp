//
//  Rparser.cpp
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

void insertR (stringstream & lineStream, NodeList & network) {
    string name = "empty";
    int nodeID1, nodeID2;
    double resistance;
    bool valid = true;
    lineStream >> name;
    // make sure name doesnt already exist
    if (network.FoundResistorLabel(name) != NULL) {
        cout << "Error: resistor " << name << " already exists\n";
        valid = false;
    }
    else {
        lineStream >> resistance;
        lineStream >> nodeID1;
        lineStream >> nodeID2;
        // check if both nodeID1 and 2 are not the same
        if (differentNodes(nodeID1, nodeID2)) {
            if (!network.FoundNode(nodeID1)) {
                network.insertNode(nodeID1);
            }
            if (!network.FoundNode(nodeID2)) {
                network.insertNode(nodeID2);
            }
            network.insertResistor(name, nodeID1, nodeID2, resistance);
            cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed
            << resistance << " Ohms " << nodeID1 << " -> " << nodeID2 << endl;
        }
    }
}

void modifyR (stringstream & lineStream, NodeList & network) {
    string name = "empty";
    double resistance;
    
    lineStream >> name;
    if (network.FoundResistorLabel(name) == NULL) {
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else {
        lineStream >> resistance;
        network.modifyResistor(name, resistance);
    }
}

void printR(stringstream & lineStream, NodeList & network) {
    string name = "empty";
    Resistor* resToPrint = NULL;
    
    lineStream >> name;
    if (network.FoundResistorLabel(name) == NULL) {
        cout << "Error: resistor " << name << " not found" << endl;
    }
    else {
        resToPrint = network.FoundResistorLabel(name);
        cout << "Print:\n";
        if (resToPrint != NULL) {
            cout.width(20);
            cout << left << resToPrint->getLabel();
            cout.width(8);
            cout << right << resToPrint->getResistance() << " Ohms " << resToPrint->getEndPoint1()
                 << " -> " << resToPrint->getEndPoint2() << endl;
        }
    }
    
    return;
}

void printNode (stringstream & lineStream, NodeList & network) {
    string name = "empty";
    int nodeID;
    
    lineStream >> nodeID;
    cout << "Print:\n";
    if (!lineStream.fail()) {
        network.printNode(nodeID);
    }
    else {
        network.printAllNodes();
    }
}

void deleteR (stringstream & lineStream, NodeList & network) {
    string name = "empty";
    
    lineStream >> name;
    if (name == "all") {
        network.deleteAllRes();
        cout << "Deleted: all resistors\n";
    }
    else {
        if (network.FoundResistorLabel(name) == NULL) {
            cout << "Error: resistor " << name << " not found" << endl;
        }
        else {
            network.deleteRes(name);
            cout << "Deleted: resistor " << name << endl;
        }
    }
}

void setV (stringstream & lineStream, NodeList & network){
    int nodeID;
    double voltage;
    
    lineStream >> nodeID;
    if (!network.FoundNode(nodeID)) {
        cout << "Error: node " << nodeID << " not found\n";
    }
    else {
        lineStream >> voltage;
        network.setV(nodeID, voltage);
        cout << "Set: node " << nodeID << " to " << voltage << " Volts\n";
    }
    
    return;
}

void unsetV (stringstream & lineStream, NodeList & network) {
    int nodeID;
    
    lineStream >> nodeID;
    if (!network.FoundNode(nodeID)) {
        cout << "Error: node " << nodeID << " not found\n";
    }
    else {
        network.unsetV(nodeID);
        cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
    }
    
    return;
}

void solve (NodeList & network) {
    
    if (!network.nodeWithSetVoltExists()) {
        cout << "Error: no nodes have their voltage set\n";
    }
    else {
        network.solve();
    }
}

bool differentNodes (int nodeid1, int nodeid2) {
    if (nodeid1 == nodeid2) {
        cout << "Error: both terminals of resistor connect to node " << nodeid1 << endl;
        return false;
    } else return true;
}
