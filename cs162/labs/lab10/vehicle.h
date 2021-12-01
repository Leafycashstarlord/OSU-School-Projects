#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Vehicle{
	private:
		string v_type;
	public:
		Vehicle();
		void set_vehicle(string);
		string get_vehicle();
};

#endif
