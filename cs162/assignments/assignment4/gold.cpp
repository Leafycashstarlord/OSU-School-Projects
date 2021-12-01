/************
 *Jackson E. Rollins
 *5/25/2020
 *Gold cpp file
 * ************/
#include <iostream>
#include <string>
#include "gold.h"

using namespace std;

//Gold constructor
Gold::Gold(){
	warning_msg = "You see a glimmer nearby.";
}

//get the warning message
string Gold::get_warning(){
	return warning_msg;
}
