#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "vehicle.h"

using namespace std;

class Person{
	private:
		string name;
		int num_vehicle;
		Vehicle* vehicles;
	public:
		Person();
		Person(string, int);
		~Person();
		Person(const Person&);
		Person& operator=(const Person&);

		string get_name();
		void set_name(string);
		int get_num_vehicle();
		void set_num_vehicle(int);
		Vehicle* get_vehicles();
		void printName();
		void printNum();
		void printVehicle();
};

#endif
