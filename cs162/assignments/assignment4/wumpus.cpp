/**********
 *Jackson E. Rollins
 *5/25/2020
 *Wumpus cpp file
 * ***********/
#include <iostream>
#include <string>
#include "wumpus.h"

using namespace std;

//Wumpus constructor
Wumpus::Wumpus(){
	warning_msg = "You smell a terrible stench nearby.";
}

//Get the warning messege
string Wumpus::get_warning(){
	return warning_msg;
}
