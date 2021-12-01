/***************
 *Jackson E. Rollins
 *5/25/2020
 *Bats cpp file
 * ***********/
#include <iostream>
#include <string>
#include "bats.h"

using namespace std;

//Bats constructor
Bats::Bats(){
	warning_msg = "You hear wings flapping.";
}

//Gets the warning messege
string Bats::get_warning(){
	return warning_msg;
}
