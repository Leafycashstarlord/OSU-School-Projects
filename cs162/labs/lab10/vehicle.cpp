#include <iostream>
#include <string>
#include <cstdlib>
#include "vehicle.h"

using namespace std;

Vehicle::Vehicle(){
	v_type = "";
}

void Vehicle::set_vehicle(string name){
	v_type = name;
}

string Vehicle::get_vehicle(){
	return v_type;
}
