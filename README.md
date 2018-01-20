# Circuit-Solver
A command line application that is able to solve a given circuit (resistors only) using approximation techniques

List of supported commands in final commit:
use "setV <nodeID> <voltage>" to set a node's voltage (adding independant voltage source) ;
use "unsetV <nodeID>" to remove a node's voltage (remove independant voltage source) ;
use "solve" to solve the current circuit ;
use "deleteR <name>" to remove a particular resistor from circuit ;
use "deleteR all" to delete the entire network ;
use "insertR <name> resistance> <nodeID> <nodeID>" to insert a new resistor into the network ;
use "modifyR <name> <resistance> "to update the resistance value of the given resistor ;
use "printR <name>" to print the information relavent to this resistor ;
use "printNode <nodeid>" to print the information relavent to this node ;
use "printNode all" to print information for all nodes ;
