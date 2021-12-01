#include <iostream>
#include <string>
#include <cstdlib>
#include "person.h"
#include "vehicle.h"

using namespace std;

Person::Person(){
	name = "";
	num_vehicle = 0;
	vehicles = new Vehicle[0];
	for(int i = 0; i < num_vehicle; i++){
		vehicles[i].set_vehicle("");
	}
}

Person::Person(string new_name, int num){
	name = new_name;
	num_vehicle = num;
	vehicles = new Vehicle[num];
	for(int i = 0; i < num; i++){
		vehicles[i].set_vehicle("");
	}
}

Person::~Person(){
	delete [] vehicles;
}

Person::Person(const Person& old_person){
	name = old_person.name;
	num_vehicle = old_person.num_vehicle;
	for(int i = 0; i < num_vehicle; i++){
		vehicles[i] = old_person.vehicles[i];
	}
}

Person& Person::operator=(const Person& old_person){
	if(this != &old_person){
		name = old_person.name;
		num_vehicle = old_person.num_vehicle;
		for(int i = 0; i < num_vehicle; i ++){
			vehicles[i] = old_person.vehicles[i];
		}
	}
	return *this;
}

void Person::printName(){
	cout << "Name: " << name << endl;
}

void Person::printNum(){
	cout << "Number of Vehicles: " num_vehicle << endl;
}

void Person::printVehicle

string Person::get_name(){
	return name;
}

void Person::set_name(string new_name){
	name = new_name;
}

int Person::get_num_vehicle(){
	return num_vehicle;
}

void Person::set_num_vehicle(int num){
	num_vehicle = num;
}

Vehicle* Person::get_vehicles(){
	return vehicles;
}
