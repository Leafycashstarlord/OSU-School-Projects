/**********
 *Jackson E. Rollins
 *5/25/2020
 *Empty cpp file
 * **********/
#include <iostream>
#include <string>
#include "empty.h"

using namespace std;

//Empty constructor
Empty::Empty(){
	warning_msg = "No Event";
}

//Get warning messege
string Empty::get_warning(){
	return warning_msg;
}
