/************
 *Jackson E. Rollins
 *5/25/2020
 *Pit cpp file
 * ************/
#include <iostream>
#include <string>
#include "pit.h"

using namespace std;

//Pit constructor
Pit::Pit(){
	warning_msg = "You feel a breeze.";
}

//Get the pit warning messege
string Pit::get_warning(){
	return warning_msg;
}
